#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSvg.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp {

public:
	//-----------IMPORT-----------//
	ofxPanel gui;
	ofTrueTypeFont font;

	//-----------GLOBAL-----------//
	float time;
	float fontSize;

	ofRectangle area;
	ofImage imgToSave;
	
	ofxCvGrayscaleImage imgGray;
	ofxCvColorImage imgBlur;
	
	ofImage imgA, imgB, imgC, imgD ,imgE, imgF, imgG;


	//-----------SLIDER-----------//
	ofxIntSlider areaWidthSlider;
	ofxIntSlider areaHeightSlider;
	ofxIntSlider xNumSlider;
	ofxIntSlider yNumSlider;
	ofxFloatSlider scaleSlider;
	ofxFloatSlider distSliderX;
	ofxFloatSlider distSliderY;
	ofxFloatSlider blurSlider;


	//----------MAIN-----------//

	void setup() {

		std::cout << "Script Begins !" << std::endl;

		//---initParam---//
		fontSize = 10;

		//---loading---//
		//img
		imgA.load("./img_leaves/A.png");
		imgB.load("./img_leaves/B.png");
		imgC.load("./img_leaves/C.png");
		imgD.load("./img_leaves/D.png");
		imgE.load("./img_leaves/E.png");
		imgF.load("./img_leaves/F.png");
		imgG.load("./img_leaves/G.png");


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
		gui.add(xNumSlider.setup("xNum", 10, 1, 20));
		gui.add(yNumSlider.setup("yNum", 10, 1, 20));
		gui.add(scaleSlider.setup("scale", 0.1, 0.01,0.1));
		gui.add(distSliderX.setup("distX", 20,10,100));
		gui.add(distSliderY.setup("distY", 20, 10, 100));
		gui.add(blurSlider.setup("blur", 9, 5, 13));

		//---basic---//

		ofSetBackgroundAuto(true);
		ofSetBackgroundColor(0, 0, 0);
		ofEnableAlphaBlending();
		//ofEnableBlendMode(); //OF_BLENDMODE_DISABLED, OF_BLENDMODE_ALPHA, OF_BLENDMODE_ADD, OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_SCREEN
		ofSetFrameRate(30);
		ofEnableAntiAliasing();

	}
	void update() {
		ofSetWindowTitle(ofToString(ofGetFrameRate()));
		time = ofGetElapsedTimef();
	}
	void draw() {
		
		arrangeToGridSelect(imgA);
		//arrangeToGridRandom();
		
		setArea();
		setGrid();
		info(10, ofGetHeight() * 0.9);
		gui.draw();
	}
	
	//----------CUSTOMFUNCS-----------//

	void info(float _x, float _y) {
		string infoData = "-Press S to save image-";
		ofRectangle bb = font.getStringBoundingBox(infoData,0,0);
		ofSetColor(0,80);
		ofFill();
		ofDrawRectangle(_x-fontSize/2,_y-fontSize/2-bb.height,bb.width+fontSize,bb.height+fontSize);
		ofSetColor(255,255);
		font.drawString(infoData, _x, _y);	
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


	void setGrid() {
		ofNoFill();
		ofSetLineWidth(1);
		ofSetColor(255, 100);
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2 -distSliderX * xNumSlider/2, ofGetHeight() / 2 - distSliderY * yNumSlider/2);
		for (int y = 0; y < yNumSlider+1; y++) {
			for (int x = 0; x < xNumSlider+1; x++) {
				drawCross(x * distSliderX, y * distSliderY,distSliderX,distSliderY);
			}
		}
		ofPopMatrix();
		ofSetColor(255, 255);
	}


	void arrangeToGridSelect(ofImage _img) {
		_img.setAnchorPercent(0.5, 0.5);
		float aW = _img.getWidth();
		float aH = _img.getHeight();
		aW = aW * scaleSlider;
		aH = aH * scaleSlider;

		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2 - distSliderX * xNumSlider / 2, ofGetHeight() / 2 - distSliderY * yNumSlider / 2);
		for (int y = 0; y < yNumSlider+1; y++) {
			for (int x = 0; x < xNumSlider+1; x++) {
			_img.draw(x * distSliderX, y * distSliderY, aW,aH);
			drawDroppedShadhow(_img, x * distSliderX, y * distSliderY, aW, aH);
			}
		}
		ofPopMatrix();
	}

	void arrangeToGridSelect() {

	}

	void drawCross(int _x, int _y, int _sizeX, int _sizeY) {
		ofPushMatrix();
		ofTranslate(_x, _y);
		ofDrawLine(-_sizeX / 2, 0, _sizeX / 2, 0);
		ofDrawLine(0, -_sizeY / 2, 0, _sizeY / 2);
		ofPopMatrix();
	}

	void drawDroppedShadhow(ofImage _img, int _x, int _y, int _w, int _h) {
		imgGray.allocate(_img.getWidth(), _img.getHeight());
		imgBlur.allocate(_img.getWidth(), _img.getHeight());
		imgGray = _img.getPixels();
		imgBlur = imgGray;
		imgBlur.blur(blurSlider);
		imgBlur.draw(_x, _y, _w, _h);
	}

	
	
	
	void drawSample(ofImage _img) {
		float aW = _img.getWidth();
		float aH = _img.getHeight();
		aW = aW * scaleSlider;
		aH = aH * scaleSlider;


		for (int y = 0; y < yNumSlider; y++) {
			for (int x = 0; x < xNumSlider; x++) {
				ofPushMatrix();
				ofTranslate(x * distSliderX, y * distSliderY);
				imgA.draw(-aW/2,-aH/2, aW, aH);
				ofPopMatrix();
			}
		}
	}





	//----------DEFAULT-OTHER-----------//
	void keyPressed(int key) {
		if (key == 's') {
			imgToSave.grabScreen(ofGetWidth() / 2 + area.x, ofGetHeight() / 2 + area.y, area.getWidth(), area.getHeight());
			imgToSave.save("ofScreenShot.png");
			std::cout << "img exported" << std::endl;
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
