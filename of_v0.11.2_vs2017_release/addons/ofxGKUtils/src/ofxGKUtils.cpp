#include "ofxGKUtils.h"

using namespace std;
//-------------------------------------------------------HELPER_DEFAULT-------------------------------------------------------//
void ofxGKUtils::setup(stringstream* _ssGlobalLog) {
	ofSetVerticalSync(true);
	ofSetFrameRate(40);
	ofNoFill();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glLineWidth(1);
	glPointSize(1);
	ofEnableAlphaBlending();
	//glEnable(GL_BLEND);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE);
	ssLog = _ssGlobalLog;

	margin = 8;
}

void ofxGKUtils::setCam(ofEasyCam* _cam) {
	_cam->removeAllInteractions();
	//_ezCam->setPosition(0, 0, 0);
	//_ezCam->lookAt(glm::vec3(0, 0, 0),glm::vec3(0,0,1));
	//_ezCam->enableOrtho();
	//_ezCam->disableMouseInput();
	//_ezCam->enableMouseInput();
	//_ezCam->enableMouseMiddleButton();
	_cam->setNearClip(0.1);
	_cam->setFarClip(100000);
	_cam->addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_RIGHT, OF_KEY_SHIFT);
	_cam->setScrollFlip(true); //you need to customize your ofEasyCam
	_cam->addInteraction(ofEasyCam::TRANSFORM_ROTATE, OF_MOUSE_BUTTON_RIGHT);
}

void ofxGKUtils::defaultUpdate(ofEasyCam* _cam, unsigned long int* _currentFrame, float* _time) {
	*_currentFrame += 1;
	*_time = ofGetElapsedTimef();

	//_cam->lookAt(_cam->getPosition() + _cam->getLookAtDir(), _cam->getUpAxis());
	//_cam->lookAt(_cam->getTarget(), _cam->getUpAxis());
	ofBackground(10);
	ofNoFill();
	//fbo.begin();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glLineWidth(1);
	glPointSize(1);
	//fbo.end();
}

glm::vec2 ofxGKUtils::getPosLayout4x4(const int& _index) {
	if (_index == 0) return glm::vec2(0,0);
	if (_index == 1) return glm::vec2(0, ofGetHeight() * 0.25);
	if (_index == 2) return glm::vec2(0, ofGetHeight() * 0.50);
	if (_index == 3) return glm::vec2(0, ofGetHeight() * 0.75);
	if (_index == 4) return glm::vec2(ofGetWidth() * 0.25, 0);
	if (_index == 5) return glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.25);
	if (_index == 6) return glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.50);
	if (_index == 7) return glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.75);
	if (_index == 8) return glm::vec2(ofGetWidth() * 0.50, 0);
	if (_index == 9) return glm::vec2(ofGetWidth() * 0.50, ofGetHeight() * 0.25);
	if (_index == 10) return glm::vec2(ofGetWidth() * 0.50, ofGetHeight() * 0.50);
	if (_index == 11) return glm::vec2(ofGetWidth() * 0.50, ofGetHeight() * 0.75);
	if (_index == 12) return glm::vec2(ofGetWidth() * 0.75, 0);
	if (_index == 13) return glm::vec2(ofGetWidth() * 0.75, ofGetHeight() * 0.25);
	if (_index == 14) return glm::vec2(ofGetWidth() * 0.75, ofGetHeight() * 0.50);
	if (_index == 15) return glm::vec2(ofGetWidth() * 0.75, ofGetHeight() * 0.75);
}

//-------------------------------------------------------HELPER_GUI-------------------------------------------------------//
glm::vec3 ofxGKUtils::myGUIPos(const int& _indexPos) {
	glm::vec2 _pos = getPosLayout4x4(_indexPos);
	_pos.x += margin;
	return glm::vec3(_pos, 0);
}

float ofxGKUtils::myGUIWidth() {
	float _width = ofGetWidth() * 0.25 - margin - margin;
	return _width;
}

