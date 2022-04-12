#pragma once

#ifndef CLASS_ESC_BUTTON_H  
#define CLASS_ESC_BUTTON_H

#include "ofApp.h"
#include "ofxGKUtils.h"
#include "ofEasyCam.h"

class Class_EscButton {
public:
	ofEasyCam* cam;
	ofxGKUtils gk;
	ofImage* originalImg;
	ofImage** selectedImg;
	glm::vec2 pos;
	glm::vec2 size;
	bool bMouseClicked;
	bool bMouseDisabled;

	Class_EscButton() {}

	Class_EscButton(ofImage* _img, ofImage** _selectedImg, ofEasyCam* _cam, const glm::vec2& _pos,const glm::vec2& _size) {
		originalImg = _img;
		selectedImg = _selectedImg;
		cam = _cam;
		pos = _pos;
		size = _size;
		bMouseClicked = false;
		bMouseDisabled = false;
	}
	~Class_EscButton() {}
	
	void setup() {
	
	};

	void draw() {
		glColor4f(1,1,1,1);
		ofPushMatrix();
		ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
		originalImg->draw(pos, size.x, size.y);
		glColor4f(1, 1, 1, 0.4);
		if(IsMouseOn())drawRect(pos,size);
		glColor4f(1, 1, 1, 1);
		ofPopMatrix();
	}

	void drawRect(const glm::vec2& _pos, const glm::vec2& _size) {
		ofFill();
		glBegin(GL_QUADS);
		glVertex2f(_pos.x,_pos.y);
		glVertex2f(_pos.x + _size.x,_pos.y);
		glVertex2f(_pos.x+_size.x,_pos.y+_size.y);
		glVertex2f(_pos.x, _pos.y+_size.y);
		glEnd();
		ofNoFill();
	}
	
	bool IsMouseOn() {
		bool _b = false;
		if (pos.x < ofGetMouseX() && ofGetMouseX()< pos.x + size.x) {
			if (pos.y < cam->getPosition().y + ofGetMouseY() && cam->getPosition().y + ofGetMouseY()< pos.y + size.y) {
				_b = true;
			}
		}
		return _b;
	}

	void onMouseClicked() {
		bMouseClicked = true;
		cout << "imgPanel Clicked" << endl;
		bMouseDisabled = true;
		if (IsMouseOn()) {
			cout << "ImgPanel : selectedImg - value : " << ( * selectedImg) << endl;
			(* selectedImg) = originalImg;
			cout << "ImgPanel : selectedImg - Changed" << endl;
		}
		//bMouseClicked = false;
	}

	void onWindowResized(const glm::vec2& _pos, const glm::vec2& _size) {
		pos = _pos;
		size = _size;
	}
};

#endif


