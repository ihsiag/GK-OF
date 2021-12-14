#pragma once

#include "ofMain.h"

class myRenderer {
public:
	virtual ~myRenderer() {}
	virtual void setup() = 0;
	virtual void render() = 0;
	virtual void sceneStarted() = 0;
	virtual void sceneEnded() = 0;
	virtual void keyPressed(int key) {};
	virtual void mousePressed(int x, int y) {};
	virtual void mouseReleased(int x, int y) {};
	virtual void mouseDragged(int x, int y) {};

	virtual std::string getName() {
		std::string res;
		res = typeid(*this).name();
		return res;
	}
};


class myManager : public ofBaseApp{

	myManager() {}
	~myManager() {
		for (myRenderer* r : scenes) {
			delete r;
		}
	}

	static std::shared_ptr<myManager> instance;

public:

	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	void addRenderer(myRenderer* r);

	ofFbo fbo;
	std::vector<myRenderer*> scenes;
	int currentSceneIndex = 0;

	float viewScale = 1.f;
	glm::vec2 viewOffset{ 0, 0 };
	glm::vec2 dragPos{ 0, 0 };

	bool bShowFramerate = false;
	bool bPaused = false;

	float currentSceneSec;
	float currentSceneFloatFrame;
	int currentSceneFrame;
	float sceneStartSec;
	float lastSec;


	static std::shared_ptr<myManager> getInstance() {
		if (instance.get() == 0) instance.reset(new myManager(), [](myManager* p) { delete p; });
		return instance;
	}
};