void ofxGKUtils::setGUI(ofxGuiGroup& _gui) {
	_gui.setup();
	_gui.setPosition(myGUIPos(13));
	_gui.setSize(myGUIWidth(), 0);
	_gui.setWidthElements(myGUIWidth() * .98);

	_gui.setDefaultBackgroundColor(ofColor(0));
	_gui.setBackgroundColor(ofColor(0));
	_gui.setDefaultHeaderBackgroundColor(ofColor(0));
	_gui.setHeaderBackgroundColor(ofColor(0));
	_gui.setDefaultBorderColor(ofColor(30));
	_gui.setBorderColor(ofColor(30));
	_gui.setDefaultFillColor(ofColor(60));
	_gui.setFillColor(ofColor(60));
}

void ofxGKUtils::resizeGUI(ofxGuiGroup& _gui) {
	_gui.setPosition(myGUIPos(13));
	_gui.setSize(myGUIWidth(), 0);
	_gui.setWidthElements(myGUIWidth() * .98);
}

void ofxGKUtils::setGraphGUI(const int& _indexPos, const glm::vec2& _size, const glm::vec2& _originalSize) {

	glm::vec2 _pos = getPosLayout4x4(_indexPos);
	if (_indexPos < 4) {
		_pos.x += 60;
	}
	else {
		_pos.x += margin;
	};
	const ofColor _boarderColor = ofColor(50);
	const ofColor _backgroundColor = ofColor(0);
	const ofRectangle _r = ofRectangle(_pos, _pos + _size);
	ofFill();
	ofSetColor(_backgroundColor);
	ofDrawRectangle(_r);
	ofNoFill();
	ofSetLineWidth(2);
	ofSetColor(_boarderColor);
	ofDrawRectangle(_r);
	ofSetLineWidth(1);
	//axis
	ofPushMatrix();
	ofTranslate(_pos + _size / 2); //translate to graphcenter          
	glLineWidth(1);
	glColor4f(1, 0, 0, 0.5); //x= red
	glBegin(GL_LINES);
	glVertex2f(-_size.x / 2, 0);
	glVertex2f(_size.x / 2, 0);
	glEnd();
	glColor4f(0, 0, 1, 0.5); //z = blue
	glBegin(GL_LINES);
	glVertex2f(0, -_size.y / 2);
	glVertex2f(0, _size.y / 2);
	glEnd();
	ofPopMatrix();
}

void ofxGKUtils::drawMouseOnGraphGUI(const int& _indexPos, const glm::vec2& _size, const glm::vec2& _originalSize, glm::vec2* _mouseOnWorldPlane) {
	glm::vec2 _pos = getPosLayout4x4(_indexPos);
	if (_indexPos < 4) {
		_pos.x += 60;
	}
	else {
		_pos.x += margin;
	};	
	//mouse
	glm::vec2 _mouseOnGraph = glm::vec2(ofGetMouseX(), ofGetMouseY());
	glm::vec2 graphCenter = glm::vec2(_pos + _size / 2);
	_mouseOnGraph = _mouseOnGraph - graphCenter;
	ofPushMatrix();
	ofTranslate(_pos + _size / 2);
	drawFoundCenterTo2D(glm::vec3(_mouseOnGraph, 0), _size, glm::vec3(0, 0, 1));
	ofPopMatrix();
	//mouseToWorld
	if (_mouseOnGraph.x<_size.x / 2 && _mouseOnGraph.x>-_size.x / 2 && _mouseOnGraph.y<_size.y / 2 && _mouseOnGraph.y>-_size.y / 2) {
		*_mouseOnWorldPlane = _mouseOnGraph / _size * _originalSize;
	}
}

void ofxGKUtils::drawEachDataOnGraphGUI(const int& _indexPos, const glm::vec2& _size, const glm::vec2& _originalSize, glm::vec3& _data, const glm::vec3& _normalOfData) {
	glm::vec2 _pos = getPosLayout4x4(_indexPos);
	if (_indexPos < 4) {
		_pos.x += 60;
	}
	else {
		_pos.x += margin;
	};
	glm::vec3 _mappedCenter;
	if (_normalOfData.y == 1) _mappedCenter = _data / glm::vec3(_originalSize.x, 1, _originalSize.y) * glm::vec3(_size.x, 1, _size.y);
	if (_normalOfData.z == 1) _mappedCenter = _data / glm::vec3(_originalSize.x, _originalSize.y, 1) * glm::vec3(_size.x, _size.y, 1);
	ofPushMatrix();
	ofTranslate(_pos + _size / 2); //translate to graphcenter  
	drawFoundCenterTo2D(_mappedCenter, _size, _normalOfData);
	ofPopMatrix();
}


