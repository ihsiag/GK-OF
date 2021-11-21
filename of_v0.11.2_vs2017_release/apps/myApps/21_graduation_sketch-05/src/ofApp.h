#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"
#include "Class_SmallScreen.h"

class ofApp : public ofBaseApp{

	public:
		//-----------DEFAULT-----------//
		ofxGKUtils gk;		
		ofEasyCam cam;
		unsigned long int currentFrame;
		float time;
		stringstream ssGlobalLog;

		//-----------LIB-----------//
		vector<Class_SmallScreen> smallScreens;

		//-----------GLOBAL-----------//
		vector<ofMesh> meshes;
		int numSmallScreens;

		//-----------SLIDER-----------//
		ofxGuiGroup gui;

		
		void setup();
		void update();
		void draw();

		//-----------FOR-LIB-----------//
		void setupSmallScreen(const int& _index);
		void resizeSmallScreen(const int& _index);


		//-----------THIS-TIME-FUNCS-----------//
		void resetCamera();
		void loadMeshes();
		void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);

		//-----------EVENT-----------//
		void keyPressed(int key) {
			switch (key) {
			case 'f':
				ofToggleFullscreen();
				break;
			case 'r':
				resetCamera();
				break;
			}
		}
		void keyReleased(int key) {}
		void mouseMoved(int x, int y) {}
		void mouseDragged(int x, int y, int button) {}
		void mousePressed(int x, int y, int button) {}
		void mouseReleased(int x, int y, int button) {}
		void mouseEntered(int x, int y) {}
		void mouseExited(int x, int y) {}
		void windowResized(int w, int h) {
			gk.resizeGUI(gui);
			for (int i = 0; i < smallScreens.size(); i++) {
				resizeSmallScreen(i);
			}
		}
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}
		
};
