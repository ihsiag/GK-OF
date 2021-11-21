#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSvg.h"
#include "ofxOpenCv.h"
#include "ofEasyCam.h"
#include "ofShader.h"

class ofApp : public ofBaseApp {

public:

	//-----------IMPORT-----------//
	ofxPanel gui;
	ofTrueTypeFont font;
	ofEasyCam cam;

	//------------OUTPUT----------//
	ofImage imgToSave;
	ofFbo fbo;
	ofShader shader;

	//-----------GLOBAL-----------//
	float time;
	float fontSize;

	vector<ofImage> imgs;

	float originalW, originalH;
	float currentW, currentH;

	bool saveCheckerID01 = false;
	bool saveCheckerID02 = false;
	bool saveCheckerID03 = false;


	//-----------SLIDER-----------//
	ofxToggle drawAreaBGToggle;
	ofxToggle drawAreaOUTToggle;
	ofxToggle drawGridToggle;
	ofxToggle arrangeToGridToggle;
	ofxToggle mainRandomImgToggle;
	ofxToggle mainRandomRotationToggle;
	ofxToggle mainRandomScaleToggle;
	ofxToggle mainRandomAlphaToggle;

	ofxIntSlider areaWidthSlider;
	ofxIntSlider areaHeightSlider;

	ofxIntSlider gridNumXSlider;
	ofxIntSlider gridNumYSlider;
	ofxFloatSlider gridDistXSlider;
	ofxFloatSlider gridDistYSlider;
	ofxIntSlider offGridMinSlider;
	ofxIntSlider offGridMaxSlider;

	ofxIntSlider organicCenterNumSlider;
	ofxFloatSlider organicRadiusMinSlider;
	ofxFloatSlider organicRadiusMaxSlider;
	ofxIntSlider organicLeavesNumMinSlider;
	ofxIntSlider organicLeavesNumMaxSlider;
	ofxFloatSlider organicDegreeMinSlider;
	ofxFloatSlider organicDegreeMaxSlider;

	ofxIntSlider mainSeedSlider;
	ofxIntSlider mainImgSelectSlider;
	ofxFloatSlider mainScaleSlider;
	ofxFloatSlider mainRandomScaleMinSlider;
	ofxFloatSlider mainRandomScaleMaxSlider;
	ofxIntSlider mainAlphaSlider;
	ofxIntSlider mainRandomAlphaMinSlider;
	ofxIntSlider mainRandomAlphaMaxSlider;

	ofxIntSlider mainAngleRangeZSlider;
	ofxIntSlider mainAngleRangeXSlider;
	ofxIntSlider mainAngleRangeYSlider;




	//----------MAIN-----------//