//-------------------------------------------------------HELPER_2D-------------------------------------------------------//

void ofxGKUtils::drawInfo(const stringstream& _ss, const int& _indexPos, const ofTrueTypeFont& _font, const int& _fontSize) {
	//TrueTypeFont
	glm::vec2 _pos = getPosLayout4x4(_indexPos);
	if (_indexPos < 4) {
		_pos.x += 60;
	}
	else {
		_pos.x += margin;
	};
	_pos.y += _fontSize;
	glColor3f(1, 1, 1);
	_font.drawString(_ss.str().c_str(), _pos.x, _pos.y);
}

void ofxGKUtils::drawInfo(const stringstream& _ss, const int& _indexPos) {
	//Bitmap
	//Width : 8pt , Height : 11pt
	glColor3f(1, 1, 1);
	glm::vec2 _pos = getPosLayout4x4(_indexPos);
	if (_indexPos < 4) {
		_pos.x += 60;
	}else{
		_pos.x += margin;
	};
	_pos.y += 11;

	//ofDrawBitmapStringHighlight(_ss.str().c_str(), _pos, ofColor(0), ofColor(255));
	ofDrawBitmapString(_ss.str().c_str(), _pos);
}

void ofxGKUtils::drawInfo(const stringstream& _ss, const glm::vec2& _xyPos) {
	//Bitmap
	//Width : 8pt , Height : 11pt
	glColor3f(1, 1, 1);
	glm::vec2 _pos = _xyPos;
	_pos.y += 11;

	//ofDrawBitmapStringHighlight(_ss.str().c_str(), _pos, ofColor(0), ofColor(255));
	ofDrawBitmapString(_ss.str().c_str(), _pos);
}

void ofxGKUtils::drawGrid() {
	const int _size = 10;
	ofNoFill();
	ofSetColor(50);
	ofDrawLine(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() / 2);
	ofDrawLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());

	ofNoFill();
	ofSetColor(50);
	ofDrawRectangle(margin, margin, ofGetWidth() - margin * 2, ofGetHeight() - margin * 2);

	ofFill();
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	for (int y = -1; y < 2; y++) {
		for (int x = -1; x < 2; x++) {
			if (y != 0) {
				if (x != 0) {
					drawCross(x * ofGetWidth() / 4, y * ofGetHeight() / 4, _size);
				}
			}
		}
	}
	ofPopMatrix();
}

void ofxGKUtils::drawCross(const int& _x, const int& _y, const int& _size) {
	glLineWidth(1);
	ofPushMatrix();
	ofTranslate(_x, _y);
	glBegin(GL_LINES);
	glVertex2f(-_size / 2, 0);
	glVertex2f(_size / 2, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, -_size / 2);
	glVertex2f(0, _size / 2);
	glEnd();
	ofPopMatrix();
}

#pragma mark -HELPER_3D
//-------------------------------------------------------HELPER_3D-------------------------------------------------------//

void ofxGKUtils::draw3DAxis() {
	const int _size = 1000;
	const float _alpha = 0.5;
	glLineWidth(2);
	glColor4f(1, 0, 0, _alpha);//x = red
	glBegin(GL_LINES);
	glVertex3f(-_size / 2, 0, 0);
	glVertex3f(_size / 2, 0, 0);
	glEnd();
	glColor4f(0, 1, 0, _alpha);//y = green
	glBegin(GL_LINES);
	glVertex3f(0, -_size / 2, 0);
	glVertex3f(0, _size / 2, 0);
	glColor4f(0, 0, 1, _alpha);//z = blue
	glBegin(GL_LINES);
	glVertex3f(0, 0, -_size / 2);
	glVertex3f(0, 0, _size / 2);
	glEnd();
}

//default size = 1000;
void ofxGKUtils::draw3DAxis(const float& _size,const float& _lineWidth, const float& _alpha) {
	glLineWidth(_lineWidth);
	glColor4f(1, 0, 0, _alpha);//x = red
	glBegin(GL_LINES);
	glVertex3f(-_size / 2, 0, 0);
	glVertex3f(_size / 2, 0, 0);
	glEnd();
	glColor4f(0, 1, 0, _alpha);//y = green
	glBegin(GL_LINES);
	glVertex3f(0, -_size / 2, 0);
	glVertex3f(0, _size / 2, 0);
	glColor4f(0, 0, 1, _alpha);//z = blue
	glBegin(GL_LINES);
	glVertex3f(0, 0, -_size / 2);
	glVertex3f(0, 0, _size / 2);
	glEnd();
}

