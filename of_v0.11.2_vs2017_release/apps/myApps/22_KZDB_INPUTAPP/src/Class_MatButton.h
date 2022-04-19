#pragma once

#ifndef CLASS_MAT_BUTTON_H  
#define CLASS_MAT_BUTTON_H

#include "ofApp.h"
#include "ofxGKUtils.h"

class Class_MatButton {
public:	
	DataSet** dataSet;
	ofImage* originalImg;
	string* imgName;

	glm::vec2 parentGlobalPos;
	glm::vec2 parentSize;
	
	glm::vec2 buttonLocalPos;
	glm::vec2 buttonSize;

	int margin;

	glm::vec2 imgAreaPos;
	glm::vec2 imgAreaSize;
	glm::vec2 imgPos;
	glm::vec2 imgSize;
	float imgRatio;

	glm::vec2 textAreaPos;
	glm::vec2 textAreaSize;
	glm::vec2 textPos;

	bool* bGoNext;

	Class_MatButton(ofImage* _img, string* _imgName, bool* _bGoNext, const glm::vec2& _buttonPos, const glm::vec2& _buttonSize, const glm::vec2& _panelPos, const glm::vec2& _panelSize, DataSet** _dataSet) {
		dataSet = _dataSet;
		originalImg = _img;
		imgName = _imgName;
		bGoNext = _bGoNext;
		buttonLocalPos = _buttonPos;
		buttonSize = _buttonSize;
		parentGlobalPos = _panelPos;
		parentSize = _panelSize;
		imgRatio = originalImg->getWidth() / originalImg->getHeight();
	}

	Class_MatButton() {
	}
	~Class_MatButton() {}
	
	void setup() {
		margin = 10;
		imgAreaPos = buttonLocalPos + glm::vec2(margin);
		imgAreaSize = buttonSize - glm::vec2(margin * 2);
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

	void update() {}

	void draw() {
		ofPushMatrix();
		ofTranslate(buttonLocalPos);
		drawImgInImgArea();
		glColor4f(1, 1, 1, 0.4);
		if(IsMouseOn())drawHoverRect(imgPos,imgSize);
		glColor4f(1, 1, 1, 1);
		ofPopMatrix();
	}

	void drawImgInImgArea() {
		ofPushMatrix();
		ofTranslate(imgPos);
		originalImg->draw(glm::vec2(0), imgSize.x, imgSize.y);
		ofPopMatrix();
	}

	void drawHoverRect(const glm::vec2& _pos, const glm::vec2& _size) {
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
		int _mx = ofGetMouseX();
		int _my = ofGetMouseY();
		if (parentGlobalPos.x + buttonLocalPos.x < _mx && _mx < parentGlobalPos.x + buttonLocalPos.x + buttonSize.x && parentGlobalPos.y + buttonLocalPos.y < _my && _my < parentGlobalPos.y + buttonLocalPos.y + buttonSize.y)_b = true;
		return _b;
	}

	void mouseScrolled(const float& _scrollY) {
		float _scrollScale = 30;
		buttonLocalPos.y += _scrollScale * _scrollY;
		setup();
	};

	void onMouseClicked() {			
		if (IsMouseOn()) {
			*bGoNext = true;
			cout << "matButton Clicked : " << originalImg<< endl;
			(*dataSet)->materialID = *imgName;
		}
	};

	void onWindowResized(const glm::vec2& _globalPos, const glm::vec2& _size) {
		parentGlobalPos = _globalPos;
		parentSize = _size;
		setup();
	};
};

#endif


