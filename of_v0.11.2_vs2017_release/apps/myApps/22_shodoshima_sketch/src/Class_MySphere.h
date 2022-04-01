#pragma once

#ifndef CLASS_MYSPHERE_H  
#define CLASS_MYSPHERE_H 

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

	bool bStored, bStaged, bGone;

	MySphere(const int& _r, const glm::vec4& _col, const int& _gridUnit) {
		gridUnit = _gridUnit;
		r = _r;
		col = _col;
		pos = glm::vec3(-gridUnit, 0, 0);
		sphere = ofSpherePrimitive(r, 30);
		bStored, bStaged, bGone = false;
	}

	void init();
	void stage() {
		if (bStaged) {
			pos = glm::vec3(0);
		}
		bStaged = false;
	};
	void gone() {
		if (bGone) { 
			pos = glm::vec3(gridUnit, 0, 0); 
		}
		bGone = false;
	};
	void store() {
		if (bStored) { 
			pos = glm::vec3(-gridUnit, 0, 0);
		}
		bStored = false;
	};

	void update() {
		if (bStaged)stage();
		if (bGone)gone();
		if (bStored)store();
		sphere.setGlobalPosition(pos);
	}

	void draw() {
		glColor4f(col.r, col.g, col.b, col.a);
		sphere.drawFaces();
		glColor4f(col.r*0.75, col.g*0.75, col.b*0.75, col.a);
		sphere.drawWireframe();
	}	
};

#endif
