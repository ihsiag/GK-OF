#pragma once

#ifndef CLASS_ZONE_HEAD_TITLE_FOR_SCENE_THREE_H  
#define CLASS_ZONE_HEAD_TITLE_FOR_SCENE_THREE_H

#include "components/zones/Class_Zone.h"

class Class_HeadTitleZone_forSceneThree :public Class_Zone{

public:
	int globalInnerMargin;
	glm::vec2 zoneSize;
	glm::vec2 zonePos;
	vector<ofImage>* uiElements;

	SceneAdminInfo* adminInfo;

	glm::vec2 eachIndexSize;

	Class_HeadTitleZone_forSceneThree() {}

	Class_HeadTitleZone_forSceneThree(const int& _globalInnerMargin,const glm::vec2& _zonePos,const glm::vec2& _zoneSize, vector<ofImage>* _uiElements, SceneAdminInfo* _adminInfo) {
		globalInnerMargin = _globalInnerMargin;
		zonePos = _zonePos;
		zoneSize = _zoneSize;
		uiElements = _uiElements;
		adminInfo = _adminInfo;
	}

	void setup() {
		eachIndexSize = glm::vec2(zoneSize.x / 3, zoneSize.y);
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
		glColor3f(0.95, 0.95, 0.95);
		ofPushMatrix();
		ofTranslate(zonePos);
		ofDrawRectangle(0, 0, zoneSize.x, zoneSize.y);
		glColor3f(1, 1, 1);
		drawHeadTitle();
		ofPopMatrix();
		ofNoFill();
	};

	void run() {
		update();
		draw();
	};

	//==============================================================//

	void drawHeadTitle() {
		glColor3f(0, 0, 0);
		uiElements->at(2).draw(0, 0, uiElements->at(2).getWidth() / 2, uiElements->at(2).getHeight() / 2);
	}


	//==============================================================//

	bool IsMouseOn() { return false; };

	void mouseScrolled(const float& _scrollY) {
		
	};

	void onMouseClicked() {};

	void onWindowResized(const int& _w, const int& _h) {
		zoneSize.x = _w;
	};

	bool goNext() { return false; };

	bool goBack() { return false; };

	void keyPressed(const int& _key) {};
};

#endif


