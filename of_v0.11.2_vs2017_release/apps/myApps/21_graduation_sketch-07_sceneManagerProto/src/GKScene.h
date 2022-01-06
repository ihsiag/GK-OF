#pragma once

class GKScene {
public:
	virtual ~GKScene() {}

	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() const = 0;
	virtual void keyPressed(int key) {};
private:
};
