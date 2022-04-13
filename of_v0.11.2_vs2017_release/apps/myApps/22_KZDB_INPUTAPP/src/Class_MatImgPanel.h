#pragma once

#ifndef CLASS_MAT_IMG_PANEL_H  
#define CLASS_MAT_IMG_PANEL_H

#include "Class_Panel.h"

class Class_MatImgPanel : public Class_Panel {
public:
	ofImage* matImg;
	string* companyID;
	string* materialID;
	ofTrueTypeFont* font;
	int* fontSize;
	int* fontHeight;

	glm::vec2 panelPos;
	glm::vec2 panelSize;
	glm::vec2 imgPos;
	glm::vec2 imgSize;
	glm::vec2 txtPos;
	glm::vec2 txtSize;

	glm::vec4 imgMargin;
	glm::vec4 txtMargin;

	bool bGoBack;
	bool bGoNext;

	Class_MatImgPanel() {}

	Class_MatImgPanel(ofImage* _matImg, string* _companyID, string* _materialID, ofTrueTypeFont* _font, int* _fontSize,int* _fontHeight) {
		matImg = _matImg;
		companyID = _companyID;
		materialID = _materialID;
		font = _font;
		fontSize = _fontSize;
		fontHeight = _fontHeight;
	}
	~Class_MatImgPanel() {}

	void setup() {
		panelSize = glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.5);
		panelPos = glm::vec2(ofGetWidth() * 1 / 8, ofGetHeight() * 1 / 4);
		imgMargin = glm::vec4(10);
		txtMargin = glm::vec4(10);
		imgSize = glm::vec2(panelSize.x - imgMargin.x - imgMargin.z, panelSize.y*0.75 - imgMargin.y - imgMargin.w);
		imgPos = glm::vec2(imgMargin.x,imgMargin.z);
		txtPos = glm::vec2(txtMargin.x, imgPos.y + imgSize.y + imgMargin.w + txtMargin.y);
	};

	void reset() {
	};

	void update() {
	};

	void draw() {
		ofNoFill();
		glColor3f(0.3, 0.3, 0.3);
		glLineWidth(1);
		drawRect(panelPos, panelSize);
		ofPushMatrix();
		ofTranslate(panelPos);
		glColor3f(1,1,1);
		matImg->draw(imgPos,imgSize.x,imgSize.y);
		drawText(txtPos, txtSize);
		ofPopMatrix();
	};

	void drawText(const glm::vec2& _pos, const glm::vec2& _size) {
		font->drawString("COMPANY-ID : " + * companyID, _pos.x, _pos.y + *fontHeight);
		font->drawString("MATERIAL-ID : " + * materialID, _pos.x, _pos.y + *fontHeight * 2);
	}

	void createInfoPanel(stringstream* _info) {
	};

	void drawRect(const glm::vec2& _pos, const glm::vec2& _size) {
		glBegin(GL_QUADS);
		glVertex2f(_pos.x, _pos.y);
		glVertex2f(_pos.x + _size.x, _pos.y);
		glVertex2f(_pos.x + _size.x, _pos.y + _size.y);
		glVertex2f(_pos.x, _pos.y + _size.y);
		glEnd();
	}




	bool IsMouseOn() { return false; }

	void mouseScrolled(const float& _scrollY) {
		float _scrollScale = 30;
	}

	void onMouseClicked() {
	}

	void onWindowResized(const int& _w, const int& _h) {
		setup();
	}

	bool goNext() { return bGoNext; }

	bool goBack() { return bGoBack; }

	void keyPressed(const int& _key) {
		switch (_key) {
		case 'e':
			break;
		case 'b':
			break;
		}
	}
};

#endif


