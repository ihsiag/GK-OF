#pragma once

#include "ofMain.h"
#include "Class_MyFunctions.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

class ofApp : public ofBaseApp{

	public:
		//-----------DEFAULT-----------//
		Class_MyFunctions mf;		
		ofEasyCam cam;
		unsigned long int currentFrame;
		float time;
		stringstream ssGlobalLog;

		//-----------GLOBAL-----------//
		vector<ofMesh> meshes;

		//-----------SLIDER-----------//
		ofxGuiGroup gui;

		
		void setup();
		void update();
		void draw();

		//-----------FOR-LIB-----------//


		//-----------THIS-TIME-FUNCS-----------//
		void resetCamera();

		//-----------EVENT-----------//
		void keyPressed(int key) {
			switch (key) {
			case ' ':
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
		void windowResized(int w, int h) {}
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}
		
};
