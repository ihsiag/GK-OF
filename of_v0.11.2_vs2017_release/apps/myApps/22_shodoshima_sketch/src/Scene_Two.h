#pragma once
#ifndef SCENE_TWO_H  
#define SCENE_TWO_H 

#include "ofMain.h"
#include "GKScene.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"


#include "Class_MySphere.h"
class Scene_Two : public GKScene{

	public:
		//-----------DEFAULT-----------//
		ofxGKUtils gk;		
		ofEasyCam cam;
		unsigned long int currentFrame;
		float time;
		stringstream ssGlobalLog;

		//-----------LIB-----------//

		//-----------GLOBAL-----------//
		bool bDebug;
		vector<MySphere> spheres;
		vector<MySphere*> spheresStored;
		vector<MySphere*> sphereStaged;
		vector<MySphere*> sphereGone;

		int gridUnit = 100;
		int counter = 0;

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

		void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);


		//-----------THIS-TIME-FUNCS-----------//
		void createSpheres();
		void initSpheresPos();
		void manageSpheres();
		void letSphereStaged();
		void letSphereGone();
		void letSphereStored();

		//-----------THISTIME-SCENE-BRIDGE-----------//
		
		//-----------EVENT-----------//
		void keyPressed(int key) {
			switch (key) {
			case 'f':
				ofToggleFullscreen();
				break;
			case 'h':
				bDebug = !bDebug;
				break;
			case 'r':
				resetCamera();
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