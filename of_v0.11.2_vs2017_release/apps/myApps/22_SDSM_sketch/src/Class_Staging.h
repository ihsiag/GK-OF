#pragma once

#ifndef CLASS_STAGING_H  
#define CLASS_STAGING_H 

#include "GKScene.h"
#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"
#include "Easing.h"

#include "Class_Sphere.h"

class Staging {
public:
	Sphere* sphere;
	glm::vec3 initialPos;
	glm::vec3 pos;
	glm::vec4 col;

	int gridUnit;

	float displayT;
	float animationT;
	float componentT;	
	float displayPeriod;
	float animationPeriod;
	float componentPeriod;

	bool bDisplayEnd;
	bool bAnimationEnd;
	bool bComponentEnd;

	Staging(Sphere* _sphere){
		sphere = _sphere;
		initialPos = glm::vec3(-gridUnit, 0, 0);
		pos = initialPos;
		
		gridUnit = sphere->gridUnit;
		
		displayT = 0;
		animationT = 0;	
		componentT = 0;
		animationPeriod = sphere->animationPeriod;
		displayPeriod = sphere->displayPeriod;
		componentPeriod = displayPeriod + animationPeriod;
		bDisplayEnd = false;
		bAnimationEnd = false;
		bComponentEnd = false;
	}

	void run() {
		update();
		draw();
	}

	void update() {
		manageComponentTimeLine();
		sphere->sphere.setGlobalPosition(pos);
	}

	void draw() {
		sphere->drawSphere();
	}


	void slide() {
		glm::vec3 animationDir = glm::vec3(1, 0, 0);
		float animationDist = gridUnit;
		pos = initialPos + animationDir * animationDist * Easing::easeInOutQuart(animationT / animationPeriod);
	}

	void manageComponentTimeLine() {
		componentT++;
		if (componentT < displayPeriod) {
			displayT++;
		}
		else if(componentT < displayPeriod + animationPeriod){
			animationT++;
			bDisplayEnd = true;
		}
		else {
			bComponentEnd = true;
		}
		if (bDisplayEnd)slide();
	}
};

#endif
