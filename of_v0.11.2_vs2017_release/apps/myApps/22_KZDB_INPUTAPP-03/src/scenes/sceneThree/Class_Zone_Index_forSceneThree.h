#pragma once

#ifndef CLASS_ZONE_INDEX_FOR_SCENE_THREE_H  
#define CLASS_ZONE_INDEX_FOR_SCENE_THREE_H

#include "components/zones/Class_Zone.h"

class Class_IndexZone_forSceneThree:public Class_Zone {

public:
	glm::vec2 zoneSize;
	glm::vec2 zonePos;

	SceneAdminInfo* adminInfo;

	glm::vec2 eachIndexSize;


	Class_IndexZone_forSceneThree() {}
	Class_IndexZone_forSceneThree(const glm::vec2& _zonePos, const glm::vec2& _zoneSize, SceneAdminInfo* _adminInfo) {
		zonePos = _zonePos;
		zoneSize = _zoneSize;
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
		glColor3f(0.90, 0.90, 0.90);
		ofPushMatrix();
		ofTranslate(zonePos);
		ofDrawRectangle(0, 0, zoneSize.x, zoneSize.y);
		glColor3f(0, 0, 0);
		drawIndexes();
		ofPopMatrix();
		ofNoFill();
	};

	void run() {
		update();
		draw();
	};

	//==============================================================//
	void drawIndexes() {
		ofPushMatrix();
		drawIndexOfSceneOne();
		ofTranslate(eachIndexSize.x, 0);
		drawIndexOfSceneTwo();
		ofTranslate(eachIndexSize.x, 0);
		drawIndexOfSceneThree();
		ofPopMatrix();
	}

	void drawIndexOfSceneOne() {
		glColor3f(0.7, 0.7, 0.7);
		gk.drawInfo("1 - SELECT PROJECT", glm::vec2(0, 0));
	}

	void drawIndexOfSceneTwo() {
		glColor3f(0.7, 0.7, 0.7);
		gk.drawInfo("2 - SELECT IMAGE", glm::vec2(0, 0));
	}

	void drawIndexOfSceneThree() {
		glColor3f(0, 0, 0);
		gk.drawInfo("3 - SELECT POSITION", glm::vec2(0, 0));
	}

	//==============================================================//

	bool IsMouseOn() { return false; };

	void mouseScrolled(const float& _scrollY) {};

	void onMouseClicked() {};

	void onWindowResized(const int& _w, const int& _h) {
		zoneSize.x = _w;
		eachIndexSize.x = zoneSize.x / 3;
	};

	bool goNext() { return false; };

	bool goBack() { return false; };

	void keyPressed(const int& _key) {};
};

#endif


