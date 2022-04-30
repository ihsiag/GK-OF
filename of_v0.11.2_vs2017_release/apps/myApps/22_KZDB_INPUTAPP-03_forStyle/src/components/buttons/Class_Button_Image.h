#pragma once

#ifndef CLASS_BUTTON_IMAGE_H  
#define CLASS_BUTTON_IMAGE_H

#include "components/buttons/Class_Button.h"

class Class_ImageButton:public Class_Button {
protected:

public:
	glm::vec2 parentGlobalPos;

	glm::vec2 buttonSize;
	glm::vec2 buttonPos;//relative to parentGlobalPos


	ofImage* img;
	string* id;

	Class_ImageButton(){}
	Class_ImageButton(const glm::vec2& _parentGlobalPos, const glm::vec2& _buttonPos, const glm::vec2 _buttonSize, ofImage* _img, string* _id) {
		parentGlobalPos = _parentGlobalPos;
		buttonPos = _buttonPos;
		buttonSize = _buttonSize;
		img = _img;
		id = _id;
	}

	void setup() {};

	void reset() {};

	void update() {};

	void draw() {
		ofPushMatrix();
		ofTranslate(buttonPos);
		img->draw(0, 0, buttonSize.x, buttonSize.y);
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
	};

	void onMouseClicked() {};

	void onWindowResized(const glm::vec2& _pos, const glm::vec2& _size) {};

	void keyPressed(const int& _key) {};
};

#endif