	void setup() {

		std::cout << "Script Begins !" << std::endl;

		//---initParam---//
		fontSize = 12;

		//---loading---//
		//img
		string dirName = "./imgs_justForFun/";
		ofDirectory dir(dirName);
		dir.allowExt("png");//only show {}file ex)png,mp3,css
		//dir.sort();
		dir.listDir();
		for (int i = 0; i < dir.size(); i++) {
			ofImage _img;
			_img.load(dir.getPath(i));
			imgs.push_back(_img);
		}
		originalW = imgs[0].getWidth();
		originalH = imgs[0].getHeight();

		//shader
		shader.load("", "./shaders/tone.frag");


		//font
		ofTrueTypeFont::setGlobalDpi(72);
		font.load("font/SourceCodePro-Light.ttf", fontSize);
		font.setLineHeight(fontSize);
		font.setLetterSpacing(1.0);

		//---sliders---//
		/*  gui.add(slider.setup("sliderName", initial, min, max); */

		gui.setup();


		gui.add(drawAreaBGToggle.setup("drawAreaBG", true));
		gui.add(drawGridToggle.setup("drawGrid", true));

		gui.add(mainRandomImgToggle.setup("mainRandomImg", false));
		gui.add(mainRandomRotationToggle.setup("mainRandomRotation", false));
		gui.add(mainRandomScaleToggle.setup("mainRandomScale", false));
		gui.add(mainRandomAlphaToggle.setup("mainRandomAlpha", false));

		gui.add(areaWidthSlider.setup("areaWidth", 2000, 900, 2000));
		gui.add(areaHeightSlider.setup("areaHeight", 2000, 900, 2000));
		gui.add(gridNumXSlider.setup("gridNumX", 6, 1, 45));
		gui.add(gridNumYSlider.setup("gridNumY", 6, 1, 45));
		gui.add(gridDistXSlider.setup("gridDistX", 185, 10, 200));
		gui.add(gridDistYSlider.setup("gridDistY", 185, 10, 200));


		gui.add(organicCenterNumSlider.setup("organicCenterNum", 30, 10, 1000));
		gui.add(organicRadiusMinSlider.setup("organicRadiusMin", 50, 0, 200));
		gui.add(organicRadiusMaxSlider.setup("organicRadiusMax", 100, 0, 500));
		gui.add(organicLeavesNumMinSlider.setup("organicLeavesNumMin", 2, 1, 10));
		gui.add(organicLeavesNumMaxSlider.setup("organicLeavesNumMax", 12, 3, 20));
		gui.add(organicDegreeMinSlider.setup("organicDegreeMin", 20, 5, 80));
		gui.add(organicDegreeMaxSlider.setup("organicDegreeMax", 20, 5, 80));

		gui.add(mainImgSelectSlider.setup("mainImgSelect", 0, 0, imgs.size()-1));
		gui.add(mainSeedSlider.setup("mainSeed", 0, 0, 50));
		gui.add(mainScaleSlider.setup("mainScale", 0.2, 0.01, 1.0));
		gui.add(mainRandomScaleMinSlider.setup("mainRandomScaleMin", 1.000, 0.000, 1.000));
		gui.add(mainRandomScaleMaxSlider.setup("mainRandomScaleMax", 1.200, 0.0000, 2.000));
		gui.add(mainAlphaSlider.setup("mainAlphaSlider", 255, 0, 255));
		gui.add(mainRandomAlphaMinSlider.setup("mainRandomAlphaMin", 0, 0, 255));
		gui.add(mainRandomAlphaMaxSlider.setup("mainRandomAlphaMax", 170, 0, 255));

		gui.add(mainAngleRangeZSlider.setup("mainAngleRangeZ", 45, 0, 180));
		gui.add(mainAngleRangeXSlider.setup("mainAngleRangeX", 0, 0, 180));
		gui.add(mainAngleRangeYSlider.setup("mainAngleRangeY", 0, 0, 180));

		//---camera---//

		int CAM_Z = 500;
		cam.setNearClip(0.1);
		cam.setFarClip(1000);
		cam.setPosition(0, 0, CAM_Z);
		cam.enableOrtho();
		cam.disableMouseInput();

		//---basic---//

		ofSetBackgroundAuto(true);
		ofSetBackgroundColor(220);
		//ofEnableAlphaBlending();
		
		//ofEnableBlendMode(); //OF_BLENDMODE_DISABLED, OF_BLENDMODE_ALPHA, OF_BLENDMODE_ADD, OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_SCREEN
		ofSetFrameRate(30);
		ofEnableAntiAliasing();
		//ofEnableDepthTest();

		ofSetWindowTitle("MIDTOWN2021_TEXTUREMAKE : by Gaishi Kudo");

		fbo.allocate(2000, 2000, GL_RGBA);

	}

	void update() {
		time = ofGetElapsedTimef();
		fbo.begin();
		ofClear(0);
		fboRun();
		fbo.end();
	}

	void draw() {
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
		if (ofGetWidth() >= ofGetHeight()) {
			float _tmpH = ofGetHeight();
			float _tmpW = fbo.getWidth() * ofGetHeight() / fbo.getHeight();
			fbo.draw(-_tmpW / 2, -_tmpH / 2, _tmpW, _tmpH);
		}
		else {
			float _tmpW = ofGetWidth();
			float _tmpH = fbo.getHeight() * ofGetWidth() / fbo.getWidth();
			fbo.draw(-_tmpW / 2, -_tmpH / 2, _tmpW, _tmpH);
		}
		ofPopMatrix();
		info();
		gui.draw();
	}

	void fboRun() {
		glEnable(GL_BLEND);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
		setArea();

		cam.begin();
		ofPushMatrix();
		ofTranslate(-fbo.getWidth() / 2, -fbo.getHeight() / 2, 0);
		arrangeOrganic();
		ofPopMatrix();
		cam.end();
		showGrid();
	}

	//----------CUSTOMFUNCS-----------//

