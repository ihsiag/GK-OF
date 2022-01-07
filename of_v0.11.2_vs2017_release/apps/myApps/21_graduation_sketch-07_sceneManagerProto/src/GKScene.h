#pragma once
#include "ofMain.h"

class GKScene {
public:
	virtual ~GKScene() {}

	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void keyPressed(int key) = 0;

private:
};
