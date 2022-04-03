#pragma once

#ifndef CLASS_SPHERE_H  
#define CLASS_SPHERE_H 

#include "GKScene.h"
#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"
#include "Easing.h"


class Sphere {
protected:
	float displayTime;
	float animationTime;
public:
	int gridUnit;
	ofSpherePrimitive sphere;
	int r;
	glm::vec3 initialPos;
	glm::vec3 pos;
	glm::vec4 col;

	float animationT;
	float animationPeriod;

	bool bStaged, bGone, bStored;

	Sphere(const int& _r, const glm::vec4& _col, const int& _gridUnit,const float& _displayTime,const float& _animationTime) {
		gridUnit = _gridUnit;
		r = _r;
		col = _col;
		initialPos = glm::vec3(-gridUnit, 0, 0);
		pos = initialPos;
		sphere = ofSpherePrimitive(r, 30);
		animationT = 0;
		displayTime = _displayTime;
		animationTime = _animationTime;
		animationPeriod = 120;
	}

	Sphere() {}
};

#endif
