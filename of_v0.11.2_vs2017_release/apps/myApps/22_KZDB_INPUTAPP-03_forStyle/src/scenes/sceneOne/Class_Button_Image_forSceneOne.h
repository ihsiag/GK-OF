#pragma once

#ifndef CLASS_BUTTON_IMAGE_FOR_SCENE_ONE_H  
#define CLASS_BUTTON_IMAGE_FOR_SCENE_ONE_H

#include "components/buttons/Class_Button.h"

class Class_ImageButton_forSceneOne:public Class_Button {
protected:

public:
	glm::vec2 parentGlobalPos;

	glm::vec2 buttonSize;
	glm::vec2 buttonPos;//relative to parentGlobalPos

	SceneAdminInfo* adminInfo;


	ofImage* prjImg;
	string* prjId;

	float imgRatio;

	glm::vec2 imgAreaPos;
	glm::vec2 imgAreaSize;
	glm::vec2 imgPos;
	glm::vec2 imgSize;

	Class_ImageButton_forSceneOne(){}
	Class_ImageButton_forSceneOne(const glm::vec2& _parentGlobalPos,const glm::vec2& _buttonPos,const glm::vec2 _buttonSize, SceneAdminInfo* _adminInfo,ofImage* _prjImg, string* _prjId) {
		parentGlobalPos = _parentGlobalPos;
		buttonPos = _buttonPos;
		buttonSize = _buttonSize;
		adminInfo = _adminInfo;
		prjImg = _prjImg;
		prjId = _prjId;

		imgAreaSize = buttonSize -glm::vec2(5);
		imgAreaPos = buttonSize / 2 - imgAreaSize / 2;

		imgRatio = prjImg->getWidth() / prjImg->getHeight();

		float _w, _h;
		if (imgAreaSize.x > imgAreaSize.y) {
			_h = imgAreaSize.y;
			_w = _h * imgRatio;
		}
		else {
			_w = imgAreaSize.x;
			_h = _w / imgRatio;
		}
		imgSize = glm::vec2(_w, _h);
		imgPos = imgAreaSize / 2 - imgSize / 2;
	}

	void setup() {};

	void reset() {};

	void update() {};

	void draw() {
		ofPushMatrix();
		ofTranslate(buttonPos);
		glColor3f(1, 1, 1);
		drawButtonArea();
		drawImg();
		drawHoverRect();
		ofPopMatrix();
	};

	void drawButtonArea() {
		float _r, _g, _b;
		_r = 245.0 / 255.0;
		_g = 245.0 / 255.0;
		_b = 250.0 / 255.0;
		ofFill();
		glColor3f(_r,_g,_b);
		ofDrawRectangle(0, 0, buttonSize.x, buttonSize.y);
		ofNoFill();
		glColor4f(0.90, 0.90, 0.90,0.8);
		ofDrawRectangle(0, 0, buttonSize.x, buttonSize.y);
		glColor4f(1, 1, 1,1);
	}

	void drawImg() {
		ofPushMatrix();
		ofTranslate(imgAreaPos + imgPos);
		prjImg->draw(glm::vec2(0), imgSize.x, imgSize.y);
		ofPopMatrix();
	}

	void drawHoverRect() {
		if (IsMouseOn()) {
			ofPushMatrix();
			ofTranslate(imgAreaPos + imgPos);
			glColor3f(1, 0, 0);
			ofFill();
			ofDrawRectangle(0, 0, imgSize.x, imgSize.y);
			ofNoFill();
			ofPopMatrix();
		}
	}


	bool IsMouseOn() {
		bool _b = false;
		int _mx = ofGetMouseX();
		int _my = ofGetMouseY();
		if (parentGlobalPos.x + buttonPos.x < _mx && _mx < parentGlobalPos.x + buttonPos.x + buttonSize.x && parentGlobalPos.y + buttonPos.y < _my && _my < parentGlobalPos.y + buttonPos.y + buttonSize.y)_b = true;
		return _b;
	};

	void mouseScrolled(const float& _scrollY) {
		float _scrollScale = buttonSize.y;
		buttonPos.y += _scrollScale * _scrollY;
		//setup();
	};

	void onMouseClicked() {
		if (IsMouseOn()) {
			cout << "IMG - CLICKED :" << *prjId << endl;
			adminInfo->dataSet.prjId = *prjId;
			adminInfo->bGo = true;
		}
	};

	void onWindowResized(const glm::vec2& _buttonPos,const glm::vec2& _buttonSize) {
		buttonPos = _buttonPos;
		buttonSize = _buttonSize;
		
		imgAreaSize = buttonSize - glm::vec2(5);
		imgAreaPos = buttonSize / 2 - imgAreaSize / 2;

		float _w, _h;
		if (imgAreaSize.x > imgAreaSize.y) {
			_h = imgAreaSize.y;
			_w = _h * imgRatio;
		}
		else {
			_w = imgAreaSize.x;
			_h = _w / imgRatio;
		}
		imgSize = glm::vec2(_w, _h);
		imgPos = imgAreaSize / 2 - imgSize / 2;
	};

	void keyPressed(const int& _key) {};
};

#endif


