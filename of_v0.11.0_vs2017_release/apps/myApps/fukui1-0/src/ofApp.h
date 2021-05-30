#pragma once

#include "ofMain.h"
#include "walker.h"
#include "particle.h"
#include "ofxAssimpModelLoader/src/ofxAssimpModelLoader.h"


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int _key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	//my defs------------------------------------------------
	//
	void initSetting();
	void initParam();
	void ui();
	bool funcDo(bool _bool, float _origin, float _period, float _ss, float _es, int _currentFrame);
	
	//
	void makeGrid();
	void makeDimension();
	
	//interaction
	void walkerFinder(ofPoint _pos);

	void func01(float _t);
	void func02(float _x, float _y, float _dThickness);
	

	void func04();
	void func05(ofPoint _pos);
	void func06(float _size, float _angle);
	void func07();
	void func08(float _threeDModel_angle,float _angle);
	void func09(float _t);
	void func10();
	void func11();


	//my class------------------------------------------------
	Walker walker;
	Particle particle;
	ofFbo fbo01;

	//data load------------------------------------------------
	ofTrueTypeFont font;
	ofxAssimpModelLoader threeDModel;

	


	//global param essential------------------------------------------------
	int id_init;
	int currentFrame;
	int sec;
	float oneCool;
	int fontSize;

	/*
	static const int num_walker = 4;
		Walker walkers[num_walker];
	*/

	vector <Walker> walkerArray;
	vector <Particle> ringCenter_particleArray;

	static const int num_particle = 8000;
	Particle particles[num_particle];



	//global param func------------------------------------------------
	float func01T;
	float func06T,func06Angle;
	float func08Angle;
	float func09T;

	bool boolWalkerDisplay;
	bool boolWalkerFinder;
	bool boolFunc04;
	bool boolFunc06;
	bool boolFunc07;
	bool boolFunc09;
	bool boolFunc10;
	bool boolFunc11;
	bool boolFbo01;
	


};