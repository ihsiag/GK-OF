#include "ofxGKUtils.h"

using namespace std;
//-------------------------------------------------------HELPER_DEFAULT-------------------------------------------------------//
void ofxGKUtils::setup(stringstream* _ssGlobalLog) {
	ofSetVerticalSync(false);
	ofSetFrameRate(0);
	ofNoFill();
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glLineWidth(1);
	glPointSize(1);
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	ofEnableAntiAliasing();
	//glEnable(GL_BLEND);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE);
	ssLog = _ssGlobalLog;

	margin = 8;
}

void ofxGKUtils::setup(stringstream* _ssGlobalLog ,const int& _frameRate) {
	ofSetVerticalSync(false);
	ofSetFrameRate(_frameRate);
	ofNoFill();
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glLineWidth(1);
	glPointSize(1);
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	ofEnableAntiAliasing();
	ofSetCircleResolution(60);
	//glEnable(GL_BLEND);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE);
	ssLog = _ssGlobalLog;

	margin = 8;
}

void ofxGKUtils::setup(const int& _frameRate) {
	ofSetVerticalSync(false);
	ofSetFrameRate(_frameRate);
	ofNoFill();
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glLineWidth(1);
	glPointSize(1);
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	ofEnableAntiAliasing();
	ofSetCircleResolution(60);
	//glEnable(GL_BLEND);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE);
	margin = 8;
};

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

void ofxGKUtils::scrollCamera(ofEasyCam* _cam,const int& _scrollY) {
	int scrollScale = 30;
	if (_cam->getPosition().y > -1) {
		_cam->move(0, -1 * _scrollY * scrollScale, 0);
	}
	if (_cam->getPosition().y < 0) {
		_cam->setPosition(_cam->getPosition().x, 0, _cam->getPosition().z);
	}
}

void ofxGKUtils::defaultUpdate(unsigned long int* _currentFrame, float* _time) {
	*_currentFrame += 1;
	*_time = ofGetElapsedTimef();

	ofBackground(10);
	ofNoFill();
	//fbo.begin();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glColor4f(0, 0, 0, 1);
	glLineWidth(1);
	glPointSize(1);
	//fbo.end();
}

void ofxGKUtils::defaultUpdate(unsigned long int* _currentFrame, float* _time, const glm::vec4& _col) {
	*_currentFrame += 1;
	*_time = ofGetElapsedTimef();

	ofBackground(_col.r * 255, _col.g * 255, _col.b * 255);
	ofNoFill();
	//fbo.begin();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glLineWidth(1);
	glPointSize(1);
	//fbo.end();
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glLineWidth(1);
	glPointSize(1);
	//fbo.end();
}