void ofxGKUtils::draw3DCADGrid(const float& _sizeUnit, const int& _numUnit, const glm::vec3& _normalPlaneToDraw, const float& _lineWidth, const glm::vec4& _col) {

	glLineWidth(_lineWidth);
	glColor4f(_col.r, _col.g, _col.b, _col.a);
	if (_normalPlaneToDraw.z == 1) {		
		//hori
		for (int i = 0; i < _numUnit+1; i++) {
			glBegin(GL_LINES);
			glVertex3f(-_sizeUnit * _numUnit / 2,0, -_sizeUnit * _numUnit / 2 + _sizeUnit * i);
			glVertex3f(+_sizeUnit * _numUnit / 2,0, -_sizeUnit * _numUnit / 2 + _sizeUnit * i);
			glEnd();
		}
		//vert
		for (int i = 0; i < _numUnit+1; i++) {
			glBegin(GL_LINES);
			glVertex3f(-_sizeUnit * _numUnit / 2 + _sizeUnit * i,0, -_sizeUnit * _numUnit / 2);
			glVertex3f(-_sizeUnit * _numUnit / 2 + _sizeUnit * i,0, _sizeUnit * _numUnit / 2);
			glEnd();
		}
	}
	if (_normalPlaneToDraw.y == 1) {
		//hori
		for (int i = 0; i < _numUnit+1; i++) {
			glBegin(GL_LINES);
			glVertex3f(-_sizeUnit * _numUnit / 2,0, -_sizeUnit * _numUnit / 2 + _sizeUnit * i);
			glVertex3f(+_sizeUnit * _numUnit / 2,0, -_sizeUnit * _numUnit / 2 + _sizeUnit * i);
			glEnd();
		}
		//vert
		for (int i = 0; i < _numUnit+1; i++) {
			glBegin(GL_LINES);
			glVertex3f(-_sizeUnit * _numUnit / 2 + _sizeUnit * i,0, -_sizeUnit * _numUnit / 2);
			glVertex3f(-_sizeUnit * _numUnit / 2 + _sizeUnit * i,0, _sizeUnit * _numUnit / 2);
			glEnd();
		}
	}
}

float* ofxGKUtils::getBoundingBox(const ofMesh& _mesh) {
	float
		min_x, max_x,
		min_y, max_y,
		min_z, max_z;
	min_x = max_x = _mesh.getVertex(0).x;
	min_y = max_y = _mesh.getVertex(0).y;
	min_z = max_z = _mesh.getVertex(0).z;
	for (int i = 0; i < _mesh.getNumVertices(); i++) {
		if (_mesh.getVertex(i).x < min_x) min_x = _mesh.getVertex(i).x;
		if (_mesh.getVertex(i).x > max_x) max_x = _mesh.getVertex(i).x;
		if (_mesh.getVertex(i).y < min_y) min_y = _mesh.getVertex(i).y;
		if (_mesh.getVertex(i).y > max_y) max_y = _mesh.getVertex(i).y;
		if (_mesh.getVertex(i).z < min_z) min_z = _mesh.getVertex(i).z;
		if (_mesh.getVertex(i).z > max_z) max_z = _mesh.getVertex(i).z;
	}
	float result[] = { min_x, max_x, min_y, max_y, min_z, max_z };
	return result;
	//glm::vec3 size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z);
	//glm::vec3 center = glm::vec3((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);
}

float* ofxGKUtils::getBoundingBox(const ofMesh& _mesh,const glm::vec3& _planeNormal) {
	float
		min_x, max_x,
		min_y, max_y,
		min_z, max_z;
	min_x = max_x = _planeNormal.x - _mesh.getVertex(0).x;
	min_y = max_y = _planeNormal.y - _mesh.getVertex(0).y;
	min_z = max_z = _planeNormal.z - _mesh.getVertex(0).z;
	for (int i = 0; i < _mesh.getNumVertices(); i++) {
		float _theta = glm::angle(glm::normalize(_planeNormal), glm::vec3(0, 1, 0));
		glm::vec3 _orientedVertexPos = _mesh.getVertex(i)/cos(_theta);
		if (_orientedVertexPos.x < min_x) min_x = _orientedVertexPos.x;
		if (_orientedVertexPos.x > max_x) max_x = _orientedVertexPos.x;
		if (_orientedVertexPos.y < min_y) min_y = _orientedVertexPos.y;
		if (_orientedVertexPos.y > max_y) max_y = _orientedVertexPos.y;
		if (_orientedVertexPos.z < min_z) min_z = _orientedVertexPos.z;
		if (_orientedVertexPos.z > max_z) max_z = _orientedVertexPos.z;
	}
	float result[] = { min_x, max_x, min_y, max_y, min_z, max_z };
	return result;
	//glm::vec3 size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z);
	//glm::vec3 center = glm::vec3((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);
}

