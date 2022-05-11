#pragma once

#ifndef CLASS_ZONE_INDEX_H  
#define CLASS_ZONE_INDEX_H

#include "components/zones/Class_Zone.h"

class Class_IndexZone:public Class_Zone {

public:
	glm::vec2 zoneSize;
	glm::vec2 zonePos;

	string title;

	Class_IndexZone() {}
	Class_IndexZone(const glm::vec2& _zonePos, const glm::vec2& _zoneSize, const string& _title) {
		zonePos = _zonePos;
		zoneSize = _zoneSize;
		title = _title;
	}

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
		glColor3f(1, 0, 0);
		ofPushMatrix();
		ofTranslate(zonePos);
		ofDrawRectangle(0, 0, zoneSize.x, zoneSize.y);
		glColor3f(0, 0, 0);
		gk.drawInfo(title, glm::vec2(0));
		ofPopMatrix();
		ofNoFill();
	};

	void run() {
		update();
		draw();
	};

	bool IsMouseOn() { return false; };

	void mouseScrolled(const float& _scrollY) {};

	void onMouseClicked() {};

	void onWindowResized(const int& _w, const int& _h) {};

	bool goNext() { return false; };

	bool goBack() { return false; };

	void keyPressed(const int& _key) {};
};

#endif

