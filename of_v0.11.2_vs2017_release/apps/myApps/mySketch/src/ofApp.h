#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

#include "GKPlane.h"
#include "GKPoint.h"
#include "GKLineSimple.h"

class ofApp : public ofBaseApp{

	public:
		//-----------DEFAULT-----------//
		ofxGKUtils gk;
		ofEasyCam cam;
		unsigned long int currentFrame;
		float time;
		stringstream ssGlobalLog;
		glm::vec2 mouseOnWorldPlane;
		
		//-----------GLOBAL-----------//
		GKPlane gkPlaneForNormal;
		GKPlane gkPlaneTestOriginal;
		GKPlane gkPlaneTestModified;

		//-----------SLIDER-----------//
		ofxGuiGroup gui;

		
		void setup();
		void update();
		void draw();

		//-----------FOR-LIB-----------//


		//-----------THIS-TIME-UTILS-----------//
		void resetCamera();
		void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);
		
		//-----------THIS-TIME-FUNCS-----------//
		void run();
		void makeRandomMesh();
		void test();

		//-----------DEBUG-FUNC-----------//

		//-----------EVENT-----------//
		void keyPressed(int key) {
			//for (auto& gkPlane : gkPlanes) {
			//	gkPlane.keyPressed(key);// used:key -> none
			//}
			switch (key) {
				cout << key << endl;
			case 'f':
				ofToggleFullscreen();
				break;
			case 'r':
				resetCamera();
				break;
			case 'l':
				ssGlobalLog.str("");
				ssGlobalLog.clear(std::stringstream::goodbit);
				ssGlobalLog << "CLEARED LOG" << endl;
				break;
			case ' ':
				makeRandomMesh();
				break;
			case 't':
				test();
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
		}
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}

		//-----------NO-InUSE-----------//
		
};
