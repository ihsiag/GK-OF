#pragma once

#include "ofMain.h"
#include "ofApp.h"


class Class_MyFunctions {
public:
	Class_MyFunctions() {
	}
	~Class_MyFunctions() {
	}
#pragma mark -HELPER_DEFAULT
//-------------------------------------------------------HELPER_DEFAULT-------------------------------------------------------//

	void setup(ofEasyCam* _ezCam) {
		ofSetVerticalSync(true);
		ofNoFill();
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 0, 0);
		ofEnableAlphaBlending();
		_ezCam->setNearClip(0.1);
		_ezCam->setFarClip(100000);
		//_ezCam->setPosition(0, 0, 0);
		//_ezCam->lookAt(glm::vec3(0, 0, 0),glm::vec3(0,0,1));
		//_ezCam->enableOrtho();
		//_ezCam->disableMouseInput();
		//_ezCam->enableMouseInput();
		//_ezCam->enableMouseMiddleButton();
	}

	void defaultUpdate(float* _currentFrame, float* _time) {
		*_currentFrame += 1.0;
		*_time = ofGetElapsedTimef();

		ofBackground(10);
		ofNoFill();
		//fbo.begin();
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 0, 0);
		glLineWidth(1);
		//fbo.end();
	}

#pragma mark -HELPER_2D
//-------------------------------------------------------HELPER_2D-------------------------------------------------------//

	void drawInfo(const stringstream& _ss,const ofTrueTypeFont& _font,const int& _fontSize) {
		//TrueTypeFont
		/*
		glm::vec2 pos = glm::vec2(60, ofGetHeight() * 0.75+_fontSize);
		glColor3f(1, 1, 1);
		_font.drawString(_ss.str().c_str(), pos.x,pos.y);
		*/

		//Bitmap
		//Width : 8pt , Height : 11pt
		glColor3f(1, 1, 1);
		glm::vec2 pos = glm::vec2(60, ofGetHeight() * 0.75 + 11);
		//ofDrawBitmapStringHighlight(_ss.str().c_str(), pos, ofColor(0), ofColor(255));
		ofDrawBitmapString(_ss.str().c_str(), pos);
	}

	void drawGrid() {
		const int _size = 10;
		ofNoFill();
		ofSetColor(50);
		ofDrawLine(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() / 2);
		ofDrawLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());

		ofNoFill();
		ofSetColor(50);
		int margin = 8;
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

	void drawCross(const int& _x, const int& _y, const int& _size) {
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

	void draw3DAxis() {
		const int _size = 1000;
		const float _alpha = 0.5;
		glLineWidth(2);
		glColor4f(1,0,0,_alpha);//x = red
		glBegin(GL_LINES);
		glVertex3f(-_size / 2, 0, 0);
		glVertex3f(_size / 2, 0, 0);
		glEnd();
		glColor4f(0, 1, 0, _alpha);//y = green
		glBegin(GL_LINES);
		glVertex3f(0, -_size / 2, 0);
		glVertex3f(0, _size / 2, 0);
		glColor4f(0, 0, 1,_alpha);//z = blue
		glBegin(GL_LINES);
		glVertex3f(0,0, -_size / 2);
		glVertex3f(0,0, _size / 2);
		glEnd();
	}

	void getBoundingBox() {

	}

#pragma mark -save
//-------------------------------------------------------HELPER_SAVE-------------------------------------------------------//

	void saveVideo(const float& _currentFrame) { //frame<=99'999 %05d %[fill][width]d
		string _name;
		_name = ofToString(_currentFrame,5,5,0);
		/*
		if (_currentFrame < 10) {
			_name = "0000" + ofToString(_currentFrame);
		}
		else if (_currentFrame < 100) {
			_name = "000" + ofToString(_currentFrame);
		}
		else if (_currentFrame < 1000) {
			_name = "00" + ofToString(_currentFrame);
		}
		else if (_currentFrame < 10000) {
			_name = "0" + ofToString(_currentFrame);
		}
		else {
			_name = ofToString(_currentFrame);
		}
		*/
		string _fileName = "./screenShotForMovie/" + _name + ".png";
		ofImage _imgToSave;
		_imgToSave.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
	}

	void saveImage() {
		string _fileName = "./screenShot/" + ofToString(ofGetMonth()) + ofToString(ofGetDay()) + ofToString(ofGetHours()) + ofToString(ofGetMinutes()) + ofToString(ofGetSeconds()) + ".png";
		ofImage _imgToSave;
		_imgToSave.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
		std::cout << "img : " + _fileName + " -exported" << std::endl;
	}

	void saveFBOtoImage(ofFbo* _fbo) {
		string _fileName = "./screenShot/" + ofToString(ofGetMonth()) + ofToString(ofGetDay()) + ofToString(ofGetHours()) + ofToString(ofGetMinutes()) + ofToString(ofGetSeconds()) + ".png";
		ofPixels _pixels;
		_fbo->readToPixels(_pixels);
		ofImage _imgToSave;
		_imgToSave.setFromPixels(_pixels);
		_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
		std::cout << "img : " + _fileName + " -exported" << std::endl;
	}
};