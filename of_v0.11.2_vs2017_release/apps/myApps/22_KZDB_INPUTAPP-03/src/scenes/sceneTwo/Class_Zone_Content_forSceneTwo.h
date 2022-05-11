#pragma once

#ifndef CLASS_ZONE_CONTENT_FOR_SCENE_TWO_H  
#define CLASS_ZONE_CONTENT_FOR_SCENE_TWO_H

#include "components/zones/Class_Zone.h"
#include "sceneTwo/Class_Button_Image_forSceneTwo.h"

class Class_ContentZone_forSceneTwo : public Class_Zone {

public:
	glm::vec2 zoneSize;
	glm::vec2 zonePos;
	SceneAdminInfo* adminInfo;

	vector<Class_ImageButton_forSceneTwo>buttons;

	Class_ContentZone_forSceneTwo() {};
	Class_ContentZone_forSceneTwo(const glm::vec2& _zonePos, const glm::vec2& _zoneSize,SceneAdminInfo* _adminInfo,vector<ofImage>* _prjImgs, vector<string>* _prjIds) {
		zonePos = _zonePos;
		zoneSize = _zoneSize;
		adminInfo = _adminInfo;
		int _columns = 4;
		glm::vec2 _buttonSize = glm::vec2(zoneSize.x / _columns, zoneSize.x / _columns * 2 / 3);
		for (int i = 0; i < _prjImgs->size(); i++) {
			glm::vec2 _buttonPos = glm::vec2(_buttonSize.x*(i%_columns),_buttonSize.y*(i/_columns));
			buttons.emplace_back(zonePos,_buttonPos,_buttonSize,adminInfo,&_prjImgs->at(i),&_prjIds->at(i));
		}
	};

	void setup() {
		reset();
	};

	void reset() {
	};

	void setZonePos(const glm::vec2& _zonePos) {
		zonePos = _zonePos;
	}

	void setZoneSize(const glm::vec2& _zoneSize) {
		zoneSize = _zoneSize;
	}

	void update() {};

	void draw() {
		ofFill();
		glColor3f(0, 0, 1);
		ofPushMatrix();
		ofTranslate(zonePos);
		ofDrawRectangle(0, 0, zoneSize.x, zoneSize.y);
		glColor3f(1, 1, 1);
		drawContent();
		ofPopMatrix();
		ofNoFill();
	};

	void run() {
		update();
		draw();
	};

	void drawContent() {
		for (auto& button : buttons) {
			if (button.buttonPos.y >-1 && button.buttonPos.y < zoneSize.y)button.draw();
		}
	}

	bool IsMouseOn() { return false; };

	void mouseScrolled(const float& _scrollY) {
		for (auto& button : buttons)button.mouseScrolled(_scrollY);
	};

	void onMouseClicked() {
		for (auto& button : buttons)button.onMouseClicked();
	};

	void onWindowResized(const int& _w, const int& _h) {
		zoneSize.x = _w;
	};

	bool goNext() { return false; };

	bool goBack() { return false; };

	void keyPressed(const int& _key) {};
};

#endif

