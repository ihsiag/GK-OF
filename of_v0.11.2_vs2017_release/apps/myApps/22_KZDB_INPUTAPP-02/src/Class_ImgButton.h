#pragma once

#ifndef CLASS_IMG_BUTTON_H  
#define CLASS_IMG_BUTTON_H

#include "ofApp.h"
#include "ofxGKUtils.h"

class Class_ImgButton {
public:	
	ofImage** selectedImg;
	string** selectedImgID;
	ofImage* originalImg;
	string* originalImgName;
	bool* bSelected;

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

	Class_ImgButton() {
	}

	Class_ImgButton(ofImage** _selectedImg, string** _selectedImgID, ofImage* _img, string* _imgName, bool* _bSelected, const glm::vec2& _buttonLocalPos, const glm::vec2& _buttonSize, const glm::vec2& _parentGlobalPos, const glm::vec2& _parentSize) {
		selectedImg = _selectedImg;
		selectedImgID = _selectedImgID;
		originalImg = _img;
		originalImgName = _imgName;
		bSelected = _bSelected;

		imgRatio = originalImg->getWidth() / originalImg->getHeight();
		
		buttonLocalPos = _buttonLocalPos;
		parentGlobalPos = _parentGlobalPos;
		parentSize = _parentSize;
		buttonSize = _buttonSize;
	}
	~Class_ImgButton() {}
	
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
		//imgSize = buttonSize;
		//imgPos = buttonLocalPos;
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
			*bSelected = true;
			(*selectedImg) = originalImg;
			(*selectedImgID) = originalImgName;
			cout << "imgButton Clicked : " << originalImg<< endl;
		}
	};

	void onWindowResized(const glm::vec2& _globalPos, const glm::vec2& _size) {
		parentGlobalPos = _globalPos;
		parentSize = _size;
		setup();
	};
};

#endif


