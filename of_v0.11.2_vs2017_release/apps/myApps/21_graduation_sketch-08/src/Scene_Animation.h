#pragma once
#ifndef SCENE_ANIMATION_H  
#define SCENE_ANIMATION_H 

#include "GKScene.h"
#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

class Scene_Animation : public GKScene {
public:
	Scene_Animation() {}

	ofxGKUtils gk;
	stringstream ssGlobalLog;
	ofEasyCam cam;
	unsigned long int currentFrame;
	float time;


	ofMesh meshToAnimate;
	vector<GKPlane> gkPlanesCreatedFromMeshToAnimate;
	vector<GKPlane> gkPlanesCreatedManuallyToAnimate;

	bool bPlayAnimation;
	unsigned long int animationFrame;

	void setup();
	void resetScene();
	void update();
	void draw();


	void initParam();
	void initSet();
	void initSliders();
	void resetCamera();

	void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);

	void drawMainMesh();

	void toggleAnimation();
	void animate();



	//-----------NO-InUSE-----------//


	void keyPressed(int key) {
		switch (key) {
		case 's':
			toggleAnimation();
			ssGlobalLog << "PLAY" << endl;
			break;
		}
	}
	void mousePressed(ofMouseEventArgs& args) {
	}
	void mousePressed(int x, int y, int button) {};
	void windowResized(int w, int h) {
		//gk.resizeGUI(guiOne, 13);
		//gk.resizeGUI(guiTwo, 13);
	}

	//-----------NO-InUSE-----------//
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void mouseEntered(int x, int y) {};
	void mouseExited(int x, int y) {};
	void mouseScrolled(int x, int y, float scrollX, float scrollY) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

private:

};

#endif
