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
	ofxFloatSlider blurSlider;

	ofxToggle gridToggle;
	ofxToggle randomRotationToggle;


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
		gui.add(blurSlider.setup("blur", 9, 5, 13));
		
		gui.add(gridToggle.setup("showGrid", true));
		gui.add(randomRotationToggle.setup("random rotation", false));

		//---basic---//

		ofSetBackgroundAuto(true);
		ofSetBackgroundColor(220);
		ofEnableAlphaBlending();
		//ofEnableBlendMode(); //OF_BLENDMODE_DISABLED, OF_BLENDMODE_ALPHA, OF_BLENDMODE_ADD, OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_SCREEN
		ofSetFrameRate(30);
		ofEnableAntiAliasing();
		//ofEnableDepthTest();

	}
	void update() {
		ofSetWindowTitle(ofToString(ofGetFrameRate()));
		time = ofGetElapsedTimef();
	}
	void draw() {

		arrangeToGrid();
		if (gridToggle) {
			showGrid();
		}
		setArea();
		
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
				//drawSelectImage(imgs[1], x * distSliderX, y * distSliderY);
				drawRandomImage(x * distSliderX, y * distSliderY);
			}
		}
		ofPopMatrix();
	}


	void drawSelectImage(int _imgIndex, int _x, int _y) {
		currentW = originalW * scaleSlider;
		currentH = originalH * scaleSlider;

		sdws[_imgIndex].setAnchorPercent(0.5, 0.5);
		imgs[_imgIndex].setAnchorPercent(0.5, 0.5);
		ofPushMatrix();
		ofTranslate(_x, _y);
		if (randomRotationToggle) {
			ofRotate(ofRandom(360));
		}
		ofSetColor(255, shadowAlphaSlider);
		sdws[_imgIndex].draw(offsetShadowSliderX, offsetShadowSliderY, currentW*shadowScaleSlider, currentH*shadowScaleSlider);
		ofSetColor(255, 255);
		imgs[_imgIndex].draw(0, 0, currentW,currentH);
		ofPopMatrix();
	}


	void drawRandomImage( int _x, int _y) {
		drawSelectImage(int(ofRandom(0, 6)), _x, _y);
	}

	
	void drawDroppedShadhow(ofImage _img, int _x, int _y, int _w, int _h) {
		imgGray.allocate(_img.getWidth(), _img.getHeight());
		imgBlur.allocate(_img.getWidth(), _img.getHeight());
		ofPixels pixels = _img.getPixels();
		imgGray.setFromPixels(pixels);
		/*imgBlur = imgGray;
		imgBlur.blur(blurSlider);
		imgBlur.draw(_x, _y, _w, _h);*/
		imgGray.draw(_x, _y, _w, _h);
	}

	void drawCross(int _x, int _y, int _sizeX, int _sizeY) {
		ofPushMatrix();
		ofTranslate(_x, _y);
		ofDrawLine(-_sizeX / 2, 0, _sizeX / 2, 0);
		ofDrawLine(0, -_sizeY / 2, 0, _sizeY / 2);
		ofPopMatrix();
	}



	
	void drawSample(ofImage _img) {
		float currentW = _img.getWidth();
		float currentH = _img.getHeight();
		currentW = currentW * scaleSlider;
		currentH = currentH * scaleSlider;


		for (int y = 0; y < yNumSlider; y++) {
			for (int x = 0; x < xNumSlider; x++) {
				ofPushMatrix();
				ofTranslate(x * distSliderX, y * distSliderY);
				imgA.draw(-currentW/2,-currentH/2, currentW, currentH);
				ofPopMatrix();
			}
		}
	}





	//----------DEFAULT-OTHER-----------//
	void keyPressed(int key) {
		if (key == 's') {
			string fileName = "../EXPORTED/screenShots/" + ofToString(ofGetMonth()) + ofToString(ofGetHours()) + ofToString(ofGetMinutes()) + ofToString(ofGetSeconds()) + ".png";
			imgToSave.grabScreen(ofGetWidth() / 2 + area.x, ofGetHeight() / 2 + area.y, area.getWidth(), area.getHeight());
			imgToSave.save(fileName, OF_IMAGE_QUALITY_BEST);
			std::cout << "img" + fileName + "exported" << std::endl;
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
