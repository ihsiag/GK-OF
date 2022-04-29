#pragma once

#ifndef CLASS_BUTTON_IMAGE_FOR_SCENE_TWO_H  
#define CLASS_BUTTON_IMAGE_FOR_SCENE_TWO_H

#include "components/buttons/Class_Button.h"

class Class_ImageButton_forSceneTwo:public Class_Button {
protected:

public:
	glm::vec2 parentGlobalPos;

	glm::vec2 buttonSize;
	glm::vec2 buttonPos;//relative to parentGlobalPos

	SceneAdminInfo* adminInfo;


	ofImage* imgInPrj;
	string* imgNameInPrj;

	Class_ImageButton_forSceneTwo(){}
	Class_ImageButton_forSceneTwo(const glm::vec2& _parentGlobalPos,const glm::vec2& _buttonPos,const glm::vec2 _buttonSize, SceneAdminInfo* _adminInfo,ofImage* _imgInPrj, string* _imgNameInPrj) {
		parentGlobalPos = _parentGlobalPos;
		buttonPos = _buttonPos;
		buttonSize = _buttonSize;
		adminInfo = _adminInfo;
		imgInPrj = _imgInPrj;
		imgNameInPrj = _imgNameInPrj;
	}

	void setup() {};

	void reset() {};

	void update() {};

	void draw() {
		ofPushMatrix();
		ofTranslate(buttonPos);
		glColor3f(1, 1, 1);
		imgInPrj->draw(0, 0, buttonSize.x, buttonSize.y);
		if (IsMouseOn()) {
			glColor3f(1, 0, 0);
			ofFill();
			ofDrawRectangle(0, 0, buttonSize.x, buttonSize.y);
			ofNoFill();
		}
		ofPopMatrix();
	};


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
			cout << "IMG - CLICKED :" << *imgNameInPrj << endl;
			adminInfo->dataSet.imgId = *imgNameInPrj;
			adminInfo->bGo = true;
		}
	};

	void onWindowResized(const int& _w, const int& _h) {};

	void keyPressed(const int& _key) {};
};

#endif


