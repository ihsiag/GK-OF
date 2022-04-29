#pragma once

#ifndef CLASS_ZONE_HEAD_TITLE_FOR_SCENE_TWO_H  
#define CLASS_ZONE_HEAD_TITLE_FOR_SCENE_TWO_H

#include "components/zones/Class_Zone.h"

class Class_HeadTitleZone_forSceneTwo :public Class_Zone{

public:
	glm::vec2 zoneSize;
	glm::vec2 zonePos;

	SceneAdminInfo* adminInfo;

	glm::vec2 eachIndexSize;

	Class_HeadTitleZone_forSceneTwo() {}

	Class_HeadTitleZone_forSceneTwo(const glm::vec2& _zonePos,const glm::vec2& _zoneSize, SceneAdminInfo* _adminInfo) {
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
		glColor3f(0, 1, 0);
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
		gk.drawInfo("FOUND IMAGES IN THE PROJECT - SELECT IMAGE TO YOU REGISTER", glm::vec2(0, 0));
	}

	void drawIndexOfSceneThree() {
		glColor3f(0.7, 0.7, 0.7);
		gk.drawInfo("SELECT POSITION THAT THE MATERIAL USED AT", glm::vec2(0, 0));
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


