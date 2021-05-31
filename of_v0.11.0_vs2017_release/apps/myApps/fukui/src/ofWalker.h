#pragma once
#define _OF_WALKER

#include "ofMain.h"

class ofWalker {
public:
	void update();
	void applyForce(ofVec2f _force);
	void seek(ofVec2f _target);
	void output(); 
	ofWalker(float _x, float _y);

private:
	//class param
	ofVec2f location;
	ofVec2f velocity;
	ofVec2f acceleration;
	float r;
	float maxforce;
	float maxspeed;	
};

