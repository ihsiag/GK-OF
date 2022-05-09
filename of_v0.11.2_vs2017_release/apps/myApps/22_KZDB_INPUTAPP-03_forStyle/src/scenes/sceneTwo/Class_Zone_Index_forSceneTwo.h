#pragma once

#ifndef CLASS_ZONE_INDEX_FOR_SCENE_TWO_H  
#define CLASS_ZONE_INDEX_FOR_SCENE_TWO_H

#include "components/zones/Class_Zone.h"

class Class_IndexZone_forSceneTwo:public Class_Zone {

public:
	int globalInnerMargin;
	glm::vec2 zoneSize;
	glm::vec2 zonePos;
	vector<ofImage>* uiElements;

	SceneAdminInfo* adminInfo;

	glm::vec2 eachIndexSize;


	Class_IndexZone_forSceneTwo() {}
	Class_IndexZone_forSceneTwo(const int& _globalInnerMargin,const glm::vec2& _zonePos, const glm::vec2& _zoneSize, vector<ofImage>* _uiElements, SceneAdminInfo* _adminInfo) {
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
		glColor4f(1, 1, 1, 1);
	}

	void drawIndexOfSceneOne() {
		glColor4f(0,0,0,0.2);
		//gk.drawInfo("1 - SELECT PROJECT", glm::vec2(0, 0));
		uiElements->at(0).draw(0, 0,uiElements->at(0).getWidth()/2, uiElements->at(0).getHeight()/2);
	}

	void drawIndexOfSceneTwo() {
		glColor4f(0, 0, 0,1);
		//gk.drawInfo("2 - SELECT IMAGE", glm::vec2(0, 0));
		uiElements->at(1).draw(0, 0, uiElements->at(1).getWidth() / 2, uiElements->at(1).getHeight() / 2);
	}

	void drawIndexOfSceneThree() {
		glColor4f(0,0,0, 0.2);
		//gk.drawInfo("3 - SELECT POSITION", glm::vec2(0, 0));
		uiElements->at(2).draw(0, 0, uiElements->at(2).getWidth() / 2, uiElements->at(2).getHeight() / 2);
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


