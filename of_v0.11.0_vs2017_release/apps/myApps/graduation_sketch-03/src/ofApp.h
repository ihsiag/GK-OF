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
#include "Class_Box2DStudy.h"
#include "Class_Delaunay.h"
#include "Class_Buckling_A.h"




class ofApp : public ofBaseApp {

public:

	//-----------IMPORT
	Class_MyFunctions mf;
	Class_ScanModel scanModel;
	Class_AnalyseModel analyseModel;
	Class_RecreateModel recreateModel;
	Class_Box2dStudy box2dStudy;
	Class_Delaunay delaunay;
	Class_Buckling buckling;
	
	ofCamera cam;
	ofEasyCam ezCam;
	ofTrueTypeFont font;
	ofxPostProcessing post;
	ofxPanel gui;

	ofShader shaderMesh;
	ofShader shaderPost;
	
	ofMesh meshScan;
	ofMesh meshCreate;

	vector <glm::vec3> arrResultAnalyseModel;
	vector<shared_ptr<ofxBox2dCircle>> circles;
	
	//ofVboMesh vboMesh;
	ofFbo fbo;

	//-----------GLOBAL
	float time;
	float currentFrame;
	int fontSize;
	int camValue;

	bool bFirst;//scan
	bool bSecond;//analysis
	bool bThird;//box2d-vertex-xy
	bool bFourth;//delaunary-mesh-xy
	bool bFifth;//recreateModel-mesh-z
	bool bSixth;//temporary END

	bool bUpdateCamera;
	bool bShowInfo;

	//-----------Sliders
	ofxFloatSlider modelShaderAlpha;




	//-----------STRUCTURE
	void setup() {
		currentFrame = -1.0;
		camValue = 200;
		fontSize = 10;
		
		bFirst = false;
		bSecond = false;
		bThird = true;
		bFourth = false;
		bFifth = false;
		bSixth = false;
		
		bUpdateCamera = true;
		bShowInfo = true;


		//free
		vector <glm::vec3>().swap(arrResultAnalyseModel);
		vector<shared_ptr<ofxBox2dCircle>>().swap(circles);
		
		meshScan.load("./3D/can_piece_remesh02.ply");
		scanModel.setup(&meshScan,&ezCam);
		analyseModel.setup(&meshScan, &arrResultAnalyseModel);
		recreateModel.setup(&meshCreate, &arrResultAnalyseModel, &ezCam);
		box2dStudy.setup(&circles,&ezCam);
		delaunay.setup(&circles,&ezCam);
		buckling.setup(&meshScan, &ezCam)


		mf.setup(&ezCam);
	
	}

	void update() {
		mf.defaultUpdate(&currentFrame,&time);
		if(bUpdateCamera)updateCamera();
	}

	void draw() {

		//update();	

		//-----------StagesBEGIN
		
		if (bFirst) { bSecond = scanModel.run(); }
		if (bSecond) { bFirst = false; bThird = analyseModel.run();}
		if (bThird) { bSecond = false; bFourth = box2dStudy.run(); }
		//if (bFourth) { bThird = false; bFifth = delaunay.run(); }
		if (bThird) { bSecond = false; bFourth = delaunay.run(); }
		if (bFifth) { bFourth = false; bSixth = recreateModel.run(); }

		//-----------StagesEND

		
		
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
		case 'c':
			box2dStudy.addElement(glm::vec2(mouseX, mouseY));
			break;
		case 's':
			mf.saveImage();
			break;
		case 'r':
			delaunay.setup(&circles,&ezCam);
			//setup();
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			camValue = 400;
			camValue /= 1 + key - '1';
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