void ofxGKUtils::drawFoundCenterTo3D(const glm::vec3& _pos, glm::vec2 _size, const glm::vec3& _normalPlaneToDraw) {
	glColor4f(1, 0, 1, 0.7);
	if (_normalPlaneToDraw.z == 1) {
		if (_pos.x<_size.x / 2 && _pos.x>-_size.x / 2 && _pos.y<_size.y / 2 && _pos.y>-_size.y / 2) {
			glLineWidth(1);
			glColor4f(1, 0, 1, 0.7);
			glBegin(GL_LINES);
			glVertex3f(_pos.x, -_size.y / 2, 0);
			glVertex3f(_pos.x, _size.y / 2, 0);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(-_size.x / 2, _pos.y, 0);
			glVertex3f(_size.x / 2, _pos.y, 0);
			glEnd();

			glPointSize(4);
			glBegin(GL_POINTS);
			glVertex3f(_pos.x, -_size.y / 2, 0);
			glVertex3f(_pos.x, _size.y / 2, 0);
			glVertex3f(-_size.x / 2, _pos.y, 0);
			glVertex3f(_size.x / 2, _pos.y, 0);
			glVertex3f(_pos.x, _pos.y, 0);
			glEnd();
		}
	}
	if (_normalPlaneToDraw.y == 1) {
		if (_pos.x<_size.x / 2 && _pos.x>-_size.x / 2 && _pos.z<_size.y / 2 && _pos.z>-_size.y / 2) {
			glLineWidth(1);
			glBegin(GL_LINES);
			glVertex3f(_pos.x, 0, -_size.y / 2);
			glVertex3f(_pos.x, 0, _size.y / 2);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(-_size.x / 2, 0, _pos.z);
			glVertex3f(_size.x / 2, 0, _pos.z);
			glEnd();

			glPointSize(4);
			glBegin(GL_POINTS);
			glVertex3f(_pos.x, 0, -_size.y / 2);
			glVertex3f(_pos.x, 0, _size.y / 2);
			glVertex3f(-_size.x / 2, 0, _pos.z);
			glVertex3f(_size.x / 2, 0, _pos.z);
			glVertex3f(_pos.x, 0, _pos.z);
			glEnd();
		}
	}
}

void ofxGKUtils::drawFoundCenterTo2D(const glm::vec3& _pos, glm::vec2 _size, const glm::vec3& _normalOfData) {
	glColor4f(1, 0, 1, 0.7);
	if (_normalOfData.z == 1) {
		if (_pos.x<_size.x / 2 && _pos.x>-_size.x / 2 && _pos.y<_size.y / 2 && _pos.y>-_size.y / 2) {
			glLineWidth(1);
			glColor4f(1, 0, 1, 0.7);
			glBegin(GL_LINES);
			glVertex3f(_pos.x, -_size.y / 2, 0);
			glVertex3f(_pos.x, _size.y / 2, 0);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(-_size.x / 2, _pos.y, 0);
			glVertex3f(_size.x / 2, _pos.y, 0);
			glEnd();

			glPointSize(4);
			glBegin(GL_POINTS);
			glVertex3f(_pos.x, -_size.y / 2, 0);
			glVertex3f(_pos.x, _size.y / 2, 0);
			glVertex3f(-_size.x / 2, _pos.y, 0);
			glVertex3f(_size.x / 2, _pos.y, 0);
			glVertex3f(_pos.x, _pos.y, 0);
			glEnd();
		}
	}
	if (_normalOfData.y == 1) {
		if (_pos.x<_size.x / 2 && _pos.x>-_size.x / 2 && _pos.z<_size.y / 2 && _pos.z>-_size.y / 2) {
			glLineWidth(1);
			glColor4f(1, 0, 1, 0.7);
			glBegin(GL_LINES);
			glVertex3f(_pos.x, -_size.y / 2, 0);
			glVertex3f(_pos.x, _size.y / 2, 0);
			glEnd();
			glBegin(GL_LINES);
			glVertex3f(-_size.x / 2, _pos.z, 0);
			glVertex3f(_size.x / 2, _pos.z, 0);
			glEnd();

			glPointSize(4);
			glBegin(GL_POINTS);
			glVertex3f(_pos.x, -_size.y / 2, 0);
			glVertex3f(_pos.x, _size.y / 2, 0);
			glVertex3f(-_size.x / 2, _pos.z, 0);
			glVertex3f(_size.x / 2, _pos.z, 0);
			glVertex3f(_pos.x, _pos.z, 0);
			glEnd();
		}
	}
}

