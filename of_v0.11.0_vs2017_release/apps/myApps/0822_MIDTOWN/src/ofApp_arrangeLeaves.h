#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSvg.h"
#include "ofxOpenCv.h"
#include "ofEasyCam.h"

class ofApp : public ofBaseApp {

public:
	//-----------ToDo-----------//
	//画質 (FBO)
	//blur
	//z_sort
	//２段階 + 合成 orアルファ写真作成

	//-----------IMPORT-----------//
	ofxPanel gui;
	ofTrueTypeFont font;
	ofEasyCam cam;

	//-----------GLOBAL-----------//
	float time;
	float fontSize;

	ofRectangle area;
	ofImage imgToSave;
	
	ofxCvGrayscaleImage imgGray;
	ofxCvColorImage imgBlur;
	
	
	ofImage imgA, imgB, imgC, imgD ,imgE, imgF, imgG;
	ofImage imgs[7];

	ofImage sdwA, sdwB, sdwC, sdwD, sdwE, sdwF, sdwG;
	ofImage sdws[7];


	float originalW, originalH;
	float currentW, currentH;


	//-----------SLIDER-----------//
	ofxIntSlider areaWidthSlider;
	ofxIntSlider areaHeightSlider;
	ofxIntSlider xNumSlider;
	ofxIntSlider yNumSlider;
	ofxFloatSlider scaleSlider;
	ofxFloatSlider distSliderX;
	ofxFloatSlider distSliderY;
	ofxFloatSlider offsetShadowSliderX;
	ofxFloatSlider offsetShadowSliderY;
	ofxFloatSlider shadowScaleSlider;
	ofxFloatSlider shadowAlphaSlider;
	ofxIntSlider seedSlider;
	ofxIntSlider angleRangeSliderZ;
	ofxIntSlider angleRangeSliderX;
	ofxIntSlider angleRangeSliderY;
	ofxFloatSlider blurSlider;

	ofxToggle gridToggle;
	ofxToggle randomRotationToggle;

	ofxButton saveButton;


	//----------MAIN-----------//

	void setup() {

		std::cout << "Script Begins !" << std::endl;

		//---initParam---//
		fontSize = 12;

		//---loading---//
		//img
		imgA.load("./img_leaves/A.png");
		imgB.load("./img_leaves/B.png");
		imgC.load("./img_leaves/C.png");
		imgD.load("./img_leaves/D.png");
		imgE.load("./img_leaves/E.png");
		imgF.load("./img_leaves/F.png");
		imgG.load("./img_leaves/G.png");
		imgs[0] = imgA;
		imgs[1] = imgB; 
		imgs[2] = imgC;  
		imgs[3] = imgD; 
		imgs[4] = imgE; 
		imgs[5] = imgF; 
		imgs[6] = imgG;
		originalW = imgA.getWidth();
		originalH = imgA.getHeight();

		//sdw
		sdwA.load("./img_leaves/sdwA.png");
		sdwB.load("./img_leaves/sdwB.png");
		sdwC.load("./img_leaves/sdwC.png");
		sdwD.load("./img_leaves/sdwD.png");
		sdwE.load("./img_leaves/sdwE.png");
		sdwF.load("./img_leaves/sdwF.png");
		sdwG.load("./img_leaves/sdwG.png");
		sdws[0] = sdwA;
		sdws[1] = sdwB;
		sdws[2] = sdwC;
		sdws[3] = sdwD;
		sdws[4] = sdwE;
		sdws[5] = sdwF;
		sdws[6] = sdwG;



		//font
		ofTrueTypeFont::setGlobalDpi(72);
		font.load("font/SourceCodePro-Light.ttf", fontSize);
		font.setLineHeight(fontSize);
		font.setLetterSpacing(1.0);

		//---sliders---//
		/*  gui.add(slider.setup("sliderName", initial, min, max); */
		
		gui.setup();
		gui.add(areaWidthSlider.setup("areaWidth", 500, 400, 800));
		gui.add(areaHeightSlider.setup("areaHeight", 500, 400, 800));
		gui.add(xNumSlider.setup("xNum", 3, 1, 20));
		gui.add(yNumSlider.setup("yNum", 3, 1, 20));
		gui.add(scaleSlider.setup("scale", 0.1, 0.01,0.2));
		gui.add(distSliderX.setup("distX", 60,10,200));
		gui.add(distSliderY.setup("distY", 60, 10, 200));
		gui.add(offsetShadowSliderX.setup("offsetShadowX", 0, -20, 20));
		gui.add(offsetShadowSliderY.setup("offsetShadowY", 0, -20, 20));
		gui.add(shadowScaleSlider.setup("shadowscale", 1.0, 0.8, 2.0));
		gui.add(shadowAlphaSlider.setup("shadowAlpha", 30, 0, 200));
		gui.add(seedSlider.setup("seed", 0, 0, 50));
		gui.add(angleRangeSliderZ.setup("angleRangeZ", 45, 0, 180));
		gui.add(angleRangeSliderX.setup("angleRangeX", 0, 0, 180));
		gui.add(angleRangeSliderY.setup("angleRangeY", 45, 0, 180));
		gui.add(blurSlider.setup("blur", 9, 5, 13));
		
		gui.add(gridToggle.setup("showGrid", true));
		gui.add(randomRotationToggle.setup("random rotation", false));

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

	}
	
