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
	ofPixels pixels;
	ofShader shader;

	//-----------GLOBAL-----------//
	float time;
	float fontSize;

	ofRectangle area;

	ofImage imgA, imgB;
	static const int loadingImgNum = 1;
	ofImage imgs[loadingImgNum];

	ofImage sdwA;
	ofImage sdws[loadingImgNum];

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

	ofxFloatSlider offsetShadowXSlider;
	ofxFloatSlider offsetShadowYSlider;
	ofxFloatSlider offsetShadowScaleSlider;
	ofxFloatSlider offsetShadowAlphaSlider;

	ofxFloatSlider blurSlider;

	ofxButton saveButton;


	//----------MAIN-----------//

	void setup() {

		std::cout << "Script Begins !" << std::endl;

		//---initParam---//
		fontSize = 12;

		//---loading---//
		//img
		imgA.load("./img_leavesGray/grayA.png");

		imgs[0] = imgA;

		originalW = imgA.getWidth();
		originalH = imgA.getHeight();

		//sdw
		sdwA.load("./img_leavesGray/sdwA.png");
		sdws[0] = sdwA;


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
		gui.add(drawAreaOUTToggle.setup("drawAreaOUT", true));
		gui.add(drawGridToggle.setup("drawGrid", true));
		gui.add(arrangeToGridToggle.setup("arrangeToGrid", true));

		gui.add(mainRandomImgToggle.setup("mainRandomImg", false));
		gui.add(mainRandomRotationToggle.setup("mainRandomRotation", false));
		gui.add(mainRandomScaleToggle.setup("mainRandomScale", false));
		gui.add(mainRandomAlphaToggle.setup("mainRandomAlpha", false));

		gui.add(areaWidthSlider.setup("areaWidth", 4000, 800, 4000));
		
		gui.add(areaHeightSlider.setup("areaHeight", 4000, 800, 4000));
		gui.add(gridNumXSlider.setup("gridNumX", 3, 1, 45));
		gui.add(gridNumYSlider.setup("gridNumY", 3, 1, 45));
		gui.add(gridDistXSlider.setup("gridDistX", 60,10,200));
		gui.add(gridDistYSlider.setup("gridDistY", 60, 10, 200));
		gui.add(offGridMinSlider.setup("offGridMin", 0, 0, gridDistXSlider * 2));
		gui.add(offGridMaxSlider.setup("offGridMax", 0, 0, gridDistXSlider * 4));

		gui.add(organicCenterNumSlider.setup("organicCenterNum", 30, 10, 1000));
		gui.add(organicRadiusMinSlider.setup("organicRadiusMin", 50, 0, 200));
		gui.add(organicRadiusMaxSlider.setup("organicRadiusMax", 100, 0, 500));
		gui.add(organicLeavesNumMinSlider.setup("organicLeavesNumMin", 2, 1, 10));
		gui.add(organicLeavesNumMaxSlider.setup("organicLeavesNumMax", 12, 3, 20));
		gui.add(organicDegreeMinSlider.setup("organicDegreeMin", 20, 5, 80));
		gui.add(organicDegreeMaxSlider.setup("organicDegreeMax", 20, 5, 80));

		gui.add(mainImgSelectSlider.setup("mainImgSelect", 0, 0, loadingImgNum - 1));
		gui.add(mainSeedSlider.setup("mainSeed", 0, 0, 50));
		gui.add(mainScaleSlider.setup("mainScale", 0.1, 0.01, 0.2));
		gui.add(mainRandomScaleMinSlider.setup("mainRandomScaleMin", 1.000, 0.000, 1.000));
		gui.add(mainRandomScaleMaxSlider.setup("mainRandomScaleMax", 1.200, 0.0000, 2.000));
		gui.add(mainAlphaSlider.setup("mainAlphaSlider", 255, 0, 255));
		gui.add(mainRandomAlphaMinSlider.setup("mainRandomAlphaMin", 0, 0, 255));
		gui.add(mainRandomAlphaMaxSlider.setup("mainRandomAlphaMax", 170, 0, 255));

		gui.add(mainAngleRangeZSlider.setup("mainAngleRangeZ", 45, 0, 180));
		gui.add(mainAngleRangeXSlider.setup("mainAngleRangeX", 0, 0, 180));
		gui.add(mainAngleRangeYSlider.setup("mainAngleRangeY", 45, 0, 180));

		gui.add(offsetShadowXSlider.setup("offsetShadowX", 0, -20, 20));
		gui.add(offsetShadowYSlider.setup("offsetShadowY", 0, -20, 20));
		gui.add(offsetShadowScaleSlider.setup("offsetShadowScale", 1.0, 0.8, 2.0));
		gui.add(offsetShadowAlphaSlider.setup("offsetShadowAlpha", 30, 0, 200));
		
		gui.add(blurSlider.setup("blur", 9, 5, 13));
		
		gui.add(saveButton.setup("save image"));

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
		ofEnableAlphaBlending();
		//ofEnableBlendMode(); //OF_BLENDMODE_DISABLED, OF_BLENDMODE_ALPHA, OF_BLENDMODE_ADD, OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_SCREEN
		ofSetFrameRate(30);
		ofEnableAntiAliasing();
		//ofEnableDepthTest();

		ofSetWindowTitle("MIDTOWN2021_TEXTUREMAKE : by Gaishi Kudo");

		fbo.allocate(4000, 4000, GL_RGBA);

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
			fbo.draw(-_tmpW/2,-_tmpH/2,_tmpW,_tmpH);
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
		if (saveButton)saveChecker();
		setArea();
		if (drawAreaBGToggle)drawAreaBG();

		cam.begin();
		ofPushMatrix();
		ofTranslate(-fbo.getWidth() / 2, -fbo.getHeight() / 2, 0);
		
		if (arrangeToGridToggle) { arrangeRandom(); }
		else { arrangeOrganic(); }
		
		ofPopMatrix();
		cam.end();

		if (drawGridToggle)showGrid();
		if (drawAreaOUTToggle)drawAreaOUT();
		if (saveButton)saveFBOtoImage();
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
			ofDrawRectangle(_x-fontSize/2, _y  - bb.height - fontSize/2+ (bb.height+fontSize)*i, bb.width+fontSize, bb.height+fontSize);
			ofSetColor(255, 255);
			font.drawString(infoData[i], _x, _y + (bb.height+fontSize)*i);
		}			
	}

	void setArea() {
		area = ofRectangle(-areaWidthSlider / 2, -areaHeightSlider / 2, areaWidthSlider, areaHeightSlider);	
	}

	void drawAreaBG() {
		ofPushMatrix();
		ofTranslate(fbo.getWidth() / 2, fbo.getHeight() / 2);
		ofFill();
		ofSetColor(50, 200, 50);
		ofDrawRectangle(area);
		ofPopMatrix();
	}

	void drawAreaOUT() {
		ofPushMatrix();
		ofTranslate(fbo.getWidth() / 2, fbo.getHeight() / 2);
		ofNoFill();
		ofSetLineWidth(1);
		ofSetColor(255, 255);
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
				drawCross(x * gridDistXSlider, y * gridDistYSlider, 20, 20);
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
				else{ drawSelectImage(mainImgSelectSlider, x * gridDistXSlider, y * gridDistYSlider); }
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
				if (mainRandomImgToggle) { drawRandomImage(x * gridDistXSlider+valueX, y * gridDistYSlider+valueY); }
				else { drawSelectImage(mainImgSelectSlider, x * gridDistXSlider+valueX, y * gridDistYSlider+valueY); }
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
			if (drawGridToggle)drawCross(0,0, 20, 20);
			ofRotateZ(-(leavesNum-1)*deg*0.5);
			for (int i = 0; i < leavesNum; i++) {
				float radius = ofRandom(organicRadiusMinSlider, organicRadiusMaxSlider);
				float newX =cos((rad)*i - PI / 2) * radius;
				float newY =sin((rad)*i - PI / 2) * radius;
				ofPushMatrix();
				ofTranslate(newX, newY, 0);
				ofRotateZ(deg * i);
				ofSetLineWidth(2);
				drawCross(0, 0, 20, 20);
				drawSelectImage(mainImgSelectSlider, 0,0);
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

		float degreeZ = ofRandom(-mainAngleRangeZSlider,mainAngleRangeZSlider);
		float degreeX = ofRandom(-mainAngleRangeXSlider, mainAngleRangeXSlider);
		float degreeY = ofRandom(-mainAngleRangeYSlider, mainAngleRangeYSlider);
		float zPos = ofRandom(500);

		
		
		ofPushMatrix();
		ofTranslate(_x, _y ,0);
		
		//--shadow
		ofPushMatrix();
		ofTranslate(offsetShadowXSlider, offsetShadowYSlider, 0);
		if (mainRandomRotationToggle) {
			//ofTranslate(0, 0, -zPos);		
			ofRotateX(degreeX);
			ofRotateY(degreeY);
			ofRotateZ(degreeZ);
		}		
		ofSetColor(255, offsetShadowAlphaSlider);
		if (arrangeToGridToggle) { sdws[_imgIndex].setAnchorPercent(0.5, 0.5); }
		else { sdws[_imgIndex].setAnchorPercent(0.5, 1.0); }
		sdws[_imgIndex].draw(0,0, currentW*offsetShadowScaleSlider, currentH*offsetShadowScaleSlider);
		ofPopMatrix();
		

		//--real
		ofPushMatrix();
		if (mainRandomRotationToggle) {
			//ofTranslate(0, 0, -zPos);
			ofRotateX(degreeX);
			ofRotateY(degreeY);
			ofRotateZ(degreeZ);
		}
		if (mainRandomAlphaToggle) {ofSetColor(255, ofRandom(mainRandomAlphaMinSlider, mainRandomAlphaMaxSlider));}
		else { ofSetColor(255, mainAlphaSlider); }
		if(arrangeToGridToggle){ imgs[_imgIndex].setAnchorPercent(0.5, 0.5); }
		else{ imgs[_imgIndex].setAnchorPercent(0.5, 1.0); }
		imgs[_imgIndex].draw(0, 0, currentW,currentH);
		ofPopMatrix();

		ofPopMatrix();
	}

	void drawRandomImage( int _x, int _y) {
		drawSelectImage(int(ofRandom(0, loadingImgNum)), _x, _y);
	}

	void drawCross(int _x, int _y, int _sizeX, int _sizeY) {
		ofPushMatrix();
		ofTranslate(_x, _y);
		ofDrawLine(-_sizeX / 2, 0, _sizeX / 2, 0);
		ofDrawLine(0, -_sizeY / 2, 0, _sizeY / 2);
		ofPopMatrix();
	}

	void saveChecker() {
		if (drawAreaBGToggle) { drawAreaBGToggle = false; saveCheckerID01 = true; }
		if (drawAreaOUTToggle) { drawAreaOUTToggle = false; saveCheckerID02 = true; }
		if (drawGridToggle) { drawGridToggle = false; saveCheckerID03 = true; }
	}


	void saveImage() {

		string fileName = "../EXPORTED/screenShots/" + ofToString(ofGetMonth()) + ofToString(ofGetDay())+ofToString(ofGetHours()) + ofToString(ofGetMinutes()) + ofToString(ofGetSeconds()) + ".png";
		imgToSave.grabScreen(ofGetWidth() / 2 + area.x, ofGetHeight() / 2 + area.y, area.getWidth(), area.getHeight());
		imgToSave.save(fileName, OF_IMAGE_QUALITY_BEST);
		std::cout << "img : " + fileName + " -exported" << std::endl;

		
		if (saveCheckerID01) {drawAreaBGToggle = true; saveCheckerID01 = false;}
		if (saveCheckerID02) {drawAreaOUTToggle = true; saveCheckerID02 = false;}
		if (saveCheckerID03) {drawGridToggle = true; saveCheckerID03 = false;}
	}

	void saveFBOtoImage() {

		string fileName = "../EXPORTED/screenShots/" + ofToString(ofGetMonth()) + ofToString(ofGetDay()) + ofToString(ofGetHours()) + ofToString(ofGetMinutes()) + ofToString(ofGetSeconds()) + ".png";
		fbo.readToPixels(pixels);
		imgToSave.setFromPixels(pixels);
		imgToSave.save(fileName, OF_IMAGE_QUALITY_BEST);
		std::cout << "img : " + fileName + " -exported" << std::endl;


		if (saveCheckerID01) { drawAreaBGToggle = true; saveCheckerID01 = false; }
		if (saveCheckerID02) { drawAreaOUTToggle = true; saveCheckerID02 = false; }
		if (saveCheckerID03) { drawGridToggle = true; saveCheckerID03 = false; }
	}




	//----------DEFAULT-OTHER-----------//
	void keyPressed(int key) {
		if (key == 's') {
			saveImage();
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