ofMesh ofxGKUtils::getModifiedMesh(ofMesh* _mesh, const ofNode& _modifyInfo) {
	auto mat = _modifyInfo.getGlobalTransformMatrix();
	for (auto& v : _mesh->getVertices()) {
		v = glm::vec3(mat * glm::vec4(v, 1));
	}
	auto mat2 = _modifyInfo.getOrientationQuat();
	for (auto& v : _mesh->getNormals()) {
		v = glm::vec3(mat2 * glm::vec4(v, 1));
	}
	return *_mesh;
}

vector<glm::vec3> ofxGKUtils::getModifiedVertices(vector<glm::vec3>* _vertices,const ofNode& _modifyInfo) {
	auto mat = _modifyInfo.getGlobalTransformMatrix();
	for (auto& v : *_vertices) {
		v = glm::vec3(mat * glm::vec4(v, 1));
	}
	/*
	auto mat2 = _modifyInfo.getOrientationQuat();
	for (auto& v : *_normals) {
		v = glm::vec3(mat2 * glm::vec4(v, 1));
	}
	*/
	return *_vertices;
}

#pragma mark -save
//-------------------------------------------------------HELPER_SAVE-------------------------------------------------------//

void ofxGKUtils::saveVideo(const float& _currentFrame) {
	string _fileName = makeFileName("./screenShotForMovie/", ".png").str().c_str();
	ofImage _imgToSave;
	_imgToSave.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
}

stringstream ofxGKUtils::makeFileName(const string& _folderName, const string& _fileType) {
	stringstream _ss;
	_ss << _folderName;
	_ss << ofGetYear();
	_ss << setfill('0') << setw(2) << ofGetMonth();
	_ss << setfill('0') << setw(2) << ofGetDay() << "-";
	_ss << setfill('0') << setw(2) << ofGetHours();
	_ss << setfill('0') << setw(2) << ofGetMinutes();
	_ss << setfill('0') << setw(2) << ofGetSeconds();
	_ss << _fileType;
	return _ss;
}

void ofxGKUtils::saveImage() {
	string _fileName = makeFileName("./screenShot/", ".png").str().c_str();
	ofImage _imgToSave;
	_imgToSave.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
	*ssLog << "EXPORTED SCREEN : " + _fileName << std::endl;
}

void ofxGKUtils::saveFBOtoImage(ofFbo* _fbo) {
	string _fileName = makeFileName("./fboShot/", ".png").str().c_str();
	ofPixels _pixels;
	_fbo->readToPixels(_pixels);
	ofImage _imgToSave;
	_imgToSave.setFromPixels(_pixels);
	_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
	*ssLog << "EXPORTED FBO : " + _fileName << std::endl;
}

void ofxGKUtils::saveMesh(ofMesh& _mesh, const float& _scaleFactor) {
	string _fileName = makeFileName("./meshExport/", ".ply").str().c_str();
	ofMesh _meshToSave = _mesh;
	glm::vec3 _centroid = _mesh.getCentroid();
	*ssLog << _centroid << endl;
	for (int i = 0; i < _mesh.getNumVertices(); i++) {
		_meshToSave.getVertices()[i] = (_mesh.getVertex(i) - _centroid) * _scaleFactor;;
	}
	_meshToSave.save(_fileName);
	*ssLog << "EXPORTED MESH : " + _fileName << endl;
	//free(&_meshToSave);
}