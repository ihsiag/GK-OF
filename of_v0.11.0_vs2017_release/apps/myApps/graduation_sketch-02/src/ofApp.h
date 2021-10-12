#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofEasyCam.h"
#include "ofCamera.h"
#include "ofxGui.h"
#include "ofxPostProcessing.h"

//
#include "Class_MyFunctions.h"
#include "Class_ScanModel.h"
#include "Class_AnalyseModel.h"
#include "Class_RecreateModel.h"




class ofApp : public ofBaseApp {

public:

	//-----------IMPORT
	Class_MyFunctions mf;
	Class_ScanModel scanModel;
	Class_AnalyseModel analyseModel;
	Class_RecreateModel recreateModel;
	ofCamera cam;
	ofEasyCam ezCam;
	ofTrueTypeFont font;
	ofxPostProcessing post;
	ofxPanel gui;

	ofShader shaderMesh;
	ofShader shaderPost;
	
	ofMesh meshScan;
	ofMesh meshCreate;
	//ofxAssimpModelLoader model;

	vector <glm::vec3> arrResultAnalyseModel;
	
	//ofVboMesh vboMesh;
	ofFbo fbo;

	//-----------GLOBAL
	float time;
	float currentFrame = -1.0;
	int fontSize = 10;

	bool bFirst;//scan
	bool bSecond;//analysis
	bool bThird;//create

	bool bUpdateCamera;
	bool bShowInfo;

	//-----------Sliders
	ofxFloatSlider modelShaderAlpha;




	//-----------STRUCTURE
	void setup() {
		mf.setup(&ezCam);
		
		bFirst = true;
		bSecond = false;
		bThird = false;
		bUpdateCamera = true;
		bShowInfo = true;

		meshScan.load("./3D/can_piece_remesh02.ply");
		scanModel.setup(&meshScan,&ezCam);
		analyseModel.setup(&meshScan, &arrResultAnalyseModel);
		recreateModel.setup(&meshCreate, &arrResultAnalyseModel, &ezCam);
	
	}

	void update() {
		mf.defaultUpdate(&currentFrame,&time);
		if(bUpdateCamera)updateCamera();
	}

	void draw() {

		//update();	

		//-----------PhaseBEGIN
		if (bFirst) { bSecond = scanModel.run(); }
		if (bSecond) { bFirst = false; bThird = analyseModel.run();}
		if (bThird) { bSecond = false; recreateModel.run(); }
		//-----------PhaseEND

		//-----------FrontLayerBEGIN
		mf.makeGrid();
		vector <string> infoList = {
			"currentFrame : "+ofToString(currentFrame),
			"frameRate : "+ofToString(ofGetFrameRate()),
			"time_passed : "+ofToString(time)
		};
		if(bShowInfo)mf.showInfo(&infoList,&fontSize);
		//-----------FrontLayerEND
	}


	//-----------ThisTimeFunctions
	void updateCamera() {
		int camValue = 200;
		float camRotationSpeed = currentFrame / 360;
		ezCam.setPosition(camValue * sin(camRotationSpeed), camValue * cos(camRotationSpeed), camValue);
		ezCam.lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
	}

	void keyPressed(int key) {
		switch (key) {
		case 'f':
			ofToggleFullscreen();
			break;
		case 'i':
			bShowInfo = !bShowInfo;
			break;
		case 's':
			mf.saveImage();
			break;
		}
	}
	
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int _x, int _y, int _button) {
		bUpdateCamera = false;
	}
	void mousePressed(int _x, int _y, int _button) {
	}
	void mouseReleased(int _x, int _y, int _button) {
		bUpdateCamera = true;
	}
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h) {
	}
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


};
