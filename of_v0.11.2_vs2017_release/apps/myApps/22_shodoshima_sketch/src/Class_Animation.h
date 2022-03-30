#pragma once

#ifndef CLASS_ANIMATION_H  
#define CLASS_ANIMATION_H 

#include "GKScene.h"
#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"
#include "Easing.h"


class AnimationClass {
public:
	virtual void setup() = 0;
	virtual void resetAnimation() = 0;
	virtual void initParam() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual bool getThisAnimationEndState() = 0;
	virtual bool getNextAnimationTriggerState() = 0;
};

class AnimationClassOverlay : public AnimationClass{
public:
	ofxGKUtils gk;
	// === DEFAULT == //
	int animationFrame;
	bool bDrawAll;
	bool bNextAnimationTrigger;

	void setup(){
		initParam();
	}

	void resetAnimation() {
		initParam();
	}

	void initParam() {
		animationFrame = 0;
		bDrawAll = false;
		bNextAnimationTrigger = false;

		alpha = 0.85;
		initCameraPos();
	}

	void update() {
		animationFrame++;
		//bDrawAll = true;
	}

	void draw() {
		cam->end();
		glDisable(GL_DEPTH_TEST);
		test();
		cam->begin();
		glEnable(GL_DEPTH_TEST);
		if (animationFrame < camPeriod)cameraWork();
		if (animationFrame > ofGetWidth() / 2)gk.draw3DPlaneGrid(2, 100, glm::vec3(0, 1, 0), 1, glm::vec4(0.7, 0.7, 0.7, 0.3));
	}

	bool getThisAnimationEndState() {
		return bDrawAll;
	}

	bool getNextAnimationTriggerState() {
		return bNextAnimationTrigger;
	}

	// === CUSTOM == //
	ofEasyCam* cam;
	glm::vec3 camInitialPos;
	glm::vec3 camTargetPos;
	int camPeriod;
	
	float alpha;

	void setCam(ofEasyCam* _cam) {
		cam = _cam;
	}

	void test() {
		glm::vec2 _cPosL;
		glm::vec2 _cPosR;
		float _cR;
		glm::vec4 _cCol;
		float _moveStep;
		_cR = ofGetHeight()/2 * 1.05;
		_cCol = glm::vec4(0.8, 0, 0, alpha);
		ofFill();
		if (alpha > 0.5)alpha -= 0.0005;
		if (animationFrame > ofGetWidth() / 2)alpha -= 0.01;

		glColor4f(_cCol.r, _cCol.g, _cCol.b, _cCol.a);
		_cPosL = glm::vec2(animationFrame, ofGetHeight() / 2);
		if (animationFrame > ofGetWidth() / 2)_cPosL.x = ofGetWidth() / 2;
		ofDrawCircle(_cPosL, _cR);
		
		glColor4f(_cCol.r, _cCol.g, _cCol.b, _cCol.a);
		_cPosR = glm::vec2(ofGetWidth() - animationFrame, ofGetHeight() / 2);
		if (animationFrame > ofGetWidth() / 2)_cPosR.x = ofGetWidth() / 2;
		ofDrawCircle(_cPosR, _cR);
		
		ofNoFill();
	}

	void initCameraPos() {
		camPeriod = ofGetWidth();
		camInitialPos = glm::vec3(100);
		camTargetPos = glm::vec3(78, 18, -70);
		cam->setPosition(camInitialPos);
	}

	void cameraWork() {
		glm::vec3 camDir = camTargetPos - camInitialPos;
		glm::vec3 currentPos = cam->getPosition();
		cam->setPosition(camInitialPos + camDir * Easing::easeOutCirc(float(animationFrame) / camPeriod));
		cam->lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
	}

};


#endif