	void info() {
		float _x = 15;
		float _y = ofGetHeight() * 0.9;
		string infoData[3];
		infoData[0] = "PROJECT : MIDTOWN2021";
		infoData[1] = "FPS : " + ofToString(ceilf(ofGetFrameRate() * 100) / 100);
		infoData[2] = "TIME : " + ofToString(ceilf(time * 100) / 100);

		for (int i = 0; i < 3; i++) {
			ofSetColor(0, 80);
			ofFill();
			ofRectangle bb = font.getStringBoundingBox(infoData[i], 0, 0);
			ofDrawRectangle(_x - fontSize / 2, _y - bb.height - fontSize / 2 + (bb.height + fontSize) * i, bb.width + fontSize, bb.height + fontSize);
			ofSetColor(255, 255);
			font.drawString(infoData[i], _x, _y + (bb.height + fontSize) * i);
		}
	}

	void setArea() {
		ofRectangle areaBG = ofRectangle(-fbo.getWidth() / 2, -fbo.getHeight() / 2, fbo.getWidth(), fbo.getHeight());
		ofRectangle area = ofRectangle(-areaWidthSlider / 2, -areaHeightSlider / 2, areaWidthSlider, areaHeightSlider);

		ofPushMatrix();
		ofTranslate(fbo.getWidth() / 2, fbo.getHeight() / 2);
		ofFill();
		ofSetColor(220);
		ofDrawRectangle(areaBG);
		ofSetColor(50, 200, 50);
		ofDrawRectangle(area);
		ofPopMatrix();
	}


	void showGrid() {
		ofNoFill();
		ofSetLineWidth(1);
		ofSetColor(255, 255);
		ofPushMatrix();
		ofTranslate(fbo.getWidth() / 2 - gridDistXSlider * gridNumXSlider / 2, fbo.getHeight() / 2 - gridDistYSlider * gridNumYSlider / 2);
		for (int y = 0; y < gridNumYSlider + 1; y++) {
			for (int x = 0; x < gridNumXSlider + 1; x++) {
				drawCross(x * gridDistXSlider, y * gridDistYSlider, 20);
			}
		}
		ofPopMatrix();
	}

	void arrangeToGrid() {
		ofSetColor(255, 255);
		ofPushMatrix();
		ofTranslate(fbo.getWidth() / 2 - gridDistXSlider * gridNumXSlider / 2, fbo.getHeight() / 2 - gridDistYSlider * gridNumYSlider / 2);
		ofSeedRandom(mainSeedSlider);
		for (int y = 0; y < gridNumYSlider + 1; y++) {
			for (int x = 0; x < gridNumXSlider + 1; x++) {
				if (mainRandomImgToggle) { drawRandomImage(x * gridDistXSlider, y * gridDistYSlider); }
				else { drawSelectImage(mainImgSelectSlider, x * gridDistXSlider, y * gridDistYSlider); }
			}
		}
		ofPopMatrix();
	}

	void arrangeRandom() {
		ofSetColor(255, 255);
		ofPushMatrix();
		ofTranslate(fbo.getWidth() / 2 - gridDistXSlider * gridNumXSlider / 2, fbo.getHeight() / 2 - gridDistYSlider * gridNumYSlider / 2);
		ofSeedRandom(mainSeedSlider);
		for (int y = 0; y < gridNumYSlider + 1; y++) {
			for (int x = 0; x < gridNumXSlider + 1; x++) {
				float offGrid = ofRandom(offGridMinSlider, offGridMaxSlider);
				float dir = ofRandom(1);
				float valueX, valueY;
				if (dir < 0.25) {
					valueX = -offGrid;
					valueY = -offGrid;
				}
				else if (dir < 0.50) {
					valueX = +offGrid;
					valueY = -offGrid;
				}
				else if (dir < 0.75) {
					valueX = -offGrid;
					valueY = +offGrid;
				}
				else {
					valueX = +offGrid;
					valueY = +offGrid;
				}
				if (mainRandomImgToggle) { drawRandomImage(x * gridDistXSlider + valueX, y * gridDistYSlider + valueY); }
				else { drawSelectImage(mainImgSelectSlider, x * gridDistXSlider + valueX, y * gridDistYSlider + valueY); }
			}
		}
		ofPopMatrix();
	}

