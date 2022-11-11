#pragma once

#include "ofMain.h"

class ofxManipulatorEventArgs
{
public:
	ofVec3f scale;
	ofQuaternion rotation;
	ofVec3f translation;

	int id;
	float dist;
	float z;
};

class ofxManipulator
{
  public:
    ofxManipulator();
   ~ofxManipulator();

    enum MANIPULATOR_TYPE
    {
      MANIPULATOR_NONE = 0,
      MANIPULATOR_SCALE = 1,
      MANIPULATOR_ROTATION = 2,
      MANIPULATOR_TRANSLATION = 3
    };

    void draw(ofEasyCam cam);

    ofMatrix4x4 getMatrix();

    ofVec3f getScale();
    ofQuaternion getRotation();
    ofVec3f getTranslation();

    void setScale(ofVec3f);
    void setRotation(ofQuaternion);
    void setTranslation(ofVec3f);

    void scale(ofVec3f);
    void rotate(ofQuaternion);
    void translate(ofVec3f);

    void toggleScale();
    void toggleRotation();
    void toggleTranslation();

    float getManipulatorScale();
    void setManipulatorScale(float scale);
    MANIPULATOR_TYPE getManipulatorType();
    void setManipulatorType(MANIPULATOR_TYPE type);
    void setManipulatorColors(ofColor x, ofColor y, ofColor z, ofColor w, ofColor select);

public:
	ofxManipulatorEventArgs m_ea;

	bool m_focus;
	bool m_auto_focus;
	bool m_cameraMouseInputEnabled;
	MANIPULATOR_TYPE m_lastManipulator;
	bool getAutoFocus() { return m_auto_focus; }
	void setAutoFocus(bool on) { m_auto_focus = on; }

	float getID() { return m_ea.id; }
	void setID(float v) { m_ea.id = v; }

	float m_onFocusThreshold;
	float getOnFocusThreshold() { return m_onFocusThreshold; }
	void setOnFocusThreshold(float t) { m_onFocusThreshold = t; }

	float m_offFocusThreshold;
	float getOffFocusThreshold() { return m_offFocusThreshold; }
	void setOffFocusThreshold(float t) { m_offFocusThreshold = t; }
	
	ofEvent<ofxManipulatorEventArgs&> onFocus, outFocus;
	ofEvent<ofxManipulatorEventArgs&> onScaleChange;
	ofEvent<ofxManipulatorEventArgs&> onTranslateChange;
	ofEvent<ofxManipulatorEventArgs&> onRotateChange;

  private:
	ofColor convGrayscale(ofColor rgb, float alpha = 255.0) {
		return ofColor(0.299f * (float)rgb.r + 0.587f * (float)rgb.g + 0.114f * (float)rgb.b, alpha);
	}

  protected:
    void mouseMoved(ofMouseEventArgs&);
    void mousePressed(ofMouseEventArgs&);
    void mouseDragged(ofMouseEventArgs&);
    void mouseReleased(ofMouseEventArgs&);
	void mouseScrolled(ofMouseEventArgs&);

  private:
    enum SCALE_TYPE
    {
      SCALE_NONE,
      SCALE_X,
      SCALE_Y,
      SCALE_Z,
      SCALE_XY,
      SCALE_XZ,
      SCALE_YZ,
      SCALE_XYZ
    };

    enum ROTATION_TYPE
    {
      ROTATION_NONE,
      ROTATION_X,
      ROTATION_Y,
      ROTATION_Z,
      ROTATION_SCREEN,
    };

    enum TRANSLATION_TYPE
    {
      TRANSLATION_NONE,
      TRANSLATION_X,
      TRANSLATION_Y,
      TRANSLATION_Z,
      TRANSLATION_XY,
      TRANSLATION_XZ,
      TRANSLATION_YZ,
      TRANSLATION_XYZ
    };

public:
	struct {
		ofParameter<bool> none = false;
		ofParameter<bool> x = true;
		ofParameter<bool> y = true;
		ofParameter<bool> z = true;
		ofParameter<bool> screen = true;
	} flag_rotation;

