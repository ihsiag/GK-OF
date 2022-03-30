#pragma once
#ifndef SCENE_ONE_H  
#define SCENE_ONE_H 

#include "ofMain.h"
#include "GKScene.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

#include "Class_Animation.h"

class Scene_One : public GKScene{

	public:
		//-----------DEFAULT-----------//
		ofxGKUtils gk;		
		ofEasyCam cam;
		unsigned long int currentFrame;
		float time;
		stringstream ssGlobalLog;

		//-----------LIB-----------//
		vector<AnimationClass*> animationClasses;
		unsigned int animationFrame;
		int animationIndex;
		bool bPlayAnimation;

		AnimationClassOverlay ao;

		//-----------GLOBAL-----------//
		
		bool bDebug;
		ofImage img;
		vector<ofMesh> meshes;

		//-----------SLIDER-----------//
		ofxGuiGroup gui;

		
		void setup();
		void resetScene();
		void update();
		void draw();

		//-----------FOR-LIB-----------//
		void initParam();
		void initGKSet();
		void resetCamera();
		void initAnimationClasses();
		void resetAnimationClasses();
		void manageAnimationClasses();
		void toggleAnimate();

		
		void loadMeshes();
		void rescaleMesh(ofMesh* _mesh,const glm::vec3& _sclC, const float& _sclF);
		void loadImage();
		void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);


		//-----------THIS-TIME-FUNCS-----------//
		void drawGridOnPlane();
		void runScan();
		void drawOverlay();

		//-----------THISTIME-SCENE-BRIDGE-----------//
		
		//-----------EVENT-----------//
		void keyPressed(int key) {
			switch (key) {
			case ' ':
				toggleAnimate();
				break;
			case 'f':
				ofToggleFullscreen();
				break;
			case 'h':
				bDebug = !bDebug;
				break;
			case 'r':
				resetAnimationClasses();
				break;
			case 's':
				gk.saveImage();
				break;
			}
		}
		void keyReleased(int key) {}
		void mouseMoved(int x, int y) {}
		void mouseDragged(int x, int y, int button) {}
		void mousePressed(ofMouseEventArgs& args) {
			if (args.button == OF_MOUSE_BUTTON_LEFT) {
				//do something
			}
		}

		void mousePressed(int x, int y, int button) {}
		void mouseReleased(int x, int y, int button) {}
		void mouseEntered(int x, int y) {}
		void mouseExited(int x, int y) {}
		void mouseScrolled(int x, int y, float scrollX, float scrollY) {}
		void windowResized(int w, int h) {
			gk.resizeGUI(gui,13);
		}
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}
		
};

#endif
