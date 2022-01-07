#pragma once
#include "GKScene.h"

class Scene_Sample1 : public GKScene{
public:
	int x;
	int currentFrame;

	void setup() {
		x = 0;
		currentFrame = 0;
	};

	void update() {
		currentFrame++;
		x = currentFrame % ofGetWidth();
	};

	void draw() {
		glClearColor(0, 0, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(2);
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(x, 0);
		glVertex2f(x, ofGetHeight());
		glEnd();
	};

	void keyPressed(int key) {
		x = key;
	};
};
