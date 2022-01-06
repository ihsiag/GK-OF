#pragma once

#include "ofMain.h"
#include "GKScene.h"

class ofApp : public ofBaseApp{
	ofApp() {}
	~ofApp() {
		for (GKScene* gs : gkScenes) {
			delete gs;
		}
	}
	static std::shared_ptr<ofApp> instance;
public:
	int currentSceneIndex;
	static std::shared_ptr<ofApp> getInstance() {
		if (instance.get() == 0) instance.reset(new ofApp(), [](ofApp* p) { delete p; });
		return instance;
	}

	vector<GKScene*> gkScenes;
	void addGKScene(GKScene* _gkScene) {
		gkScenes.push_back(_gkScene);
	}


	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);	
};
