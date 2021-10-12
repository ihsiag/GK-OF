#pragma once

#include "ofMain.h"
#include "ofApp.h"


class Class_MyFunctions {
public:
	Class_MyFunctions() {

	}

	void setup(ofEasyCam* _ezCam) {
		ofSetVerticalSync(true);
		//_ezCam->setNearClip(0.1);
		//_ezCam->setFarClip(100000);
		//_ezCam->setPosition(0, 0, 0);
		//_ezCam->lookAt(glm::vec3(0, 0, 0),glm::vec3(0,0,1));
		//_ezCam->enableOrtho();
		//_ezCam->disableMouseInput();
		//_ezCam->enableMouseInput();
		//_ezCam->enableMouseMiddleButton();
	}

	void resetBasics() {
		ofBackground(10);
		glClearColor(0,0,0,0);
	}


	void makeGrid() {
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
						drawCross(x * ofGetWidth() / 4, y * ofGetHeight() / 4, 10);
					}
				}
			}
		}
		ofPopMatrix();
	}

	void drawCross(const int& _x, const int& _y, const int& _size) {
		ofPushMatrix();
		ofTranslate(_x, _y);
		ofDrawLine(-_size / 2, 0, _size / 2, 0);
		ofDrawLine(0, -_size / 2, 0, _size / 2);
		ofPopMatrix();
	}


#pragma mark -save
	void saveVideo(const float& _currentFrame) { //frame<=99'999 %05d %[fill][width]d
		string _name;
		_name = ofToString(_currentFrame,5,0);
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
		string _fileName = "../EXPORTED/screenShots/" + ofToString(ofGetMonth()) + ofToString(ofGetDay()) + ofToString(ofGetHours()) + ofToString(ofGetMinutes()) + ofToString(ofGetSeconds()) + ".png";
		ofPixels _pixels;
		_fbo->readToPixels(_pixels);
		ofImage _imgToSave;
		_imgToSave.setFromPixels(_pixels);
		_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
		std::cout << "img : " + _fileName + " -exported" << std::endl;
	}
};