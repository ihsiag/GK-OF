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

	glm::vec2 panelPos;
	glm::vec2 panelSize;

	int margin;

	glm::vec2 imgAreaPos;
	glm::vec2 imgAreaSize;

	glm::vec2 imgPos;
	glm::vec2 imgSize;
	float imgRatio;

	glm::vec2 txtPos;
	glm::vec2 txtSize;

	bool bGoBack;
	bool bGoNext;

	Class_MatImgPanel() {}

	Class_MatImgPanel(ofImage* _matImg, string* _companyID, string* _materialID, ofTrueTypeFont* _font) {
		matImg = _matImg;
		companyID = _companyID;
		materialID = _materialID;
		font = _font;
	}
	~Class_MatImgPanel() {}

	void setup() {
		margin = 10;

		panelSize = glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.5);
		panelPos = glm::vec2(ofGetWidth() * 1 / 8, ofGetHeight() * 1 / 4);

		imgAreaPos = glm::vec2(margin);
		float _x = panelSize.x - margin * 2;
		imgAreaSize = glm::vec2(_x, _x * 2 / 3);
		imgRatio = matImg->getWidth() / matImg->getHeight();
		float _h = imgAreaSize.y;
		float _w = _h * imgRatio;
		imgSize = glm::vec2(_w,_h);
		imgPos = imgAreaPos + (imgSize/2 -imgAreaSize/2);
		txtPos = glm::vec2(margin) + glm::vec2(0,imgAreaPos.y+imgAreaSize.y + margin);
	};

	void reset() {
	};

	void update() {
	};

	void draw() {
		ofNoFill();
		glColor3f(0.3, 0.3, 0.3);
		glLineWidth(1);
		drawOutline(panelPos, panelSize);
		ofPushMatrix();
		ofTranslate(panelPos);
		glColor3f(1,1,1);
		matImg->draw(imgPos,imgSize.x,imgSize.y);
		glColor3f(1, 1, 1);
		glLineWidth(1);
		drawPartingLine(glm::vec2(margin, margin + imgSize.y + margin), imgSize.x);
		drawText(txtPos, txtSize);
		drawTitle(glm::vec2(0,-margin- font->getSize()));
		ofPopMatrix();
	};

	void drawText(const glm::vec2& _pos, const glm::vec2& _size) {
		font->drawString("COMPANY-ID : " + * companyID, _pos.x, _pos.y + font->getSize());
		font->drawString("MATERIAL-ID : " + * materialID, _pos.x, _pos.y + font->getSize() * 2);
	}

	void drawPartingLine(const glm::vec2& _pos, const float& _length) {
		glBegin(GL_LINES);
		glVertex2f(_pos.x, _pos.y);
		glVertex2f(_pos.x + _length, _pos.y);
		glEnd();
	}

	void drawTitle(const glm::vec2& _pos) {
		font->drawString("SELECTED-MATERIAL", _pos.x, _pos.y + font->getSize());
	}

	void drawOutline(const glm::vec2& _pos, const glm::vec2& _size) {
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


