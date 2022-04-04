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

public:
	ofEasyCam* cam;
	int id;
	int gridUnit;
	ofSpherePrimitive sphere;
	glm::vec3 initialPos;
	glm::vec3 pos;
	glm::vec4 col;

	float animationT;
	float animationPeriod;
	float displayPeriod;

	bool bStaged, bGone, bStored;

	Sphere(ofEasyCam* _cam,const int& _id, const int& _r, const glm::vec4& _col, const int& _gridUnit,const float& _displayPeriod,const float& _animationPeriod) {
		cam = _cam;
		id = _id;
		gridUnit = _gridUnit;
		col = _col;
		sphere = ofSpherePrimitive(_r, 30);
		displayPeriod = _displayPeriod;
		animationPeriod = _animationPeriod;
	}

	Sphere() {}

	void drawSphere() {
		glColor4f(col.r, col.g, col.b, col.a);
		sphere.drawFaces();
		glColor4f(col.r * 0.75, col.g * 0.75, col.b * 0.75, col.a);
		sphere.drawWireframe();
		cam->end();
		glDisable(GL_DEPTH_TEST);
		ofDrawBitmapStringHighlight(ofToString(id), cam->worldToScreen(sphere.getPosition()));
		cam->begin();
		glEnable(GL_DEPTH_TEST);
	}
};

#endif
