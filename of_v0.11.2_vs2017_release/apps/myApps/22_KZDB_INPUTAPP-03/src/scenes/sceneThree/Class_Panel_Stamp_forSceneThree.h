#pragma once

#ifndef CLASS_PANEl_STAMP_H  
#define CLASS_PANEL_STAMP_H

#include "components/panels/Class_Panel.h"

class Class_StampPanel_forSceneThree:public Class_Panel {
protected:

public:
	glm::vec2 parentGlobalPos;

	glm::vec2 panelSize;
	glm::vec2 panelPos;//relative to parentGlobalPos

	SceneAdminInfo* adminInfo;

	ofImage* img;

	float imgRatio;

	glm::vec2 imgAreaPos;
	glm::vec2 imgAreaSize;
	glm::vec2 imgPos;
	glm::vec2 imgSize;

	glm::vec2 mousePosOnPanel;
	vector<glm::vec2> selectedAreaPos;
	glm::vec2 customFormatAreaPos;

	Class_StampPanel_forSceneThree(){}
	Class_StampPanel_forSceneThree(const glm::vec2& _parentGlobalPos, const glm::vec2& _panelPos, const glm::vec2 _panelSize,SceneAdminInfo* _adminInfo, ofImage* _img) {
		parentGlobalPos = _parentGlobalPos;
		panelPos = _panelPos;
		panelSize = _panelSize;

		adminInfo = _adminInfo;
		
		imgAreaSize = panelSize/2;
		imgAreaPos = panelSize / 2 - imgAreaSize / 2;
		
		img = _img;

		imgRatio = img->getWidth() / img->getHeight();

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
	
		customFormatAreaPos = glm::vec2(0);
	}

	void setup() {};

	void reset() {};

	void update() {
		customFormatAreaPos = getcustomFormatAreaPos(ofGetMouseX()-parentGlobalPos.x-panelPos.x, ofGetMouseY()-parentGlobalPos.y-panelPos.y);
	};

	void draw() {
		update();
		ofPushMatrix();
		//ofTranslate(panelPos);
		glColor3f(1, 1, 1);
		ofDrawCircle(20, 20, 20, 20);
		drawImg();
		drawCurrentCircle();
		drawStampedCircle();
		ofPopMatrix();
	};

	void drawImg() {
		ofPushMatrix();
		ofTranslate(imgAreaPos + imgPos);
		img->draw(glm::vec2(0), imgSize.x, imgSize.y);
		ofPopMatrix();
	}

	void drawCurrentCircle() {
		ofFill();
		glColor4f(0.7, 0, 0, 0.8);
		ofDrawCircle(getDefaultFormatPos(customFormatAreaPos), 20);
		glColor4f(1, 1, 1, 1);
		ofNoFill();
		glColor3f(1, 0, 0);
		ofDrawCircle(getDefaultFormatPos(customFormatAreaPos), 20);
		glColor3f(1, 1, 1);
	}

	void drawStampedCircle() {
		for (auto& sap : selectedAreaPos) {
			ofFill();
			glColor4f(0.7, 0, 0.7, 0.8);
			ofDrawCircle(getDefaultFormatPos(sap), 20);
			glColor4f(1, 1, 1, 1);
			ofNoFill();
			glColor3f(1, 0, 1);
			ofDrawCircle(getDefaultFormatPos(sap), 20);
			glColor3f(1, 1, 1);
		}
	}

	glm::vec2 getcustomFormatAreaPos(const float& _mousePosX, const float& _mousePosY) {
		glm::vec2 _range = glm::vec2(panelSize / imgSize);
		return glm::vec2(ofMap(_mousePosX, 0, panelSize.x, -_range.x, _range.x), ofMap(_mousePosY, 0, panelSize.y, _range.y, -_range.y));
	}

	glm::vec2 getDefaultFormatPos(const glm::vec2& _customFormatPos) {
		glm::vec2 _range = glm::vec2(panelSize / imgSize);
		return glm::vec2(ofMap(_customFormatPos.x, -_range.x, _range.x, 0, panelSize.x), ofMap(_customFormatPos.y, _range.y, -_range.y, 0, panelSize.y));
	}

	bool IsMouseOn() {
		bool _b = false;
		int _mx = ofGetMouseX();
		int _my = ofGetMouseY();
		if (parentGlobalPos.x + panelPos.x < _mx && _mx < parentGlobalPos.x + panelPos.x + panelSize.x && parentGlobalPos.y + panelPos.y < _my && _my < parentGlobalPos.y + panelPos.y + panelSize.y)_b = true;
		return _b;
	};

	void mouseScrolled(const float& _scrollY) {
		float _scrollScale = 30;
		imgSize.y += _scrollScale * _scrollY;
		imgSize.x = imgSize.y * imgRatio;
		imgPos = imgAreaSize / 2 - imgSize / 2;
	};

	void onMouseClicked() {
		if (glm::compMin(customFormatAreaPos) >= -1 && glm::compMax(customFormatAreaPos) <= 1) {
			selectedAreaPos.erase(selectedAreaPos.begin(), selectedAreaPos.end());
			selectedAreaPos.push_back(customFormatAreaPos);
			adminInfo->dataSet.posX = ofToString(selectedAreaPos[0].x);
			adminInfo->dataSet.posY = ofToString(selectedAreaPos[0].y);
		}
	};

	void onWindowResized(const int& _w, const int& _h) {
		panelPos = glm::vec2(0);
		panelSize = glm::vec2(_w, _h);
		imgSize = panelSize / 2;
		imgPos = panelPos / 2 - imgSize / 2;
	};

	void keyPressed(const int& _key) {};
};

#endif