	struct {
		ofParameter<bool> none = false;
		ofParameter<bool> x = true;
		ofParameter<bool> y = true;
		ofParameter<bool> z = true;
		ofParameter<bool> xy = true;
		ofParameter<bool> xz = true;
		ofParameter<bool> yz = true;
		ofParameter<bool> xyz = true;
	} flag_scale;

	struct {
		ofParameter<bool> none = false;
		ofParameter<bool> x = true;
		ofParameter<bool> y = true;
		ofParameter<bool> z = true;
		ofParameter<bool> xy = true;
		ofParameter<bool> xz = true;
		ofParameter<bool> yz = true;
		ofParameter<bool> xyz = true;
	} flag_translation;

private:
    float computeScreenFactor();

    void getCurrScale(SCALE_TYPE &type, unsigned int x, unsigned int y);
    void getCurrRotation(ROTATION_TYPE &type, unsigned int x, unsigned int y);
    void getCurrTranslation(TRANSLATION_TYPE &type, unsigned int x, unsigned int y);

    void createRay(float x, float y, ofVec3f &ray_origin, ofVec3f &ray_direction);
    void intersectRay(ofVec4f &plane, ofVec3f &inter_point, ofVec3f position, ofVec3f direction);
    ofVec3f raytrace(ofVec3f ray_origin, ofVec3f ray_direction, ofVec3f normal, ofMatrix4x4 matrix);

    ofVec4f createPlane(ofVec3f p, ofVec3f n);
    bool checkRotationPlane(ofVec3f normal, float factor, ofVec3f ray_origin, ofVec3f ray_direction);

    void drawCircle(ofVec3f origin, ofVec3f vtx, ofVec3f vty, ofColor color);
    void drawAxis(ofVec3f origin, ofVec3f axis, ofVec3f vtx, ofVec3f vty, float fct, float fct2, ofColor color);
    void drawScaleAxis(ofVec3f origin, ofVec3f axis, ofVec3f vtx, ofColor color);
    void drawCamembert(ofVec3f origin, ofVec3f vtx, ofVec3f vty, float ng, ofColor color);
    void drawQuad(ofVec3f origin, float size, bool is_selected, ofVec3f axis_u, ofVec3f axis_v, ofColor color);
    void drawTriangle(ofVec3f origin, float size, bool is_selected, ofVec3f axis_u, ofVec3f axis_v, ofColor color);

    SCALE_TYPE m_currScale;
    SCALE_TYPE m_currScalePredict;

    ROTATION_TYPE m_currRotation;
    ROTATION_TYPE m_currRotationPredict;

    TRANSLATION_TYPE m_currTranslation;
    TRANSLATION_TYPE m_currTranslationPredict;

    MANIPULATOR_TYPE m_currManipulator;

    float m_angleRad;
    float m_screenFactor;
    float m_manipulatorScale;
    float m_lockedCursor_x;
    float m_lockedCursor_y;

    ofVec3f m_lockedPoint;
    ofVec3f m_axis;
    ofVec3f m_rotate_x;
    ofVec3f m_rotate_y;

    //ofVec3f m_scale;         // moved to ofxManipulatorEventArgs
    ofVec3f m_scaleSaved;
    //ofVec3f m_translation;   // moved to ofxManipulatorEventArgs
    ofVec3f m_translationSaved;
    //ofQuaternion m_rotation; // moved to ofxManipulatorEventArgs
    ofQuaternion m_rotationSaved;

    ofColor m_x_color;
    ofColor m_y_color;
    ofColor m_z_color;
    ofColor m_w_color;
    ofColor m_select_color;

    ofVec4f m_plane;

    ofMatrix4x4 m_view;
    ofMatrix4x4 m_viewInverse;
    ofMatrix4x4 m_proj;
};