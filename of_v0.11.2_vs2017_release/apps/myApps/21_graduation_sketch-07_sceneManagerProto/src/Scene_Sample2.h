#pragma once

#include "GKScene.h"

class Scene_Sample2 : public GKScene {
public:
	int x;
	int currentFrame;
	void setup() {
		x = 0;
	};
	void update() {
		currentFrame++;
		x = currentFrame*2 % ofGetWidth();
	};
	void draw() {
		glClearColor(0.5, 0.5, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(2);
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(x, 0);
		glVertex2f(x, ofGetHeight());
		glEnd();
	};
	void keyPressed(int key) {};
};
