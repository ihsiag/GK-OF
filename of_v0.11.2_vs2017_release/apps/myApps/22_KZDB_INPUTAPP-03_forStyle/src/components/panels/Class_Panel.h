#pragma once

#ifndef CLASS_PANEL_H  
#define CLASS_PANEL_H

#include "ofMain.h"
#include "ofxGKUtils.h"

class Class_Panel {

public:

	virtual void setup() =0;

	virtual void reset() =0;

	virtual void update() =0;

	virtual void draw() =0;

	virtual bool IsMouseOn() =0;

	virtual void mouseScrolled(const float& _scrollY) =0;

	virtual void onMouseClicked() =0;

	virtual void onWindowResized(const int& _w, const int& _h) =0;

	virtual void keyPressed(const int& _key) =0;
};

#endif


