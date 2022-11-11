#include "ofxManipulator.h"

ofxManipulator::ofxManipulator()
:m_currScale              (SCALE_NONE)
,m_currScalePredict       (SCALE_NONE)
,m_currRotation           (ROTATION_NONE)
,m_currRotationPredict    (ROTATION_NONE)
,m_currTranslation        (TRANSLATION_NONE)
,m_currTranslationPredict (TRANSLATION_NONE)
,m_currManipulator        (MANIPULATOR_NONE)
,m_x_color                (0xff, 0x41, 0x36)
,m_y_color                (0x2e, 0xcc, 0x40)
,m_z_color                (0x00, 0x74, 0xd9)
,m_w_color                (0xff, 0x4b, 0xff)
,m_select_color           (0xff, 0xdc, 0x00)
//,m_scale                  (1.0f, 1.0f, 1.0f)
,m_manipulatorScale       (1.0f)
,m_screenFactor           (0.0f)
,m_angleRad               (0.0f)
, m_onFocusThreshold(100.0f) // added
, m_offFocusThreshold(200.0f) // added
, m_focus(false) // added
, m_auto_focus(true) // added
//, m_id(0) // added
, m_lastManipulator(MANIPULATOR_TRANSLATION) // added
{
	m_ea.scale = ofVec3f(1.0f, 1.0f, 1.0f);
	m_ea.id = 0;

  auto &events = ofEvents();
  ofAddListener(events.mouseMoved   , this, &ofxManipulator::mouseMoved   , OF_EVENT_ORDER_BEFORE_APP);
  ofAddListener(events.mousePressed , this, &ofxManipulator::mousePressed , OF_EVENT_ORDER_BEFORE_APP);
  ofAddListener(events.mouseDragged , this, &ofxManipulator::mouseDragged , OF_EVENT_ORDER_BEFORE_APP);
  ofAddListener(events.mouseReleased, this, &ofxManipulator::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
  ofAddListener(events.mouseScrolled, this, &ofxManipulator::mouseScrolled, OF_EVENT_ORDER_BEFORE_APP); // added
}

ofxManipulator::~ofxManipulator()
{
  auto &events = ofEvents();
  ofRemoveListener(events.mouseMoved   , this, &ofxManipulator::mouseMoved   , OF_EVENT_ORDER_BEFORE_APP);
  ofRemoveListener(events.mousePressed , this, &ofxManipulator::mousePressed , OF_EVENT_ORDER_BEFORE_APP);
  ofRemoveListener(events.mouseDragged , this, &ofxManipulator::mouseDragged , OF_EVENT_ORDER_BEFORE_APP);
  ofRemoveListener(events.mouseReleased, this, &ofxManipulator::mouseReleased, OF_EVENT_ORDER_BEFORE_APP);
  ofRemoveListener(events.mouseScrolled, this, &ofxManipulator::mouseScrolled, OF_EVENT_ORDER_BEFORE_APP); // added
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void ofxManipulator::draw(ofEasyCam cam)
{
  ofPushStyle();

  ofFill();
  ofSetLineWidth(1.0f);
  ofDisableDepthTest();

  m_view = cam.getModelViewMatrix();
  m_proj = cam.getProjectionMatrix();
  m_viewInverse = m_view.getInverse();
  m_screenFactor = computeScreenFactor();
  m_cameraMouseInputEnabled = cam.getMouseInputEnabled(); // added

  ofVec3f origin = m_ea.translation;
  float screenf = m_screenFactor;
  float screenf_half = screenf * 0.5f;

  ofMatrix4x4 m;
  m.rotate(m_ea.rotation);
  ofVec3f axe_x = m.getRowAsVec3f(0);
  ofVec3f axe_y = m.getRowAsVec3f(1);
  ofVec3f axe_z = m.getRowAsVec3f(2);

  ofColor unit_color_x = m_x_color;
  ofColor unit_color_y = m_y_color;
  ofColor unit_color_z = m_z_color;
  ofColor unit_color_w = m_w_color;
  ofColor select_color = m_select_color;

  switch (m_currManipulator)
  {
  case (MANIPULATOR_SCALE) :
  {
	  SCALE_TYPE curr = m_currScalePredict;

	  ofColor flagged_color_y = (flag_scale.xz || (flag_scale.xyz && (curr == SCALE_XYZ))) ? unit_color_y : convGrayscale(unit_color_y);
	  ofColor flagged_color_z = (flag_scale.xy || (flag_scale.xyz && (curr == SCALE_XYZ))) ? unit_color_z : convGrayscale(unit_color_z);
	  ofColor flagged_color_x = (flag_scale.yz || (flag_scale.xyz && (curr == SCALE_XYZ))) ? unit_color_x : convGrayscale(unit_color_x);

	  drawTriangle(origin, screenf_half, ((curr == SCALE_XZ) || (curr == SCALE_XYZ)), axe_x, axe_z, flagged_color_y);
	  drawTriangle(origin, screenf_half, ((curr == SCALE_XY) || (curr == SCALE_XYZ)), axe_x, axe_y, flagged_color_z);
	  drawTriangle(origin, screenf_half, ((curr == SCALE_YZ) || (curr == SCALE_XYZ)), axe_y, axe_z, flagged_color_x);

      axe_x *= screenf;
      axe_y *= screenf;
      axe_z *= screenf;

	  flagged_color_x = ((curr == SCALE_X) || (curr == SCALE_XYZ)) ? select_color : unit_color_x;
	  flagged_color_y = ((curr == SCALE_Y) || (curr == SCALE_XYZ)) ? select_color : unit_color_y;
	  flagged_color_z = ((curr == SCALE_Z) || (curr == SCALE_XYZ)) ? select_color : unit_color_z;

      drawScaleAxis(origin, axe_x, axe_y, (flag_scale.x || (flag_scale.xyz && (curr == SCALE_XYZ))) ? flagged_color_x : convGrayscale(flagged_color_x));
      drawScaleAxis(origin, axe_y, axe_x, (flag_scale.y || (flag_scale.xyz && (curr == SCALE_XYZ))) ? flagged_color_y : convGrayscale(flagged_color_y));
      drawScaleAxis(origin, axe_z, axe_x, (flag_scale.z || (flag_scale.xyz && (curr == SCALE_XYZ))) ? flagged_color_z : convGrayscale(flagged_color_z));
    }
    break;
    case (MANIPULATOR_ROTATION):
    {
      ROTATION_TYPE type = m_currRotation;
      ROTATION_TYPE curr = m_currRotationPredict;

      ofVec3f right;
      ofVec3f front;
      ofVec3f dir;
      ofVec3f up;

      dir = origin - m_viewInverse.getTranslation();
      dir.normalize();

      right = dir;
      right.cross(axe_y);
      right.normalize();

      up = dir;
      up.cross(right);
      up.normalize();

      right = dir;
      right.cross(up);
      right.normalize();

      {
        ofVec3f vtx = 1.2f * screenf * up;
        ofVec3f vty = 1.2f * screenf * right;
		ofColor flagged_color_w = curr == ROTATION_SCREEN ? select_color : unit_color_w;
        drawCircle(origin, vtx, vty, flag_rotation.screen ? flagged_color_w : convGrayscale(flagged_color_w));
      }

      {
        right = dir;
        right.cross(axe_x);
        right.normalize();
        front = right;
        front.cross(axe_x);
        front.normalize();
        ofVec3f vtx = screenf * right;
        ofVec3f vty = screenf * front;
		ofColor flagged_color_x = curr == ROTATION_X ? select_color : unit_color_x;
        drawCircle(origin, vtx, vty, flag_rotation.x ? flagged_color_x : convGrayscale(flagged_color_x));
      }

      {
        right = dir;
        right.cross(axe_y);
        right.normalize();
        front = right;
        front.cross(axe_y);
        front.normalize();
        ofVec3f vtx = screenf * right;
        ofVec3f vty = screenf * front;
		ofColor flagged_color_y = curr == ROTATION_Y ? select_color : unit_color_y;
        drawCircle(origin, vtx, vty, flag_rotation.y ? flagged_color_y : convGrayscale(flagged_color_y));
      }

      {
        right = dir;
        right.cross(axe_z);
        right.normalize();
        front = right;
        front.cross(axe_z);
        front.normalize();
        ofVec3f vtx = screenf * right;
        ofVec3f vty = screenf * front;
		ofColor flagged_color_z = curr == ROTATION_Z ? select_color : unit_color_z;
        drawCircle(origin, vtx, vty, flag_rotation.z ? flagged_color_z : convGrayscale(flagged_color_z));
      }

      if (type != ROTATION_NONE)
      {
        ofVec3f x = m_rotate_x;
        ofVec3f y = m_rotate_y;
        float angle = m_angleRad;
        x *= screenf;
        y *= screenf;
        switch (curr)
        {
		case (ROTATION_X) : {
			ofColor flagged_color_x = flag_rotation.x ? unit_color_x : convGrayscale(unit_color_x);
			drawCamembert(origin, x, y, -angle, flagged_color_x);
		}
		break;
		case (ROTATION_Y) : {
			ofColor flagged_color_y = flag_rotation.y ? unit_color_y : convGrayscale(unit_color_y);
			drawCamembert(origin, x, y, -angle, flagged_color_y);
		}
		break;
		case (ROTATION_Z) : {
			ofColor flagged_color_z = flag_rotation.z ? unit_color_z : convGrayscale(unit_color_z);
			drawCamembert(origin, x, y, -angle, flagged_color_z);
		}
		break;
		case (ROTATION_SCREEN) : {
			ofColor flagged_color_w = flag_rotation.screen ? unit_color_w : convGrayscale(unit_color_w);
			drawCamembert(origin, x, y, -angle, flagged_color_w);
		}
		break;
        }
      }
    }
    break;
    case (MANIPULATOR_TRANSLATION):
    {
      TRANSLATION_TYPE curr = m_currTranslationPredict;

	  ofColor flagged_color_y = (flag_translation.xz || (flag_translation.xyz && (curr == TRANSLATION_XYZ))) ? unit_color_y : convGrayscale(unit_color_y);
	  ofColor flagged_color_z = (flag_translation.xy || (flag_translation.xyz && (curr == TRANSLATION_XYZ))) ? unit_color_z : convGrayscale(unit_color_z);
	  ofColor flagged_color_x = (flag_translation.yz || (flag_translation.xyz && (curr == TRANSLATION_XYZ))) ? unit_color_x : convGrayscale(unit_color_x);

      drawQuad(origin, screenf_half, ( (curr == TRANSLATION_XZ) || (curr == TRANSLATION_XYZ) ), axe_x, axe_z, flagged_color_y);
      drawQuad(origin, screenf_half, ( (curr == TRANSLATION_XY) || (curr == TRANSLATION_XYZ) ), axe_x, axe_y, flagged_color_z);
      drawQuad(origin, screenf_half, ( (curr == TRANSLATION_YZ) || (curr == TRANSLATION_XYZ) ), axe_y, axe_z, flagged_color_x);

      axe_x *= screenf;
      axe_y *= screenf;
      axe_z *= screenf;

	  flagged_color_x = ((curr == TRANSLATION_X) || (curr == TRANSLATION_XYZ)) ? select_color : unit_color_x;
	  flagged_color_y = ((curr == TRANSLATION_Y) || (curr == TRANSLATION_XYZ)) ? select_color : unit_color_y;
	  flagged_color_z = ((curr == TRANSLATION_Z) || (curr == TRANSLATION_XYZ)) ? select_color : unit_color_z;
      drawAxis(origin, axe_x, axe_y, axe_z, 0.05f, 0.83f, (flag_translation.x || (flag_translation.xyz && (curr == TRANSLATION_XYZ))) ? flagged_color_x : convGrayscale(flagged_color_x));
      drawAxis(origin, axe_y, axe_x, axe_z, 0.05f, 0.83f, (flag_translation.y || (flag_translation.xyz && (curr == TRANSLATION_XYZ))) ? flagged_color_y : convGrayscale(flagged_color_y));
      drawAxis(origin, axe_z, axe_x, axe_y, 0.05f, 0.83f, (flag_translation.z || (flag_translation.xyz && (curr == TRANSLATION_XYZ))) ? flagged_color_z : convGrayscale(flagged_color_z));
    }
    break;
  }

  ofEnableDepthTest();

  ofPopStyle();
}

ofMatrix4x4 ofxManipulator::getMatrix()
{
  ofMatrix4x4 m;
  m.scale(m_ea.scale);
  m.rotate(m_ea.rotation);
  m.translate(m_ea.translation);
  return m;
}

ofVec3f ofxManipulator::getScale()
{
  return m_ea.scale;
}

ofQuaternion ofxManipulator::getRotation()
{
  return m_ea.rotation;
}

ofVec3f ofxManipulator::getTranslation()
{
  return m_ea.translation;
}

void ofxManipulator::setScale(ofVec3f scale)
{
  m_ea.scale = scale;
}

void ofxManipulator::setRotation(ofQuaternion rotation)
{
  m_ea.rotation = rotation;
}

void ofxManipulator::setTranslation(ofVec3f translation)
{
  m_ea.translation = translation;
}

void ofxManipulator::scale(ofVec3f scale)
{
  m_ea.scale *= scale;
}

void ofxManipulator::rotate(ofQuaternion rotation)
{
  m_ea.rotation *= rotation;
}

void ofxManipulator::translate(ofVec3f translation)
{
  m_ea.translation += translation;
}

void ofxManipulator::toggleScale()
{
  m_currManipulator = (m_currManipulator == MANIPULATOR_SCALE) ? MANIPULATOR_NONE : MANIPULATOR_SCALE;
}

void ofxManipulator::toggleRotation()
{
  m_currManipulator = (m_currManipulator == MANIPULATOR_ROTATION) ? MANIPULATOR_NONE : MANIPULATOR_ROTATION;
}

void ofxManipulator::toggleTranslation()
{
  m_currManipulator = (m_currManipulator == MANIPULATOR_TRANSLATION) ? MANIPULATOR_NONE : MANIPULATOR_TRANSLATION;
}

float ofxManipulator::getManipulatorScale()
{
  return m_manipulatorScale;
}

void ofxManipulator::setManipulatorScale(float scale)
{
  m_manipulatorScale = scale;
}

ofxManipulator::MANIPULATOR_TYPE ofxManipulator::getManipulatorType()
{
  return m_currManipulator;
}

void ofxManipulator::setManipulatorType(MANIPULATOR_TYPE type)
{
  m_currManipulator = type;
}

void ofxManipulator::setManipulatorColors(ofColor x, ofColor y, ofColor z, ofColor w, ofColor select)
{
  m_x_color = x;
  m_y_color = y;
  m_z_color = z;
  m_w_color = w;
  m_select_color = select;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void ofxManipulator::mouseMoved(ofMouseEventArgs &mouse)
{
  int x = mouse.x;
  int y = mouse.y;

  // Focus
  ofCamera cam;
  cam.setTransformMatrix(m_viewInverse);
  ofVec3f cur = cam.worldToScreen(m_ea.translation);
  float dist = cur.distance(mouse);
  cur.x = m_ea.id;
  cur.y = dist;
  // cur.z = cur.z;
  m_ea.dist = dist;
  m_ea.z = cur.z;

  // Change to onFocus
  if ((dist < m_onFocusThreshold * m_manipulatorScale) && !m_cameraMouseInputEnabled) {
	  m_focus = true;
	  if (m_auto_focus) {
		  if (m_currManipulator == MANIPULATOR_NONE) {
			  m_currManipulator = m_lastManipulator;
		  }
	  }
  }
  // OnFocus process
  if ((dist < m_offFocusThreshold * m_manipulatorScale) && !m_cameraMouseInputEnabled) {
	  if (m_focus) {
		  ofNotifyEvent(onFocus, m_ea);
	  }
  }
  // Change to outFocus
  else {
	  if (m_focus) {
		  ofNotifyEvent(outFocus, m_ea);
		  m_focus = false;
		  if (m_auto_focus) {
			  m_currManipulator = MANIPULATOR_NONE;
		  }
	  }
  }
  if (m_currManipulator != MANIPULATOR_NONE) {
	  m_lastManipulator = m_currManipulator;
  }

  switch (m_currManipulator)
  {
    case (MANIPULATOR_SCALE):
      getCurrScale(m_currScalePredict, x, y);
      break;
    case (MANIPULATOR_ROTATION):
      getCurrRotation(m_currRotationPredict, x, y);
      break;
    case (MANIPULATOR_TRANSLATION):
      getCurrTranslation(m_currTranslationPredict, x, y);
      break;
  }
}

void ofxManipulator::mousePressed(ofMouseEventArgs &mouse)
{
  int x = mouse.x;
  int y = mouse.y;
  int button = mouse.button;

  if(button != OF_MOUSE_BUTTON_LEFT)
    return;

  switch (m_currManipulator)
  {
    case (MANIPULATOR_SCALE):
      getCurrScale(m_currScale, x, y);
      break;
    case (MANIPULATOR_ROTATION):
      getCurrRotation(m_currRotation, x, y);
      break;
    case (MANIPULATOR_TRANSLATION):
      getCurrTranslation(m_currTranslation, x, y);
      break;
  }
}

void ofxManipulator::mouseDragged(ofMouseEventArgs &mouse)
{
  int x = mouse.x;
  int y = mouse.y;
  int button = mouse.button;

  if (button != OF_MOUSE_BUTTON_LEFT)
    return;

  switch (m_currManipulator)
  {
    case (MANIPULATOR_SCALE):
    {
      if (m_currScale == SCALE_NONE) {
        getCurrScale(m_currScalePredict, x, y);
        break;
      }

      ofVec3f ray_origin;
      ofVec3f ray_direction;
      ofVec3f intersection;

      createRay(x, y, ray_origin, ray_direction);
      intersectRay(m_plane, intersection, ray_origin, ray_direction);

      ofMatrix4x4 m;
      m.rotate(m_ea.rotation);
      ofVec3f axe_x = m.getRowAsVec3f(0);
      ofVec3f axe_y = m.getRowAsVec3f(1);
      ofVec3f axe_z = m.getRowAsVec3f(2);

      ofVec3f df;

      if (m_currScale == SCALE_XYZ)
      {
        float scale = x - m_lockedCursor_x;
        df = ofVec3f(scale);
      } else {
        df = intersection - m_lockedPoint;
        switch (m_currScale)
        {
          case SCALE_X:  df = ofVec3f(df.dot(axe_x),0,0); break;
          case SCALE_Y:  df = ofVec3f(0,df.dot(axe_y),0); break;
          case SCALE_Z:  df = ofVec3f(0,0,df.dot(axe_z)); break;
          case SCALE_XY: df = ofVec3f(df.dot(axe_x+axe_y),df.dot(axe_x+axe_y),0); break;
          case SCALE_XZ: df = ofVec3f(df.dot(axe_x+axe_z),0,df.dot(axe_x+axe_z)); break;
          case SCALE_YZ: df = ofVec3f(0,df.dot(axe_y+axe_z),df.dot(axe_y+axe_z)); break;
        }
      }

      float len = (sqrtf(df.x * df.x + df.y * df.y + df.z * df.z)) / 100.f;

      m_ea.scale = m_scaleSaved + (df.normalize() * len);

	  ofNotifyEvent(onScaleChange, m_ea);
    }
    break;
    case (MANIPULATOR_ROTATION):
    {
      if (m_currRotation == ROTATION_NONE) {
        getCurrRotation(m_currRotationPredict, x, y);
        break;
      }

      ofVec3f ray_origin;
      ofVec3f ray_direction;
      ofVec3f intersection;

      createRay(x, y, ray_origin, ray_direction);
      intersectRay(m_plane, intersection, ray_origin, ray_direction);

      ofVec3f df = intersection - m_ea.translation;
      df.normalize();

      float acos_angle = df.dot(m_lockedPoint);
      m_angleRad = (acos_angle < -0.99999f) || (acos_angle > 0.99999f) ? 0.0f : acos(acos_angle);

      if (df.dot(m_rotate_y) > 0)
        m_angleRad = -m_angleRad;

      ofMatrix4x4 m;
      m.rotate(m_rotationSaved);
      m.rotateRad(m_angleRad, m_axis.x, m_axis.y, m_axis.z);

      m_ea.rotation = m.getRotate();

	  ofNotifyEvent(onRotateChange, m_ea);
    }
    break;
    case (MANIPULATOR_TRANSLATION):
    {
      if (m_currTranslation == TRANSLATION_NONE) {
        getCurrTranslation(m_currTranslationPredict, x, y);
        break;
      }

      ofVec3f ray_origin;
      ofVec3f ray_direction;
      ofVec3f intersection;

      createRay(x, y, ray_origin, ray_direction);
      intersectRay(m_plane, intersection, ray_origin, ray_direction);

      ofMatrix4x4 m;
      m.rotate(m_ea.rotation);
      ofVec3f axe_x = m.getRowAsVec3f(0);
      ofVec3f axe_y = m.getRowAsVec3f(1);
      ofVec3f axe_z = m.getRowAsVec3f(2);

      if (m_currTranslation == TRANSLATION_XYZ)
      {
        ofCamera cam;
        cam.setTransformMatrix(m_viewInverse);
        ofVec3f mat_pos = m_translationSaved;
        ofVec3f cam_pos = cam.getPosition();
        ofVec3f cam_n = cam.getLookAtDir();

        ofVec3f v = mat_pos - cam_pos;
        float dist = v.dot(cam_n);
        ofVec3f mat_plane_pos = mat_pos - (cam_n * dist);

        ofVec3f n = mat_pos - mat_plane_pos;
        n.normalize();

        ofVec3f ray_end = cam.screenToWorld(ofVec3f(x + m_lockedCursor_x, y + m_lockedCursor_y, 1.0f));
        ofVec3f ray_dir = cam_pos - ray_end;
        ray_dir.normalize();

        float t = -((mat_pos - cam_pos).dot(n)) / n.dot(ray_dir);

        m_ea.translation = cam_pos - (ray_dir * t);
      } else {
        ofVec3f df = intersection - m_lockedPoint;
        switch (m_currTranslation)
        {
          case TRANSLATION_X:  df = ofVec3f(df.dot(axe_x),0,0); break;
          case TRANSLATION_Y:  df = ofVec3f(0,df.dot(axe_y),0); break;
          case TRANSLATION_Z:  df = ofVec3f(0,0,df.dot(axe_z)); break;
          case TRANSLATION_XY: df = ofVec3f(df.dot(axe_x),df.dot(axe_y),0); break;
          case TRANSLATION_XZ: df = ofVec3f(df.dot(axe_x),0,df.dot(axe_z)); break;
          case TRANSLATION_YZ: df = ofVec3f(0,df.dot(axe_y),df.dot(axe_z)); break;
        }
        ofVec3f vec = (df.x * axe_x) + (df.y * axe_y) + (df.z * axe_z);

        m_ea.translation = m_translationSaved + vec;
      }

	  ofNotifyEvent(onTranslateChange, m_ea);
    }
    break;
  }
}

void ofxManipulator::mouseReleased(ofMouseEventArgs &mouse)
{
  int x = mouse.x;
  int y = mouse.y;
  int button = mouse.button;

  if (button != OF_MOUSE_BUTTON_LEFT)
    return;

  m_currScale = SCALE_NONE;
  m_currRotation = ROTATION_NONE;
  m_currTranslation = TRANSLATION_NONE;
}

void ofxManipulator::mouseScrolled(ofMouseEventArgs &mouse)
{
	if (m_cameraMouseInputEnabled) return;
	if (m_auto_focus && !m_focus) return;

	int x = mouse.x;
	int y = mouse.y;
	int scroll_x = mouse.scrollX;
	int scroll_y = mouse.scrollY;

	// flag_check
	deque<MANIPULATOR_TYPE> deqc;
	deqc.push_back(MANIPULATOR_NONE);
	if (!flag_scale.none) deqc.push_back(MANIPULATOR_SCALE);
	if (!flag_rotation.none) deqc.push_back(MANIPULATOR_ROTATION);
	if (!flag_translation.none) deqc.push_back(MANIPULATOR_TRANSLATION);

	// init check
	int init = 0;
	if (m_currManipulator == MANIPULATOR_NONE) init = 0;
	else if (m_currManipulator == MANIPULATOR_SCALE) {
		if (!flag_scale.none) init = 1;
		else init = 0;
	}
	else if (m_currManipulator == MANIPULATOR_ROTATION) {
		if (!flag_rotation.none && !flag_scale.none) init = 2;
		else if (!flag_rotation.none && flag_scale.none) init = 1;
		else /* if (flag_rotation.none && flag_scale.none)*/ init = 0;
	}
	else if (m_currManipulator == MANIPULATOR_TRANSLATION) {
		if (!flag_translation.none && deqc.size() == 4) init = 3;
		else if (!flag_translation.none && deqc.size() == 2) init = 1;
		else if (!flag_translation.none && deqc.size() == 3) init = 2;
		else /* if(flag_translation.none && flag_rotation.none && flag_scale.none*/ init = 0;
	}

	// scroll_y
	if (scroll_y == 0) return;
	int desired = init + scroll_y;
	if (desired < 0) desired = deqc.size() - 1;
	else if (desired >= deqc.size()) desired = 0;
	m_currManipulator = deqc[desired];
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

float ofxManipulator::computeScreenFactor()
{
  ofMatrix4x4 viewproj = m_view * m_proj;
  ofVec3f origin = m_ea.translation;
  ofVec4f transform = ofVec4f(origin.x, origin.y, origin.z, 1.0f);
  transform = transform * viewproj;
  return transform.w * 0.2f * m_manipulatorScale;
}

void ofxManipulator::getCurrScale(SCALE_TYPE &type, unsigned int x, unsigned int y)
{
  m_lockedCursor_x = x;
  m_lockedCursor_y = y;
  m_scaleSaved = m_ea.scale;

  ofVec3f ray_origin;
  ofVec3f ray_direction;

  createRay(x, y, ray_origin, ray_direction);

  ofMatrix4x4 m;
  m.rotate(m_ea.rotation);
  m.translate(m_ea.translation);
  ofVec3f axe_x = m.getRowAsVec3f(0);
  ofVec3f axe_y = m.getRowAsVec3f(1);
  ofVec3f axe_z = m.getRowAsVec3f(2);

  ofVec3f df;

  df = raytrace(ray_origin, ray_direction, axe_y, m);

  if ((df.x < 0.1f) && (df.z < 0.1f) && (df.x > -0.1f) && (df.z > -0.1f)) { type = SCALE_XYZ; if (!flag_scale.xyz) type = SCALE_NONE; return; }
  else
  {
    df = raytrace(ray_origin, ray_direction, axe_z, m);

    if( (df.x < 0.1f) && (df.y < 0.1f) && (df.x > -0.1f) && (df.y > -0.1f) ) { type = SCALE_XYZ; if (!flag_scale.xyz) type = SCALE_NONE; return; }
    else
    {
      df = raytrace(ray_origin, ray_direction, axe_x, m);

      if( (df.y < 0.1f) && (df.z < 0.1f) && (df.y > -0.1f) && (df.z > -0.1f) ) { type = SCALE_XYZ; if (!flag_scale.xyz) type = SCALE_NONE; return; }
    }
  }

  df = raytrace(ray_origin, ray_direction, axe_y, m);

  if      ( (df.x >= 0.f) && (df.x <= 1.f) && (fabs(df.z) < 0.1f) )          { type = SCALE_X;  if (!flag_scale.x) type = SCALE_NONE; return; }
  else if ( (df.z >= 0.f) && (df.z <= 1.f) && (fabs(df.x) < 0.1f) )          { type = SCALE_Z;  if (!flag_scale.z) type = SCALE_NONE; return; }
  else if ( (df.x < 0.5f) && (df.z < 0.5f) && (df.x > 0.f) && (df.z > 0.f) ) { type = SCALE_XZ; if (!flag_scale.xz) type = SCALE_NONE; return; }
  else
  {
    df = raytrace(ray_origin, ray_direction, axe_z, m);

    if      ( (df.x >= 0.f) && (df.x <= 1.f) && (fabs(df.y) < 0.1f) )          { type = SCALE_X;  if (!flag_scale.x) type = SCALE_NONE; return; }
    else if ( (df.y >= 0.f) && (df.y <= 1.f) && (fabs(df.x) < 0.1f) )          { type = SCALE_Y;  if (!flag_scale.y) type = SCALE_NONE; return; }
    else if ( (df.x < 0.5f) && (df.y < 0.5f) && (df.x > 0.f) && (df.y > 0.f) ) { type = SCALE_XY; if (!flag_scale.xy) type = SCALE_NONE; return; }
    else
    {
      df = raytrace(ray_origin, ray_direction, axe_x, m);

      if      ( (df.y >= 0.f) && (df.y <= 1.f) && (fabs(df.z) < 0.1f) )          { type = SCALE_Y;  if (!flag_scale.y) type = SCALE_NONE; return; }
      else if ( (df.z >= 0.f) && (df.z <= 1.f) && (fabs(df.y) < 0.1f) )          { type = SCALE_Z;  if (!flag_scale.z) type = SCALE_NONE; return; }
      else if ( (df.y < 0.5f) && (df.z < 0.5f) && (df.y > 0.f) && (df.z > 0.f) ) { type = SCALE_YZ; if (!flag_scale.yz) type = SCALE_NONE; return; }
    }
  }

  type = SCALE_NONE;
}

void ofxManipulator::getCurrRotation(ROTATION_TYPE &type, unsigned int x, unsigned int y)
{
  ofVec3f ray_origin;
  ofVec3f ray_direction;

  createRay(x, y, ray_origin, ray_direction);

  ofMatrix4x4 m;
  m.rotate(m_ea.rotation);
  ofVec3f axe_x = m.getRowAsVec3f(0);
  ofVec3f axe_y = m.getRowAsVec3f(1);
  ofVec3f axe_z = m.getRowAsVec3f(2);

  if (checkRotationPlane(axe_x, 1.0f, ray_origin, ray_direction)) { type = ROTATION_X; if (!flag_rotation.x) type = ROTATION_NONE; return; }
  if (checkRotationPlane(axe_y, 1.0f, ray_origin, ray_direction)) { type = ROTATION_Y; if (!flag_rotation.y) type = ROTATION_NONE; return; }
  if (checkRotationPlane(axe_z, 1.0f, ray_origin, ray_direction)) { type = ROTATION_Z; if (!flag_rotation.z) type = ROTATION_NONE; return; }

  ofVec3f direction = m_ea.translation - m_viewInverse.getTranslation();
  direction.normalize();

  if (checkRotationPlane(direction, 1.2f, ray_origin, ray_direction)) { type = ROTATION_SCREEN; if (!flag_rotation.screen) type = ROTATION_NONE; return; }

  type = ROTATION_NONE;
}

void ofxManipulator::getCurrTranslation(TRANSLATION_TYPE &type, unsigned int x, unsigned int y)
{
  ofCamera cam;
  cam.setTransformMatrix(m_viewInverse);
  ofVec3f mat_screenCoord = cam.worldToScreen(m_translationSaved);
  m_lockedCursor_x = mat_screenCoord.x - x;
  m_lockedCursor_y = mat_screenCoord.y - y;
  m_translationSaved = m_ea.translation;

  ofVec3f ray_origin;
  ofVec3f ray_direction;

  createRay(x, y, ray_origin, ray_direction);

  ofMatrix4x4 m;
  m.rotate(m_ea.rotation);
  m.translate(m_ea.translation);
  ofVec3f axe_x = m.getRowAsVec3f(0);
  ofVec3f axe_y = m.getRowAsVec3f(1);
  ofVec3f axe_z = m.getRowAsVec3f(2);

  ofVec3f df;

  df = raytrace(ray_origin, ray_direction, axe_y, m);

  if ((df.x < 0.1f) && (df.z < 0.1f) && (df.x > -0.1f) && (df.z > -0.1f)) { type = TRANSLATION_XYZ; if (!flag_translation.xyz) type = TRANSLATION_NONE; return; }
  else
  {
    df = raytrace(ray_origin, ray_direction, axe_z, m);

    if( (df.x < 0.1f) && (df.y < 0.1f) && (df.x > -0.1f) && (df.y > -0.1f) ) { type = TRANSLATION_XYZ; if (!flag_translation.xyz) type = TRANSLATION_NONE; return; }
    else
    {
      df = raytrace(ray_origin, ray_direction, axe_x, m);

      if( (df.y < 0.1f) && (df.z < 0.1f) && (df.y > -0.1f) && (df.z > -0.1f) ) { type = TRANSLATION_XYZ; if (!flag_translation.xyz) type = TRANSLATION_NONE; return; }
    }
  }

  df = raytrace(ray_origin, ray_direction, axe_y, m);

  if      ( (df.x >= 0.f) && (df.x <= 1.f) && (fabs(df.z) < 0.1f) )          { type = TRANSLATION_X;  if (!flag_translation.x) type = TRANSLATION_NONE; return; }
  else if ( (df.z >= 0.f) && (df.z <= 1.f) && (fabs(df.x) < 0.1f) )          { type = TRANSLATION_Z;  if (!flag_translation.z) type = TRANSLATION_NONE; return; }
  else if ( (df.x < 0.5f) && (df.z < 0.5f) && (df.x > 0.f) && (df.z > 0.f) ) { type = TRANSLATION_XZ; if (!flag_translation.xz) type = TRANSLATION_NONE; return; }
  else
  {
    df = raytrace(ray_origin, ray_direction, axe_z, m);

    if      ( (df.x >= 0.f) && (df.x <= 1.f) && (fabs(df.y) < 0.1f) )          { type = TRANSLATION_X;  if (!flag_translation.x) type = TRANSLATION_NONE; return; }
    else if ( (df.y >= 0.f) && (df.y <= 1.f) && (fabs(df.x) < 0.1f) )          { type = TRANSLATION_Y;  if (!flag_translation.y) type = TRANSLATION_NONE; return; }
    else if ( (df.x < 0.5f) && (df.y < 0.5f) && (df.x > 0.f) && (df.y > 0.f) ) { type = TRANSLATION_XY; if (!flag_translation.xy) type = TRANSLATION_NONE; return; }
    else
    {
      df = raytrace(ray_origin, ray_direction, axe_x, m);

      if      ( (df.y >= 0.f) && (df.y <= 1.f) && (fabs(df.z) < 0.1f) )          { type = TRANSLATION_Y;  if (!flag_translation.y) type = TRANSLATION_NONE; return; }
      else if ( (df.z >= 0.f) && (df.z <= 1.f) && (fabs(df.y) < 0.1f) )          { type = TRANSLATION_Z;  if (!flag_translation.z) type = TRANSLATION_NONE; return; }
      else if ( (df.y < 0.5f) && (df.z < 0.5f) && (df.y > 0.f) && (df.z > 0.f) ) { type = TRANSLATION_YZ; if (!flag_translation.yz) type = TRANSLATION_NONE; return; }
    }
  }

  type = TRANSLATION_NONE;
}

void ofxManipulator::createRay(float x, float y, ofVec3f &ray_origin, ofVec3f &ray_dir)
{
  ofMatrix4x4 view_inverse = m_viewInverse;
  ofMatrix4x4 proj = m_proj;

  float w = ofGetWidth();
  float h = ofGetHeight();

  ofVec3f screen_space(
     (((2.0f * x) / w) - 1.0f) / proj._mat[0][0],
    -(((2.0f * y) / h) - 1.0f) / proj._mat[1][1],
    -1.0f
  );

  auto transform = [] (ofVec3f v, ofMatrix4x4 m)
  {
    ofVec3f vec;
    vec.x = v.x * m._mat[0][0] + v.y * m._mat[1][0] + v.z * m._mat[2][0];
    vec.y = v.x * m._mat[0][1] + v.y * m._mat[1][1] + v.z * m._mat[2][1];
    vec.z = v.x * m._mat[0][2] + v.y * m._mat[1][2] + v.z * m._mat[2][2];
    return vec;
  };

  ray_origin = view_inverse.getTranslation();

  ray_dir = transform(screen_space, view_inverse);
  ray_dir.normalize();
}

void ofxManipulator::intersectRay(ofVec4f &m_plane, ofVec3f &inter_point, ofVec3f position, ofVec3f direction)
{
  float den = m_plane.dot(direction);
  ofVec3f tmp = (m_plane * m_plane.w) - position;
  inter_point = position + (m_plane.dot(tmp) / den) * direction;
}

ofVec3f ofxManipulator::raytrace(ofVec3f ray_origin, ofVec3f ray_dir, ofVec3f normal, ofMatrix4x4 matrix)
{
  ofVec3f df;
  ofVec3f intersection;

  m_plane = createPlane(m_ea.translation, normal);
  intersectRay(m_plane, intersection, ray_origin, ray_dir);
  df = intersection * matrix.getInverse();
  m_lockedPoint = intersection;
  df /= m_screenFactor;

  return df;
}

ofVec4f ofxManipulator::createPlane(ofVec3f p, ofVec3f n)
{
  ofVec4f m_plane;
  ofVec3f normal;

  float length = 1.0f / sqrtf( (n.x * n.x) + (n.y * n.y) + (n.z * n.z) );

  normal = n * length;

  m_plane.x = normal.x;
  m_plane.y = normal.y;
  m_plane.z = normal.z;
  m_plane.w = normal.dot(p);

  return m_plane;
}

bool ofxManipulator::checkRotationPlane(ofVec3f normal, float factor, ofVec3f ray_origin, ofVec3f ray_direction)
{
  ofVec3f df;
  ofVec3f intersection;
  ofVec3f translation = m_ea.translation;

  m_plane = createPlane(translation, normal);
  intersectRay(m_plane, intersection, ray_origin, ray_direction);
  df = intersection - translation;
  df /= m_screenFactor;

  float dflen = (df.length() / factor);
  if ((dflen > 0.9f) && (dflen < 1.1f))
  {
    m_rotationSaved = m_ea.rotation;
    m_lockedPoint = df;
    m_lockedPoint.normalize();
    m_rotate_x = m_lockedPoint;
    m_rotate_y = m_lockedPoint;
    m_rotate_y.cross(normal);
    m_rotate_y.normalize();
    m_rotate_x *= factor;
    m_rotate_y *= factor;
    m_angleRad = 0.0f;
    m_axis = normal;
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
// DRAW FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void ofxManipulator::drawCircle(ofVec3f origin, ofVec3f vtx, ofVec3f vty, ofColor color)
{
  const int size = 50;
  vector<ofVec3f> vertices;
  vertices.resize(size);
  for (int i = 0; i < size; i++) {
    ofVec3f vt;
    vt  = vtx * cos((2 * PI / size) * i);
    vt += vty * sin((2 * PI / size) * i);
    vt += origin;
    vertices[i] = vt;
  }

  ofSetColor(color);
  ofMesh(OF_PRIMITIVE_LINE_LOOP, vertices).draw();
}

void ofxManipulator::drawAxis(ofVec3f origin, ofVec3f m_axis, ofVec3f vtx, ofVec3f vty, float fct, float fct2, ofColor color)
{
  vector<ofVec3f> cone_mesh;
  cone_mesh.resize(93);
  for (int i = 0, j = 0; i <= 30; i++) {
    ofVec3f pt;
    pt  = vtx * cos(((2 * PI) / 30.0f) * i) * fct;
    pt += vty * sin(((2 * PI) / 30.0f) * i) * fct;
    pt += m_axis * fct2;
    pt += origin;
    cone_mesh[j++] = pt;
    pt  = vtx * cos(((2 * PI) / 30.0f) * (i + 1)) * fct;
    pt += vty * sin(((2 * PI) / 30.0f) * (i + 1)) * fct;
    pt += m_axis * fct2;
    pt += origin;
    cone_mesh[j++] = pt;
    cone_mesh[j++] = origin + m_axis;
  }

  ofSetColor(color);
  ofMesh(OF_PRIMITIVE_LINES, {origin, origin + m_axis}).draw();
  ofMesh(OF_PRIMITIVE_TRIANGLE_FAN, cone_mesh).draw();
}

void ofxManipulator::drawScaleAxis(ofVec3f origin, ofVec3f m_axis, ofVec3f vtx, ofColor color)
{
  ofSetColor(color);
  ofMesh(OF_PRIMITIVE_LINES, {origin, origin + m_axis}).draw();

  float box_size = 0.1f * m_screenFactor;

  ofVec3f box_pos = origin;
  box_pos += m_axis.getNormalized() * (m_axis.length() - (box_size * 0.5f));

  ofNode box_node;
  box_node.lookAt(m_axis, vtx);
  box_node.setPosition(box_pos);
  ofPushMatrix();
  ofMultMatrix(box_node.getGlobalTransformMatrix());
  ofDrawBox(box_size);
  ofPopMatrix();
}

void ofxManipulator::drawCamembert(ofVec3f origin, ofVec3f vtx, ofVec3f vty, float ng, ofColor color)
{
  vector<ofVec3f> vertices;
  vertices.resize(52);
  int j = 0;
  vertices[j++] = origin;
  for (int i = 0; i <= 50; i++) {
    ofVec3f vt;
    vt  = vtx * cos((ng / 50) * i);
    vt += vty * sin((ng / 50) * i);
    vt += origin;
    vertices[j++] = vt;
  }

  ofSetColor(color, 255.0f * 0.5f);
  ofMesh(OF_PRIMITIVE_TRIANGLE_FAN, vertices).draw();
  ofMesh(OF_PRIMITIVE_LINE_LOOP, vertices).draw();
}

void ofxManipulator::drawQuad(ofVec3f origin, float size, bool is_selected, ofVec3f m_axis_u, ofVec3f m_axis_v, ofColor color)
{
  origin += ((m_axis_u + m_axis_v) * size) * 0.2f;
  m_axis_u *= 0.8f;
  m_axis_v *= 0.8f;

  vector<ofVec3f> pts;
  pts.resize(4);
  pts[0] = origin;
  pts[1] = origin + (m_axis_u * size);
  pts[2] = origin + (m_axis_u + m_axis_v) * size;
  pts[3] = origin + (m_axis_v * size);

  ofSetColor(color, 255.0f * (is_selected? 0.8f : 0.4f));
  ofMesh(OF_PRIMITIVE_TRIANGLE_FAN, pts).draw();
  ofSetColor(color, 255.0f * (is_selected? 1.0f : 0.8f));
  ofMesh(OF_PRIMITIVE_LINE_LOOP, pts).draw();
}

void ofxManipulator::drawTriangle(ofVec3f origin, float size, bool is_selected, ofVec3f m_axis_u, ofVec3f m_axis_v, ofColor color)
{
  origin += ((m_axis_u + m_axis_v) * size) * 0.2f;
  m_axis_u *= 0.8f;
  m_axis_v *= 0.8f;

  vector<ofVec3f> pts;
  pts.resize(3);
  pts[0] = origin;
  pts[1] = (m_axis_u * size) + origin;
  pts[2] = (m_axis_v * size) + origin;

  ofSetColor(color, 255.0f * (is_selected? 0.8f : 0.4f));
  ofMesh(OF_PRIMITIVE_TRIANGLES, pts).draw();
  ofSetColor(color, 255.0f * (is_selected? 1.0f : 0.8f));
  ofMesh(OF_PRIMITIVE_LINE_LOOP, pts).draw();
}