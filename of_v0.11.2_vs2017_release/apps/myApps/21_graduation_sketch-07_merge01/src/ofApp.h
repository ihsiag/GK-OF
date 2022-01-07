#pragma once

#include "ofMain.h"
#include "GKScene.h"

class ofApp : public ofBaseApp{
	//*work as scene manager *//
private:
	ofApp() {}
	~ofApp() {
		for (GKScene* gs : gkScenes) {
			delete gs;
		}
	}
	static std::shared_ptr<ofApp> instance;
public:
	static std::shared_ptr<ofApp> getInstance() {
		if (instance.get() == 0) instance.reset(new ofApp(), [](ofApp* p) { delete p; });
		return instance;
	}
	vector<GKScene*> gkScenes;
	void addGKScene(GKScene* _gkScene);

	int currentSceneIndex;
	float currentSceneSec;
	float currentSceneFloatFrame;
	int currentSceneFrame;
	float sceneStartSec;
	float lastSec;
	

	void setup();
	void update();
	void draw();

	void keyPressed(int key) {
		gkScenes[currentSceneIndex]->keyPressed(key);
		switch (key) {
		case OF_KEY_RIGHT:
			//gkScenes[currentSceneIndex]->sceneEnded();
			currentSceneIndex++;
			currentSceneIndex %= gkScenes.size();
			//gkScenes[currentSceneIndex]->sceneStarted();
			sceneStartSec = ofGetElapsedTimef();
			break;

		case OF_KEY_LEFT:
			//gkScenes[currentSceneIndex]->sceneEnded();
			currentSceneIndex--;
			if (currentSceneIndex < 0) currentSceneIndex += gkScenes.size();
			//gkSscenes[currentSceneIndex]->sceneStarted();
			sceneStartSec = ofGetElapsedTimef();
			break;
		}
	};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void mouseEntered(int x, int y) {};
	void mouseExited(int x, int y) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};
};
