#pragma once

#ifndef CLASS_TXT_BUTTON_H  
#define CLASS_TXT_BUTTON_H

#include "ofApp.h"
#include "ofxGKUtils.h"
#include "ofEasyCam.h"

class Class_TxtButton {
public:

	string* id;
	ofTrueTypeFont** font;
	int** fontSize;
	int** fontHeight;
	glm::vec2 txtMargin;

	glm::vec2 parentPanelPos;

	glm::vec2 buttonPos;
	glm::vec2 buttonSize;
	bool bMouseClicked;
	bool bMouseDisabled;

	Class_TxtButton() {}

	Class_TxtButton(string* _id, ofTrueTypeFont** _font, int** _fontSize, int** _fontHeight, const glm::vec2& _parentPanelPos) {
		id = _id;
		font = _font;
		fontSize = _fontSize;
		fontHeight = _fontHeight;
		txtMargin = glm::vec2(*(*fontHeight)*0.1);
		parentPanelPos = _parentPanelPos;

	}

	~Class_TxtButton() {}
	
	void setup() {
	
	};

	void draw() {
		ofPushMatrix();
		ofTranslate(txtMargin.x,*( * fontHeight) + txtMargin.y);
		glColor3f(1, 1, 1);
		if (IsMouseOn()) {
			ofFill();
			drawRect(buttonPos,buttonSize);
			ofFill();
			glColor3f(0, 0, 0);
		}
		drawText(buttonPos);
		ofNoFill();
		ofPopMatrix();
	}

	void update(const glm::vec2& _pos, const glm::vec2& _size) {
		buttonPos = _pos;
		buttonSize = _size;
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
		(*font)->drawString("- " + * id, 0, **fontHeight);
		ofPopMatrix();
	}
	
	bool IsMouseOn() {
		bool _b = false;
		int _mx = ofGetMouseX();
		int _my = ofGetMouseY();
		if (parentPanelPos.x+buttonPos.x < _mx && _mx < parentPanelPos.x+buttonPos.x + buttonSize.x && parentPanelPos.y+buttonPos.y < _my && _my < parentPanelPos.y + buttonPos.y + buttonSize.y)_b = true;
		return _b;
	}

	void onMouseClicked() {
	}

	void onWindowResized(const glm::vec2& _pos, const glm::vec2& _size) {
		buttonPos = _pos;
		buttonSize = _size;
	}
};

#endif