	void arrangeOrganic() {
		ofSeedRandom(mainSeedSlider);
		for (int i = 0; i < organicCenterNumSlider; i++) {
			float x = ofRandom(fbo.getWidth());
			float y = ofRandom(fbo.getHeight());
			int leavesNum = ofRandom(organicLeavesNumMinSlider, organicLeavesNumMaxSlider);
			//float radius = ofRandom(organicRadiusMinSlider,organicRadiusMaxSlider);
			float deg = ofRandom(organicDegreeMinSlider, organicDegreeMaxSlider);
			float rad = sin(ofDegToRad(deg));
			ofPushMatrix();
			ofTranslate(x, y, 0);
			if (drawGridToggle)drawCross(0, 0, 20);
			ofRotateZ(-(leavesNum - 1) * deg * 0.5);
			for (int i = 0; i < leavesNum; i++) {
				float radius = ofRandom(organicRadiusMinSlider, organicRadiusMaxSlider);
				float newX = cos(rad*i - PI / 2) * radius;
				float newY = sin(rad*i - PI / 2) * radius;
				ofPushMatrix();
				ofTranslate(newX, newY, 0);
				ofRotateZ(deg * i);
				ofSetLineWidth(2);
				if (drawGridToggle) { drawCross(0, 0, 20); }
				drawSelectImage(mainImgSelectSlider, 0, 0);
				ofPopMatrix();
			}
			ofPopMatrix();
		}
	}


	void drawSelectImage(int _imgIndex, int _x, int _y) {
		currentW = originalW * mainScaleSlider;
		currentH = originalH * mainScaleSlider;
		if (mainRandomScaleToggle) {
			float value = ofRandom(mainRandomScaleMinSlider, mainRandomScaleMaxSlider);
			currentW = currentW * value;
			currentH = currentH * value;
		}

		float degreeZ = ofRandom(-mainAngleRangeZSlider, mainAngleRangeZSlider);
		float degreeX = ofRandom(-mainAngleRangeXSlider, mainAngleRangeXSlider);
		float degreeY = ofRandom(-mainAngleRangeYSlider, mainAngleRangeYSlider);
		float zPos = ofRandom(500);

		ofPushMatrix();
		ofTranslate(_x, _y, 0);

		ofPushMatrix();
		if (mainRandomRotationToggle) {
			//ofTranslate(0, 0, -zPos);
			ofRotateX(degreeX);
			ofRotateY(degreeY);
			ofRotateZ(degreeZ);
		}
		if (mainRandomAlphaToggle) { ofSetColor(255, ofRandom(mainRandomAlphaMinSlider, mainRandomAlphaMaxSlider)); }
		else { ofSetColor(255, mainAlphaSlider); }
		if (arrangeToGridToggle) { imgs[_imgIndex].setAnchorPercent(0.5, 0.5); }
		else { imgs[_imgIndex].setAnchorPercent(0.5, 1.0); }
		imgs[_imgIndex].draw(0, 0, currentW, currentH);
		ofPopMatrix();

		ofPopMatrix();
	}

	void drawRandomImage(int _x, int _y) {
		drawSelectImage(int(ofRandom(0, imgs.size())), _x, _y);
	}

	void drawCross(const int& _x, const int& _y, const int& _size) {
		glLineWidth(2);
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

	void saveChecker() {
		if (drawAreaBGToggle) { drawAreaBGToggle = false; saveCheckerID01 = true; }
		if (drawAreaOUTToggle) { drawAreaOUTToggle = false; saveCheckerID02 = true; }
		if (drawGridToggle) { drawGridToggle = false; saveCheckerID03 = true; }
	}

	void saveImage() {
		string _fileName = "../EXPORTED/screenShots/" + ofToString(ofGetMonth()) + ofToString(ofGetDay()) + ofToString(ofGetHours()) + ofToString(ofGetMinutes()) + ofToString(ofGetSeconds()) + ".png";
		ofImage _imgToSave;
		_imgToSave.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		_imgToSave.save(_fileName, OF_IMAGE_QUALITY_BEST);
		std::cout << "img : " + _fileName + " -exported" << std::endl;
		if (saveCheckerID01) { drawAreaBGToggle = true; saveCheckerID01 = false; }
		if (saveCheckerID02) { drawAreaOUTToggle = true; saveCheckerID02 = false; }
		if (saveCheckerID03) { drawGridToggle = true; saveCheckerID03 = false; }
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




	//----------DEFAULT-OTHER-----------//
	void keyPressed(int key) {
		switch (key) {
		case 'f':
			ofToggleFullscreen();
			break;
		case 's':
			//saveImage();
			saveFBOtoImage(&fbo);
			break;
			}
	};
	void keyReleased(int key) {
	};
	void mouseMoved(int x, int y) {
	};
	void mouseDragged(int x, int y, int button){
	};
	void mousePressed(int x, int y, int button) {
	};
	void mouseReleased(int x, int y, int button) {
	};
	void mouseEntered(int x, int y) {
	};
	void mouseExited(int x, int y) {
	};
	void windowResized(int w, int h){
	};
	void dragEvent(ofDragInfo dragInfo) {
	};
	void gotMessage(ofMessage msg) {
	};
		
};
