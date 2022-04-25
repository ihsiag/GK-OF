#pragma once

#ifndef CLASS_PROJECT_BUTTON_H  
#define CLASS_PROJECT_BUTTON_H

#include "ofApp.h"
#include "ofxGKUtils.h"
#include "ofEasyCam.h"

class Class_ProjectButton {
public:
	DataSet** dataSet;
	string* id;
	
	ofTrueTypeFont** font;

	glm::vec2 buttonLocalPos;
	glm::vec2 buttonSize;

	glm::vec2 parentGlobalPos;
	glm::vec2 parentSize;

	int margin = 10;

	bool bMouseClicked;
	bool bMouseDisabled;

	Class_ProjectButton() {}

	Class_ProjectButton(DataSet** _dataSet,string* _id, ofTrueTypeFont** _font, const glm::vec2& _buttonLocalPos, const glm::vec2& _parentGlobalPos, const glm::vec2& _parentSize) {
		dataSet = _dataSet;
		id = _id;
		font = _font;
		buttonLocalPos = _buttonLocalPos;
		parentGlobalPos = _parentGlobalPos;
		parentSize = _parentSize;	
		buttonSize = glm::vec2(parentSize.x, (*font)->getSize());
	}

	~Class_ProjectButton() {}
	
	void setup() {
		
	};

	void update() {
	}

	void draw() {
		glColor3f(1, 1, 1);
		if (IsMouseOn()) {
			ofFill();
			drawRect(buttonLocalPos,buttonSize);
			glColor3f(0, 0, 0);
		}
		drawText(buttonLocalPos);
		glColor3f(1, 1, 1);
		ofNoFill();
	}

	void drawRect(const glm::vec2& _pos, const glm::vec2& _size) {
		glBegin(GL_QUADS);
		glVertex2f(_pos.x,_pos.y);
		glVertex2f(_pos.x + _size.x,_pos.y);
		glVertex2f(_pos.x+_size.x,_pos.y+_size.y);
		glVertex2f(_pos.x, _pos.y+_size.y);
		glEnd();
	}

	void drawText(const glm::vec2& _pos) {
		ofPushMatrix();
		ofTranslate(_pos);
		(*font)->drawString("- " + * id, 0, (*font)->getSize());
		ofPopMatrix();
	}

	void mouseScrolled(const float& _scrollY) {
		float _scrollScale = (*font)->getSize();
		buttonLocalPos.y += _scrollScale * _scrollY;
	}
	
	bool IsMouseOn() {
		bool _b = false;
		int _mx = ofGetMouseX();
		int _my = ofGetMouseY();
		if (parentGlobalPos.x+buttonLocalPos.x < _mx && _mx < parentGlobalPos.x + buttonLocalPos.x+buttonSize.x && parentGlobalPos.y + buttonLocalPos.y < _my && _my < parentGlobalPos.y+buttonLocalPos.y+ buttonSize.y)_b = true;
		return _b;
	}

	void onMouseClicked() {
		if (IsMouseOn()) {
			cout << "PROJECT-BUTTON-CLICKED : " <<*id<< endl;
			(*dataSet)->projectID = *id;
		}
	}

	void onWindowResized(const glm::vec2& _globalPos, const glm::vec2& _size) {
		parentGlobalPos = _globalPos;
		parentSize = _size;
	}
};

#endif


