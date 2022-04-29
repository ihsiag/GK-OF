#pragma once

#ifndef CLASS_ZONE_H  
#define CLASS_ZONE_H

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "GKScene.h"

class Class_Zone {

private:
	glm::vec2 zoneSize;
	glm::vec2 zonePos;


public:
	ofxGKUtils gk;

	virtual void setup()=0;

	virtual void reset()=0;

	virtual void update()=0;

	virtual void draw()=0;

	virtual void run() = 0;

	void drawMyText(const string& _txt, const ofTrueTypeFont& _font) {
		glColor3f(1, 1, 1);
		_font.drawString(_txt, 0, _font.getSize());
	}

	virtual bool IsMouseOn()=0;

	virtual void mouseScrolled(const float& _scrollY) =0;

	virtual void onMouseClicked()=0;

	virtual void onWindowResized(const int& _w, const int& _h)=0;

	virtual bool goNext()=0;

	virtual bool goBack()=0;

	virtual void keyPressed(const int& _key)=0;
};

#endif