void ofxGKUtils::defaultUpdate(ofEasyCam* _cam, unsigned long int* _currentFrame, float* _time, const glm::vec4& _col) {
	*_currentFrame += 1;
	*_time = ofGetElapsedTimef();

	//_cam->lookAt(_cam->getPosition() + _cam->getLookAtDir(), _cam->getUpAxis());
	//_cam->lookAt(_cam->getTarget(), _cam->getUpAxis());
	ofNoFill();
	ofBackground(_col.r*255, _col.g*255, _col.b*255);
	//fbo.begin();
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

glm::vec2 ofxGKUtils::getPosLayout4x4Inverse(const int& _index) {
	glm::vec2 _pos;
	_pos.x = _index % 4 * ofGetWidth() * 0.25;
	_pos.y = floor(_index / 4) * ofGetHeight() * 0.25;
	return _pos;
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

void ofxGKUtils::setGUI(ofxGuiGroup& _gui,const int& _posIndex) {
	_gui.setup();
	_gui.setPosition(myGUIPos(_posIndex));
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

void ofxGKUtils::resizeGUI(ofxGuiGroup& _gui, const int& _posIndex) {
	_gui.setPosition(myGUIPos(_posIndex));
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
	if (_indexPos % 4 == 0){
		_pos.y += 60;
	}
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
	if (_indexPos % 4 == 0) {
		_pos.y += 60;
	}
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
	if (_indexPos % 4 == 0) {
		_pos.y += 60;
	}
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
	if (_indexPos % 4 == 0) {
		_pos.y += 60;
	}
	_pos.y += _fontSize;
	glColor3f(1, 1, 1);
	_font.drawString(_ss.str().c_str(), _pos.x, _pos.y);
}

void ofxGKUtils::drawInfo(const stringstream& _ss, const int& _indexPos) {
	//Bitmap
	//Width : 8pt , Height : 11pt
	glm::vec2 _pos = getPosLayout4x4(_indexPos);
	if (_indexPos < 4) {
		_pos.x += 60;
	}else{
		_pos.x += margin;
	};
	if (_indexPos % 4 == 0) {
		_pos.y += 60;
	}
	_pos.y += 11;

	//ofDrawBitmapStringHighlight(_ss.str().c_str(), _pos, ofColor(0), ofColor(255));
	ofDrawBitmapString(_ss.str().c_str(), _pos);
}

void ofxGKUtils::drawInfo(const stringstream& _ss, const int& _indexPos, const bool& _bSetMargin, const glm::vec2& _margin) {
	glm::vec2 _pos = getPosLayout4x4(_indexPos);
	if (_bSetMargin)_pos += _margin;
	_pos.y += 11;
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

void ofxGKUtils::drawInfo(const string& _s, const glm::vec2& _xyPos) {
	//Bitmap
	//Width : 8pt , Height : 11pt
	glm::vec2 _pos = _xyPos;
	_pos.y += 11;

	//ofDrawBitmapStringHighlight(_ss.str().c_str(), _pos, ofColor(0), ofColor(255));
	ofDrawBitmapString(_s, _pos);
}

void ofxGKUtils::drawInfo(const stringstream& _ss, const glm::vec2& _xyPos, const ofTrueTypeFont& _font, const int& _fontSize) {
	//TrueTypeFont
	glm::vec2 _pos = _xyPos;
	_pos.y += _fontSize;
	glColor3f(1, 1, 1);
	_font.drawString(_ss.str().c_str(), _pos.x, _pos.y);
}

void ofxGKUtils::manageInfoLimit(stringstream* _ss, const float& _height) {
}

void ofxGKUtils::manageInfoLimit(stringstream* _ss, const int& _numOfGrids) {
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
	//glLineWidth(1);
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

void ofxGKUtils::drawCross(const glm::vec3& _normalPlaneToDraw,const int& _x, const int& _y, const int& _size) {
	//glLineWidth(1);
	ofPushMatrix();
	if (_normalPlaneToDraw.y > 0)ofRotateXRad(PI / 2);
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

void ofxGKUtils::draw3DPlaneGrid(const float& _sizeUnit, const int& _numUnit, const glm::vec3& _normalPlaneToDraw, const float& _lineWidth, const glm::vec4& _col) {

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

void ofxGKUtils::draw3DBox(const glm::vec3& _center, const float& _sizeW, const float& _sizeH, const float& _sizeD, const float& _lineWidth, const glm::vec4& _lineColor) {
	ofPushMatrix();
	ofTranslate(_center);
	glLineWidth(_lineWidth);
	glColor4f(_lineColor.r, _lineColor.b, _lineColor.g, _lineColor.a);
	glBegin(GL_LINE_LOOP);
	glVertex3f(_sizeW / 2, _sizeD / 2, _sizeH / 2);
	glVertex3f(-_sizeW / 2, _sizeD / 2, _sizeH / 2);
	glVertex3f(-_sizeW / 2, -_sizeD / 2, _sizeH / 2);
	glVertex3f(+_sizeW / 2, -_sizeD / 2, _sizeH / 2);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(_sizeW / 2, _sizeD / 2, -_sizeH / 2);
	glVertex3f(-_sizeW / 2, _sizeD / 2, -_sizeH / 2);
	glVertex3f(-_sizeW / 2, -_sizeD / 2, -_sizeH / 2);
	glVertex3f(+_sizeW / 2, -_sizeD / 2, -_sizeH / 2);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(_sizeW / 2, _sizeD / 2, _sizeH / 2);
	glVertex3f(_sizeW / 2, _sizeD / 2, -_sizeH / 2);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(-_sizeW / 2, _sizeD / 2, _sizeH / 2);
	glVertex3f(-_sizeW / 2, _sizeD / 2, -_sizeH / 2);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-_sizeW / 2, -_sizeD / 2, _sizeH / 2);
	glVertex3f(-_sizeW / 2, -_sizeD / 2, -_sizeH / 2);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(+_sizeW / 2, -_sizeD / 2, _sizeH / 2);
	glVertex3f(+_sizeW / 2, -_sizeD / 2, -_sizeH / 2);
	glEnd();
	ofPopMatrix();
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

ofMesh ofxGKUtils::getModifiedMesh(const ofMesh& _inputMesh, const ofNode& _modifyInfo) {
	ofMesh _mesh = _inputMesh;
	auto mat = _modifyInfo.getGlobalTransformMatrix();
	for (auto& v : _mesh.getVertices()) {
		v = glm::vec3(mat * glm::vec4(v, 1));
	}
	auto mat2 = _modifyInfo.getOrientationQuat();
	for (auto& v : _mesh.getNormals()) {
		v = glm::vec3(mat2 * glm::vec4(v, 1));
	}
	return _mesh;
}

vector<glm::vec3> ofxGKUtils::getModifiedVertices(const vector<glm::vec3>& _inputVertices,const ofNode& _modifyInfo) {
	vector<glm::vec3> _vertices = _inputVertices;
	auto mat = _modifyInfo.getGlobalTransformMatrix();
	for (auto& v : _vertices) {
		v = glm::vec3(mat * glm::vec4(v, 1));
	}
	/*
	auto mat2 = _modifyInfo.getOrientationQuat();
	for (auto& v : *_normals) {
		v = glm::vec3(mat2 * glm::vec4(v, 1));
	}
	*/
	return _vertices;
}

vector<glm::vec3> ofxGKUtils::getOnPlaneVertices(const vector<glm::vec3>& _inputVertices, const ofNode& _modifyInfo) {
	vector<glm::vec3> _vertices = _inputVertices;
	auto mat = glm::inverse(_modifyInfo.getGlobalTransformMatrix());
	glm::quat _tmp = glm::quat(PI, 0, 0, 1);
	for (auto& v : _vertices) {
		v = glm::vec3(mat * glm::vec4(v, 1));
	}
	/*
	auto mat2 = _modifyInfo.getOrientationQuat();
	for (auto& v : *_normals) {
		v = glm::vec3(mat2 * glm::vec4(v, 1));
	}
	*/
	return _vertices;
}

glm::vec3 ofxGKUtils::getPolarFromRectangular(const glm::vec3& _coord) {
	//(r,theta,phi) theta <90,phi <180
	float _r = glm::length(_coord);
	float _theta = acos(_coord.z / _r);
	float _phi = atan2(_coord.y , _coord.x);
	return glm::vec3(_r, _theta, _phi);
}

glm::vec3 ofxGKUtils::getPolarFromRectangular(const GKPoint& _gkPoint) {
	//(r,theta,phi) theta <90,phi <180
	float _r = glm::length(_gkPoint.pos);
	float _theta = acos(_gkPoint.pos.z / _r);
	float _phi = atan2(_gkPoint.pos.y , _gkPoint.pos.x);
	return glm::vec3(_r, _theta, _phi);
}

// Cartesian
// 0<=theta(y)<=PI
// 0<=phi(z)<=2*PI
glm::vec3 ofxGKUtils::getRectangularFromPolar(const glm::vec3& _coord) {
	//x=r*sin(theta)*cos(phi)
	//y=r*sin(theta)*sin(phi)
	//z=r*cos(thata)
	float _x = _coord.x * sin(_coord.y) * cos(_coord.z);
	float _y = _coord.x * sin(_coord.y) * sin(_coord.z);
	float _z = _coord.x * cos(_coord.y);
	return glm::vec3(_x, _y, _z);
}
// Cartesian
// 0<=theta(y)<=PI
// 0<=phi(z)<=2*PI
glm::vec3 ofxGKUtils::getRectangularFromPolar(const GKPoint& _gkPoint) {
	//x=r*sin(theta)*cos(phi)
	//y=r*sin(theta)*sin(phi)
	//z=r*cos(thata)
	float _x = _gkPoint.pos.x * sin(_gkPoint.pos.y) * cos(_gkPoint.pos.z);
	float _y = _gkPoint.pos.x * sin(_gkPoint.pos.y) * sin(_gkPoint.pos.z);
	float _z = _gkPoint.pos.x * cos(_gkPoint.pos.y);
	return glm::vec3(_x, _y, _z);
}

void ofxGKUtils::sortPolars(vector<glm::vec3>* _coords) {
	for (int i = 0; i < _coords->size(); i++) {
		for (int j = 0; j < _coords->size(); j++) {
			if (_coords->at(i).z < _coords->at(j).z) {
				swap(_coords->at(i), _coords->at(j));
			}
		}
	}
}

void ofxGKUtils::sortPolars(vector<GKPoint>* _gkPoints) {
	for (int i = 0; i < _gkPoints->size(); i++) {
		for (int j = 0; j < _gkPoints->size(); j++) {
			if (_gkPoints->at(i).pos.z < _gkPoints->at(j).pos.z) {
				swap(_gkPoints->at(i), _gkPoints->at(j));
			}
		}
	}
}

ofQuaternion ofxGKUtils::slerp(ofQuaternion qtn1, ofQuaternion qtn2, float time) {
	ofQuaternion dest;
	float ht = qtn1[0] * qtn2[0] + qtn1[1] * qtn2[1] + qtn1[2] * qtn2[2] + qtn1[3] * qtn2[3];
	float hs = 1.0 - ht * ht;
	if (hs <= 0.0) {
		dest[0] = qtn1[0];
		dest[1] = qtn1[1];
		dest[2] = qtn1[2];
		dest[3] = qtn1[3];
	}
	else {
		hs = sqrt(hs);
		if (abs(hs) < 0.0001) {
			dest[0] = (qtn1[0] * 0.5 + qtn2[0] * 0.5);
			dest[1] = (qtn1[1] * 0.5 + qtn2[1] * 0.5);
			dest[2] = (qtn1[2] * 0.5 + qtn2[2] * 0.5);
			dest[3] = (qtn1[3] * 0.5 + qtn2[3] * 0.5);
		}
		else {
			float ph = acos(ht);
			float pt = ph * time;
			float t0 = sin(ph - pt) / hs;
			float t1 = sin(pt) / hs;
			dest[0] = qtn1[0] * t0 + qtn2[0] * t1;
			dest[1] = qtn1[1] * t0 + qtn2[1] * t1;
			dest[2] = qtn1[2] * t0 + qtn2[2] * t1;
			dest[3] = qtn1[3] * t0 + qtn2[3] * t1;
		}
	}
	return dest;
};

#pragma mark - calc
//-------------------------------------------------------HELPER_CALC-------------------------------------------------------//
int ofxGKUtils::factorial(int _n) {
	if (_n == 0)return 1;
	else return _n * factorial(_n - 1);
}

int ofxGKUtils::totalNumCombination(int _n, int _r) {
	if (_n == _r)return(1);
	else if (_r == 0)return(1);
	else if (_r == 1) return(_n);
	else return(totalNumCombination(_n - 1, _r - 1) + totalNumCombination(_n - 1, _r));
}

vector<glm::vec2> ofxGKUtils:: getIndexList_nC2(int _n) {	
	vector<glm::vec2> _resultList;
	for (int i = 0; i < _n-1; i++) {		
		for (int j = i+1; j < _n; j++) {
			_resultList.push_back(glm::vec2(i, j));
		}
	}
	return _resultList;
}


#pragma mark - importGK
//-------------------------------------------------------HELPER_IMPORT-------------------------------------------------------//
string ofxGKUtils::findLatestFilePath(const string& _dirPath,const string& _fileType) {
	ofDirectory _dir(_dirPath);
	_dir.allowExt(_fileType);//only show {}file ex)png,mp3,css
	_dir.sort();
	_dir.listDir();
	if (_dir.size() > 0) {
		return _dir.getPath(_dir.size() - 1);
	}
}

string ofxGKUtils::extractFilePathWithoutExt(const string& _filePath) {
	string::size_type pos;
	if ((pos = _filePath.find_last_of(".")) == string::npos) {
		return _filePath;
	}
	return _filePath.substr(0, pos);
}

void ofxGKUtils::loadImgsInDir(vector<ofImage>* _imgs, const string& _dirPath) {
	ofDirectory _dir(_dirPath);
	_dir.allowExt("png");
	_dir.allowExt("jpg");
	_dir.allowExt("jpeg");
	_dir.allowExt("JPEG");
	_dir.sort();
	_dir.listDir();
	for (int i = 0; i < _dir.size(); i++) {
		ofImage _img;
		_img.loadImage(_dir.getPath(i));
		_imgs->push_back(_img);
	}
}

void ofxGKUtils::loadImgsInDir(vector<ofImage>* _imgs,vector<string>* _names, const string& _dirPath) {
	ofDirectory _dir(_dirPath);
	_dir.allowExt("png");
	_dir.allowExt("jpg");
	_dir.allowExt("jpeg");
	_dir.allowExt("JPEG");
	_dir.sort();
	_dir.listDir();
	for (int i = 0; i < _dir.size(); i++) {
		ofImage _img;
		_img.loadImage(_dir.getPath(i));
		_imgs->push_back(_img);
		string _name;
		_name = _dir.getName(i);
		_names->push_back(_name);
	}
}

void ofxGKUtils::importGK3D(const string& _url,ofMesh& _meshToPass, vector<GKPlane>& _gkPlanesCreatedFromMeshToPass,vector<GKPlane>& _gkPlanesCreatedManuallyToPass) {
	ifstream file_in_asGk3d;	
	ofstream file_out_asTmpMeshPly;
	bool bMeshToPassIsLoaded = false;
	string lineInput;
	string wordInput;
	float valueInput;
	vector<float> vertexInfo;
	vector<glm::vec3> verticesInfo;
	int type = 0;

	file_in_asGk3d.open("./data/" + _url, std::ios::in);
	if (!file_in_asGk3d.is_open()) {
		std::cout << "failed to open " << "./data/" + _url << '\n';
	}else {
		while (std::getline(file_in_asGk3d,lineInput)){
			if ((lineInput[0] == '/' && lineInput[1] == '/') || lineInput.empty()) {
				continue;
			}
			else {
				if (lineInput == "Original Mesh") {
					type = 1;
					file_out_asTmpMeshPly.open("./data/tmpMesh.ply", std::ios::out);
				}
				else
				if (lineInput == "GKPlane Created From Mesh") {
					type = 2;
					vertexInfo.erase(vertexInfo.begin(), vertexInfo.end());
					verticesInfo.erase(verticesInfo.begin(), verticesInfo.end());
				}
				else
				if (lineInput == "GKPlane Created Manually") {
					type = 3;
					vertexInfo.erase(vertexInfo.begin(), vertexInfo.end());
					verticesInfo.erase(verticesInfo.begin(), verticesInfo.end());
				}
				else {
					if (type == 1) {
						file_out_asTmpMeshPly << lineInput << endl;
					}
					else
					if (type == 2) {
						cout << "type2" << endl;
						if (!bMeshToPassIsLoaded) {
							_meshToPass.load("./tmpMesh.ply");
							if (_meshToPass.hasVertices()) {
								cout << "tmpMesh.ply is loaded" << endl;
								bMeshToPassIsLoaded = true;
							}
							else {
								cout << "tmpMesh.ply is not loaded. fail." << endl;
							}
						}
						std::istringstream lineInputStream(lineInput);
						while (std::getline(lineInputStream, wordInput, ',')) {
							cout << "begin" << endl;
							valueInput = std::stof(wordInput);
							vertexInfo.push_back(valueInput);
							if (vertexInfo.size() == 3) {
								verticesInfo.push_back(glm::vec3(vertexInfo[0], vertexInfo[1], vertexInfo[2]));
								cout << "vertex made" << endl;
								vertexInfo.erase(vertexInfo.begin(), vertexInfo.end());
								cout << "vertex released" << endl;
							}
						}
						ofMesh _meshToCreate;
						_meshToCreate.addVertices(verticesInfo);
						cout << "mesh created" << endl;
						_gkPlanesCreatedFromMeshToPass.push_back(GKPlane(_meshToCreate, 0));
						verticesInfo.erase(verticesInfo.begin(), verticesInfo.end());
					}
					else
					if (type == 3) {
						cout << "type3" << endl;
						std::istringstream lineInputStream(lineInput);
						while (std::getline(lineInputStream, wordInput, ',')) {
							valueInput = std::stof(wordInput);
							vertexInfo.push_back(valueInput);
							if (vertexInfo.size() == 3) {
								verticesInfo.push_back(glm::vec3(vertexInfo[0], vertexInfo[1], vertexInfo[2]));
								cout << "vertex made" << endl;
								vertexInfo.erase(vertexInfo.begin(), vertexInfo.end());
								cout << "vertex released" << endl;
							}
						}
						_gkPlanesCreatedManuallyToPass.push_back(GKPlane(verticesInfo, 0));
						cout << "manual plane created" << endl;
						verticesInfo.erase(verticesInfo.begin(), verticesInfo.end());
					}
				}
			}
		}
	}
	if (ofFile::doesFileExist("./tmpMesh.ply")) {
		cout << "tmpMesh.ply exists" << endl;
		//ofFile::removeFile("./tmpMesh.ply", true);
	}
	//*ssLog << "IMPORTED GK3D : " + _url << endl;
	std::cout << "valuesToCreateMesh : " << _gkPlanesCreatedFromMeshToPass.size() << endl;
	std::cout << "valuesToCreateGKPlnae : " << _gkPlanesCreatedManuallyToPass.size() << endl;
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
	_ss << "." <<_fileType;
	return _ss;
}

void ofxGKUtils::saveImage() {
	string _fileName = makeFileName("./screenShot/", "png").str().c_str();
	ofImage _imgToSave;
	_imgToSave.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
	//*ssLog << "EXPORTED SCREEN : " + _fileName << std::endl;
}

void ofxGKUtils::saveImage(const string& _url) {
	string _fileName = makeFileName(_url, "png").str().c_str();
	ofImage _imgToSave;
	_imgToSave.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
	//*ssLog << "EXPORTED SCREEN : " + _fileName << std::endl;
}

void ofxGKUtils::saveFBOtoImage(ofFbo* _fbo) {
	string _fileName = makeFileName("./fboShot/", "png").str().c_str();
	ofPixels _pixels;
	_fbo->readToPixels(_pixels);
	ofImage _imgToSave;
	_imgToSave.setFromPixels(_pixels);
	_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
	//*ssLog << "EXPORTED FBO : " + _fileName << std::endl;
}

void ofxGKUtils::saveFBOtoImage(ofFbo* _fbo, const string& _url) {
	string _fileName = makeFileName(_url, "png").str().c_str();
	ofPixels _pixels;
	_fbo->readToPixels(_pixels);
	ofImage _imgToSave;
	_imgToSave.setFromPixels(_pixels);
	_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
	//*ssLog << "EXPORTED FBO : " + _fileName << std::endl;
}

void ofxGKUtils::saveMesh(ofMesh& _mesh, const float& _scaleFactor) {
	string _fileName = makeFileName("./meshExport/", "ply").str().c_str();
	ofMesh _meshToSave = _mesh;
	glm::vec3 _centroid = _mesh.getCentroid();
	//*ssLog << _centroid << endl;
	for (int i = 0; i < _mesh.getNumVertices(); i++) {
		_meshToSave.getVertices()[i] = (_mesh.getVertex(i) - _centroid) * _scaleFactor;;
	}
	_meshToSave.save(_fileName);
	//*ssLog << "EXPORTED MESH : " + _fileName << endl;
	//free(&_meshToSave);
}

void ofxGKUtils::saveMesh(ofMesh& _mesh, const float& _scaleFactor, const string& _url) {
	string _fileName = makeFileName(_url, "ply").str().c_str();
	ofMesh _meshToSave = _mesh;
	glm::vec3 _centroid = _mesh.getCentroid();
	//*ssLog << _centroid << endl;
	for (int i = 0; i < _mesh.getNumVertices(); i++) {
		_meshToSave.getVertices()[i] = (_mesh.getVertex(i) - _centroid) * _scaleFactor;;
	}
	_meshToSave.save(_fileName);
	//*ssLog << "EXPORTED MESH : " + _fileName << endl;
	//free(&_meshToSave);
}

void ofxGKUtils::saveGK3D(const string& _url, ofMesh& _originalMesh,vector<GKPlane>& _gkPlanesCreatedFromMesh,vector<GKPlane>& _gkPlanesCreatedManually) {
	string _fileName = makeFileName(_url, "gk3d").str().c_str();
	_fileName = "./data/" + _fileName;
	ofstream file_out;
	file_out.open(_fileName, std::ios::out);
	if (!file_out.is_open()) {
		std::cout << "failed to open " << _fileName << '\n';
	}
	else {
		file_out << "// =   THIS FILE WAS CREATED IN GK3D.                                      = //" << endl;
		file_out << "// =   IF YOU USE THIS FILE, DONWLOAD GK3D FROM GITHUB REPOSITORY [GK3D].  = //" << endl;
		file_out << "// =   SOFTWARE DEVELOPED & MANAGED BY GAISHI KUDO.                        = //" << endl;
		file_out << "// = - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - = //"<< endl;
		file_out << "// = - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - = //" << endl;
		file_out << "// = - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - = //" << endl;

		//----------- MESH PLY -----------//
		file_out << "Original Mesh" << endl;
		file_out << "ply" << std::endl;
		file_out << "format ascii 1.0" << endl;
		if (_originalMesh.getNumVertices()) {
			file_out << "element vertex " << _originalMesh.getNumVertices() << std::endl;
			file_out << "property float x" << std::endl;
			file_out << "property float y" << std::endl;
			file_out << "property float z" << std::endl;
			if (_originalMesh.getNumColors()) {
				file_out << "property uchar red" << std::endl;
				file_out << "property uchar green" << std::endl;
				file_out << "property uchar blue" << std::endl;
				file_out << "property uchar alpha" << std::endl;
			}
			if (_originalMesh.getNumTexCoords()) {
				file_out << "property float u" << std::endl;
				file_out << "property float v" << std::endl;
			}
			if (_originalMesh.getNumNormals()) {
				file_out << "property float nx" << std::endl;
				file_out << "property float ny" << std::endl;
				file_out << "property float nz" << std::endl;
			}
		}

		uint8_t faceSize = 3;
		if (_originalMesh.getNumIndices()) {
			file_out << "element face " << _originalMesh.getNumIndices() / faceSize << std::endl;
			file_out << "property list uchar int vertex_indices" << std::endl;
		}
		else if (_originalMesh.getMode() == OF_PRIMITIVE_TRIANGLES) {
			file_out << "element face " << _originalMesh.getNumVertices() / faceSize << std::endl;
			file_out << "property list uchar int vertex_indices" << std::endl;
		}
		else if (_originalMesh.getMode() == OF_PRIMITIVE_TRIANGLE_STRIP && _originalMesh.getNumVertices() >= 4) {
			file_out << "element face " << _originalMesh.getNumVertices() - 2 << std::endl;
			file_out << "property list uchar int vertex_indices" << std::endl;
		}

		file_out << "end_header" << std::endl;

		for (std::size_t i = 0; i < _originalMesh.getNumVertices(); i++) {
			file_out << _originalMesh.getVertex(i).x << " " << _originalMesh.getVertex(i).y << " " << _originalMesh.getVertex(i).z;
			
			if (_originalMesh.getNumColors()) {
				// VCG lib / MeshLab don't support float colors, so we have to cast
				ofColor cur = _originalMesh.getColors()[i];
				file_out << " " << (int)cur.r << " " << (int)cur.g << " " << (int)cur.b << " " << (int)cur.a;
			}
			if (_originalMesh.getNumTexCoords()) {
				file_out << " " << _originalMesh.getTexCoord(i).x << " " << _originalMesh.getTexCoord(i).y;
			}
			if (_originalMesh.getNumNormals()) {
				file_out << " " << _originalMesh.getNormal(i).x << " " << _originalMesh.getNormal(i).y << " " << _originalMesh.getNormal(i).z;
			}
			file_out << std::endl;
		}

		if (_originalMesh.getNumIndices()) {
			for (uint32_t i = 0; i < _originalMesh.getNumIndices(); i += faceSize) {
				file_out << (std::size_t)faceSize << " " << _originalMesh.getIndex(i) << " " << _originalMesh.getIndex(i + 1) << " " << _originalMesh.getIndex(i + 2) << std::endl;
			}
		}
		else if (_originalMesh.getMode() == OF_PRIMITIVE_TRIANGLES) {
			for (uint32_t i = 0; i < _originalMesh.getNumVertices(); i += faceSize) {
				uint32_t indices[] = { i, i + 1, i + 2 };
				file_out << (std::size_t)faceSize << " " << indices[0] << " " << indices[1] << " " << indices[2] << std::endl;
			}
		}
		else if (_originalMesh.getMode() == OF_PRIMITIVE_TRIANGLE_STRIP && _originalMesh.getNumVertices() >= 4) {
			for (uint32_t i = 0; i < _originalMesh.getNumVertices() - 2; i += 2) {
				uint32_t indices1[] = { i, i + 1, i + 2 };
				uint32_t indices2[] = { i + 1, i + 3, i + 2 };
				file_out << (std::size_t)faceSize << " " << indices1[0] << " " << indices1[1] << " " << indices1[2] << std::endl;
				file_out << (std::size_t)faceSize << " " << indices2[0] << " " << indices2[1] << " " << indices2[2] << std::endl;
			}
		}

		//----------- GKPlane Created From Mesh -----------//
		file_out << "GKPlane Created From Mesh" << endl;
		for (auto& gkp : _gkPlanesCreatedFromMesh) {
			ofMesh& _tmpMesh = gkp.originalMesh;
			file_out << gkp.originalMesh.getVertex(0) << "," << gkp.originalMesh.getVertex(1) << "," << gkp.originalMesh.getVertex(2) << endl;
		}

		//----------- GKPlane Created Manually -----------//
		file_out << "GKPlane Created Manually" << endl;
		for (auto& gkp : _gkPlanesCreatedManually) {
			string _tmpVerticesLog;
			for (auto itr = gkp.vertices.begin(); itr != gkp.vertices.end(); ++itr) {
				if (itr != gkp.vertices.end() - 1) {
					_tmpVerticesLog += ofToString(*itr) + ",";
				}
				else {
					_tmpVerticesLog += ofToString(*itr);
				}
			}
			file_out << _tmpVerticesLog << endl;
		}
		//*ssLog << "EXPORTED GK3D : " + _fileName << endl;
	}
}