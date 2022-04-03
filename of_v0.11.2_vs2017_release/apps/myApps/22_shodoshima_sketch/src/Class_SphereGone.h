#pragma once

#ifndef CLASS_SPHEREGONE_H  
#define CLASS_SPHEREGONE_H 

#include "GKScene.h"
#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"
#include "Easing.h"


class MySphere {
public:
	int gridUnit;
	ofSpherePrimitive sphere;
	int r;
	glm::vec3 pos;
	glm::vec4 col;

	float animationT;
	float animationPeriod;

	MySphere(const int& _r, const glm::vec4& _col, const int& _gridUnit) {
		gridUnit = _gridUnit;
		r = _r;
		col = _col;
		pos = glm::vec3(-gridUnit, 0, 0);
		sphere = ofSpherePrimitive(r, 30);
		animationT = 0;
		animationPeriod = 120;
	}

	void update() {
		animationT++;	
		sphere.setGlobalPosition(pos);
	}

	void draw() {
		glColor4f(col.r, col.g, col.b, col.a);
		sphere.drawFaces();
		glColor4f(col.r*0.75, col.g*0.75, col.b*0.75, col.a);
		sphere.drawWireframe();
	}	


	void slide() {
		glm::vec3 animationDir = glm::vec3(1, 0, 0);
		float animationDist = gridUnit;
		pos = pos + animationDir * animationDist * Easing::easeInOutQuart(animationT/ animationPeriod);
	}

	void readyToSlide() {
		if (animationT > animationPeriod)animationT = 0;
	}
};

#endif
