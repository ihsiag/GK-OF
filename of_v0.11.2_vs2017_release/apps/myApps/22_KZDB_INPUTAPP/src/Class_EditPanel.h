#pragma once

#ifndef CLASS_EDIT_PANEL_H  
#define CLASS_EDIT_PANEL_H

#include "ofApp.h"
#include "ofxGKUtils.h"
#include "ofEasyCam.h"

class Class_EditPanel {
public:
	ofEasyCam* cam;
	ofxGKUtils gk;
	ofImage** selectedImg;
	glm::vec2 pos;
	glm::vec2 size;
	bool bSetImg;
	bool bMouseDisabled;
	
	Class_EditPanel() {}

	Class_EditPanel(ofImage** _selectedImg, ofEasyCam* _cam) {
		selectedImg = _selectedImg;
		cam = _cam;
		pos = glm::vec2(0);
		size = glm::vec2(ofGetWidth()/2,ofGetHeight()/2);
		bSetImg = false;
		bMouseDisabled = true;
	}
	~Class_EditPanel() {}
	
	void setup() {
	
	};

	void draw() {
		ofPushMatrix();
		ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
		ofFill();
		glColor4f(0, 0, 0, 0.7);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(ofGetWidth(), 0);
		glVertex2f(ofGetWidth(), ofGetHeight());
		glVertex2f(0, ofGetHeight());
		glEnd();
		ofTranslate(ofGetWidth() / 4, ofGetHeight() / 4);
		glColor4f(1, 1, 1, 1);
		ofNoFill();
		(* selectedImg)->draw(pos, size.x, size.y);
		ofPopMatrix();
		ofPushMatrix();
		ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
		drawCircle();
		ofPopMatrix();
		
	};

	void drawCircle() {
		ofFill();
		glColor4f(0.7, 0,0, 0.8);
		ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 20);
		glColor4f(1, 1, 1,1);
		ofNoFill();
		glColor3f(1, 0, 0);
		ofDrawCircle(ofGetMouseX(), ofGetMouseY(),20);
		glColor3f(1, 1, 1);
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
		bSetImg = true;
		cout << "editPanel : selectedImg - value : " << ( * selectedImg) << endl;
	}

	void onWindowResized(const glm::vec2& _pos, const glm::vec2& _size) {
		pos = _pos;
		size = _size;
	}
};

#endif


