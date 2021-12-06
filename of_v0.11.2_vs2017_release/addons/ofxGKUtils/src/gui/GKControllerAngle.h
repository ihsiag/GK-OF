#pragma once

#ifndef GK_CONTROLLER_ANGLE_H
#define GK_CONTROLLER_ANGLE_H

#include "ofMain.h"
#include "ofxGKUtils.h"



class GKControllerAngle{
public:
	glm::vec3 pos;
	float radius;
	glm::vec3 normal;
	float measureSize;
	ofNode modifyInfo;
	ofTrueTypeFont* font;

	GKControllerAngle() {}
	~GKControllerAngle() {}

	void set(const glm::vec3& _pos, const float& _r, const float& _measureSize,const glm::vec3& _normalToDraw, ofTrueTypeFont* _font) {
		pos = _pos;
		radius = _r;
		normal = _normalToDraw;
		measureSize = _measureSize;
		modifyInfo.setGlobalPosition(glm::vec3(0));
		modifyInfo.lookAt(normal);
		modifyInfo.move(_pos.x, _pos.y, _pos.z);
		ofSetCircleResolution(180);
		font = _font;
	}

	void update(const float& _sliderDeg) {
		modifyInfo.setGlobalPosition(glm::vec3(0));
		modifyInfo.lookAt(normal);
		modifyInfo.move(pos.x, pos.y, pos.z);
		modifyInfo.rotateDeg(_sliderDeg, normal);
	}

	void drawController() {
		ofPushMatrix();
		ofMultMatrix(modifyInfo.getGlobalTransformMatrix());
		ofNoFill();
		glColor4f(0.05, 0.2, 0.1, 1);
		glLineWidth(1);
		ofDrawCircle(glm::vec3(0), radius);
		drawMeasure(1,10,measureSize/1.5, measureSize, glm::vec4(0, 0.3, 0.1, 1), 2);
		ofPopMatrix();
	}
	void drawMeasure(const int& _divideS, const int& _divideL,const float& _sizeS, const float& _sizeL, const glm::vec4& _col,const float& _lineWidth) {
		glLineWidth(_lineWidth/2);
		glColor4f(_col.r, _col.g, _col.b, _col.a);
		ofPushMatrix();
		for (int i = 0; i < 360/ _divideS; i++) {
			ofRotateZDeg(_divideS);
			if (i % _divideL == 0) {
				glLineWidth(_lineWidth);
				glBegin(GL_LINES);
				glVertex3f(0, radius - _sizeL / 2, 0);
				glVertex3f(0, radius + _sizeL / 2, 0);
				glEnd();
			}
			else {
				glBegin(GL_LINES);
				glVertex3f(0, radius - _sizeS / 2, 0);
				glVertex3f(0, radius + _sizeS / 2, 0);
				glEnd();
			}
		}
		gk.drawCross(0,0,radius*2);
		ofPopMatrix();		
	}

	void drawVerticalLine() {

	}
private:
	ofxGKUtils gk;
		
};
#endif