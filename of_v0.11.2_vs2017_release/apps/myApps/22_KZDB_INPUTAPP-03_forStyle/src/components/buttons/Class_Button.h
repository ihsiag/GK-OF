#pragma once

#ifndef CLASS_BUTTON_H  
#define CLASS_BUTTON_H

#include "ofMain.h"
#include "ofxGKUtils.h"

class Class_Button {

public:

	virtual void setup() =0;

	virtual void reset() =0;

	virtual void update() =0;

	virtual void draw() =0;

	virtual bool IsMouseOn() =0;

	virtual void mouseScrolled(const float& _scrollY) =0;

	virtual void onMouseClicked() =0;

	virtual void onWindowResized(const glm::vec2& _pos, const glm::vec2& _size) =0;

	virtual void keyPressed(const int& _key) =0;
};

#endif