	void update() {
		time = ofGetElapsedTimef();
	}
	
	void draw() {
		
		cam.begin();
		ofPushMatrix();
		ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2,0);
		arrangeToGrid();
		ofPopMatrix();
		cam.end();

		if (gridToggle) {
			showGrid();
		}
		setArea();
		
		info();
		gui.draw();
		if (saveButton) {
			saveImage();
		}
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
		ofNoFill();
		ofSetLineWidth(1);
		ofSetColor(255, 255);
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		area = ofRectangle(-areaWidthSlider / 2, -areaHeightSlider / 2, areaWidthSlider, areaHeightSlider);
		ofDrawRectangle(area);
		ofPopMatrix();
	}


	void showGrid() {
		ofNoFill();
		ofSetLineWidth(1);
		ofSetColor(255, 100);
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2 -distSliderX * xNumSlider/2, ofGetHeight() / 2 - distSliderY * yNumSlider/2);
		for (int y = 0; y < yNumSlider+1; y++) {
			for (int x = 0; x < xNumSlider+1; x++) {
				drawCross(x * distSliderX, y * distSliderY, 20, 20);
			}
		}
		ofPopMatrix();
		ofSetColor(255, 255);
	}

	void arrangeToGrid() {
		ofSetColor(255, 255);
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2 - distSliderX * xNumSlider / 2, ofGetHeight() / 2 - distSliderY * yNumSlider / 2);
		ofSeedRandom(seedSlider);
		for (int y = 0; y < yNumSlider + 1; y++) {
			for (int x = 0; x < xNumSlider + 1; x++) {
				drawRandomImage(x * distSliderX, y * distSliderY);
			}
		}
		ofPopMatrix();
	}


	void drawSelectImage(int _imgIndex, int _x, int _y) {
		currentW = originalW * scaleSlider;
		currentH = originalH * scaleSlider;

		float degreeZ = ofRandom(-angleRangeSliderZ,angleRangeSliderZ);
		float degreeX = ofRandom(-angleRangeSliderX, angleRangeSliderX);
		float degreeY = ofRandom(-angleRangeSliderY, angleRangeSliderY);
		float zPos = ofRandom(500);

		sdws[_imgIndex].setAnchorPercent(0.5, 0.5);
		imgs[_imgIndex].setAnchorPercent(0.5, 0.5);
		
		ofPushMatrix();
		ofTranslate(_x, _y ,0);
		
		//--shadow
		ofPushMatrix();
		ofTranslate(offsetShadowSliderX, offsetShadowSliderY, 0);
		if (randomRotationToggle) {
			//ofTranslate(0, 0, -zPos);		
			ofRotateX(degreeX);
			ofRotateY(degreeY);
			ofRotateZ(degreeZ);
		}		
		ofSetColor(255, shadowAlphaSlider);
		sdws[_imgIndex].draw(0,0, currentW*shadowScaleSlider, currentH*shadowScaleSlider);
		ofPopMatrix();

		//--real
		ofPushMatrix();
		if (randomRotationToggle) {
			//ofTranslate(0, 0, -zPos);
			ofRotateX(degreeX);
			ofRotateY(degreeY);
			ofRotateZ(degreeZ);
		}
		ofSetColor(255, 255);
		imgs[_imgIndex].draw(0, 0, currentW,currentH);
		ofPopMatrix();

		ofPopMatrix();
	}

	void drawRandomImage( int _x, int _y) {
		drawSelectImage(int(ofRandom(0, 6)), _x, _y);
	}

	void drawCross(int _x, int _y, int _sizeX, int _sizeY) {
		ofPushMatrix();
		ofTranslate(_x, _y);
		ofDrawLine(-_sizeX / 2, 0, _sizeX / 2, 0);
		ofDrawLine(0, -_sizeY / 2, 0, _sizeY / 2);
		ofPopMatrix();
	}

	void shadowEditer(int _x, int _y) {
	}

	void saveImage() {
		string fileName = "../EXPORTED/screenShots/" + ofToString(ofGetMonth()) + ofToString(ofGetDay())+ofToString(ofGetHours()) + ofToString(ofGetMinutes()) + ofToString(ofGetSeconds()) + ".png";
		imgToSave.grabScreen(ofGetWidth() / 2 + area.x, ofGetHeight() / 2 + area.y, area.getWidth(), area.getHeight());
		imgToSave.save(fileName, OF_IMAGE_QUALITY_BEST);
		std::cout << "img : " + fileName + " -exported" << std::endl;
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
