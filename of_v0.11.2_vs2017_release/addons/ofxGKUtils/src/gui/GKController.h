#pragma once

#ifndef GK_ANGLECONTROLLER_H
#define GK_ANGLECONTROLLER_H

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "GKGui.h"



class GKController: public GKGui {
public:
	glm::vec3 pos;
	float radius;

	GKController() {}
	~GKController() {}

	void set(const glm::vec3& _pos, const float& _r) {
		pos = _pos;
		radius = _r;
	}
	void i() {
		ofPushMatrix();
		ofTranslate(pos.x, pos.y,pos.z);
		ofDrawCircle(glm::vec3(0), radius);
		t(360, 10, glm::vec4(0, 0.3, 0.1, 1), 2);
		ofPopMatrix();
	}
	void t(const int& _divideN, const int& _size, const glm::vec4& _col,const float& _lineWidth) {
		glLineWidth(_lineWidth);
		glColor4f(_col.r, _col.g, _col.b, _col.a);
		ofPushMatrix();
		for (int i = 0; i < _divideN; i++) {
			ofRotateZ(360 / _divideN * i);
			glBegin(GL_LINES);
			glVertex3f(0, radius - _size / 2, 0);
			glVertex3f(0, radius + _size / 2, 0);
			glEnd();
		}
		ofPopMatrix();
		
	}
private:
		
};
#endif