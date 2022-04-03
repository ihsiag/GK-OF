#pragma once

#ifndef CLASS_STORED_H  
#define CLASS_STORED_H 

#include "GKScene.h"
#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"
#include "Easing.h"

#include "Class_Sphere.h"

class Stored :public Sphere {
public:
	int gridUnit;
	Sphere* sphere;
	int r;
	glm::vec3 initialPos;
	glm::vec3 pos;
	glm::vec4 col;

	float animationT;
	float animationPeriod;

	bool bStaged, bGone, bStored;

	bool bAnimationEnd;

	Stored(Sphere* _sphere) {
		sphere = _sphere;
		gridUnit = sphere->gridUnit;
		initialPos = glm::vec3(-gridUnit, 0, 0);
		pos = initialPos;
		animationT = 0;
		animationPeriod = 120;
		bAnimationEnd = false;
	}

	void run() {
		update();
		draw();
	}

	void update() {
		manageAnimationTime();
		sphere->sphere.setGlobalPosition(pos);
	}

	void draw() {
		glColor4f(col.r, col.g, col.b, col.a);
		sphere->sphere.drawFaces();
		glColor4f(col.r * 0.75, col.g * 0.75, col.b * 0.75, col.a);
		sphere->sphere.drawWireframe();
	}


	void slide() {
		glm::vec3 animationDir = glm::vec3(1, 0, 0);
		float animationDist = gridUnit;
		pos = initialPos + animationDir * animationDist * Easing::easeInOutQuart(animationT / animationPeriod);
	}

	void manageAnimationTime() {
		animationT++;
		if (animationT > animationPeriod) {
			animationT = 0;
			bAnimationEnd = true;
		}
	}
};

#endif
