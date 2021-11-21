#pragma once

#include "Walker.h"
#include "ofMain.h"
#include "ofxAssimpModelLoader/src/ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	//my defs
	void initSetting();
	void initParam();
	void ui();
	void makeGrid(int _gridSize);
	void makeDimension();
	void func01(float _x, float _y, float _dThickness);
	void func02(float _x, float _y, float _dThickness);
	void func03(ofPoint _pos);
	void func04();
	void func05(ofPoint _pos);
	void func06(float _size, float _angle);
	void func07();
	void func08(float _threeDModel_angle,float _angle);
	void func09();

	//my class
	ofTrueTypeFont font;
	ofxAssimpModelLoader threeDModel;
	Walker walker;
	ofFbo fbo01;



	//global param
	int currentFrame;
	float X, Y;
	float deltaThickness;
	float func06Size,func06Angle;
	float func08Angle;

	static const int num_walker = 4;
	Walker walkers[num_walker];

	int tmpFrame;
	int fontSize;


};