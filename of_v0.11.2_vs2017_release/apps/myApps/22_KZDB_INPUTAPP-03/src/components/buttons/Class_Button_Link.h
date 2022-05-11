#pragma once

#ifndef CLASS_BUTTON_LINK_H  
#define CLASS_BUTTON_LINK_H

#include "components/buttons/Class_Button.h"

class Class_LinkButton : public Class_Button {

public:

	void setup() {};

	void reset() {};

	void update() {};

	void draw() {};

	bool IsMouseOn() { return false; };

	void mouseScrolled(const float& _scrollY) {};

	void onMouseClicked() {};

	void onWindowResized(const int& _w, const int& _h) {};

	void keyPressed(const int& _key) {};
};

#endif

