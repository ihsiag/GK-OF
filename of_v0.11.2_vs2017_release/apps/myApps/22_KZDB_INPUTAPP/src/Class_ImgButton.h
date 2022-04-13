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
	glm::vec2 pos;
	glm::vec2 size;

	glm::vec2* mousePosOnPanel;
	bool* bSelected;

	Class_ImgButton() {
	}

	Class_ImgButton(ofImage** _selectedImg,string** _selectedImgID, ofImage* _img,string* _imgName,glm::vec2* _mousePosOnPanel, bool* _bSelected) {
		selectedImg = _selectedImg;
		selectedImgID = _selectedImgID;
		originalImg = _img;
		originalImgName = _imgName;
		pos = glm::vec2(0);
		size = glm::vec2(0);
		mousePosOnPanel = _mousePosOnPanel;
		bSelected = _bSelected;
	}
	~Class_ImgButton() {}
	
	void setup() {
	
	};

	void update() {}

	void draw() {
		originalImg->draw(pos, size.x, size.y);
		glColor4f(1, 1, 1, 0.4);
		if(IsMouseOn())drawHoverRect(pos,size);
		glColor4f(1, 1, 1, 1);
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
		if (pos.x < mousePosOnPanel->x && mousePosOnPanel->x< pos.x + size.x) {
			if (pos.y < mousePosOnPanel->y && mousePosOnPanel->y < pos.y + size.y) {
				_b = true;
			}
		}
		return _b;
	}

	void mouseScrolled(const float& _scrollY) {
	};

	void onMouseClicked() {			
		if (IsMouseOn()) {
			*bSelected = true;
			(*selectedImg) = originalImg;
			(*selectedImgID) = originalImgName;
			cout << "imgButton Clicked : " << originalImg<< endl;
		}
	};

	void onWindowResized(const glm::vec2& _pos, const glm::vec2& _size) {
		pos = _pos;
		size = _size;
	};
};

#endif


