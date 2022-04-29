#pragma once

#ifndef CLASS_ZONE_CONTENT_FOR_SCENE_THREE_H  
#define CLASS_ZONE_CONTENT_FOR_SCENE_THREE_H

#include "components/zones/Class_Zone.h"
#include "sceneThree/Class_Panel_Stamp_forSceneThree.h"

class Class_ContentZone_forSceneThree : public Class_Zone {

public:
	glm::vec2 zoneSize;
	glm::vec2 zonePos;
	SceneAdminInfo* adminInfo;

	Class_StampPanel_forSceneThree stampPanel;

	Class_ContentZone_forSceneThree() {};
	Class_ContentZone_forSceneThree(const glm::vec2& _zonePos, const glm::vec2& _zoneSize,SceneAdminInfo* _adminInfo,ofImage* _imgToStamp) {
		zonePos = _zonePos;
		zoneSize = _zoneSize;
		adminInfo = _adminInfo;
		
		stampPanel = Class_StampPanel_forSceneThree(zonePos, glm::vec2(0), zoneSize,adminInfo, _imgToStamp);
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
		stampPanel.draw();
	}

	bool IsMouseOn() { return false; };

	void mouseScrolled(const float& _scrollY) {
		stampPanel.mouseScrolled(_scrollY);
	};

	void onMouseClicked() {
		stampPanel.onMouseClicked();
	};

	void onWindowResized(const int& _w, const int& _h) {
		zoneSize.x = _w;
		stampPanel.onWindowResized(_w, _h);
	};

	bool goNext() { return false; };

	bool goBack() { return false; };

	void keyPressed(const int& _key) {};
};

#endif


