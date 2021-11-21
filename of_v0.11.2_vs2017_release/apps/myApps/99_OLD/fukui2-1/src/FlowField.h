#pragma once

#include "ofMain.h"

class FlowField {

public:
	//FLowFiled(int _r) {}
	FlowField(int _r);
	void init();
	void update();
	void display();
	void drawVector(ofVec2f _v, float _x, float _y, float _scayl);
	ofVec2f lookup(ofVec2f _vecToLookup);

private:
	//vector<vector<ofVec2f>> field;
	int cols, rows;
	int resolution;
	float zoff;

};