#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

class ofApp : public ofBaseApp{

	public:
		//-----------DEFAULT-----------//
		ofxGKUtils gk;		
		ofEasyCam cam;
		unsigned long int currentFrame;
		float time;
		stringstream ssGlobalLog;

		//-----------GLOBAL-----------//
		vector<ofMesh> meshes;
		vector<ofFbo> fbos;

		int numFbos;
		glm::vec2 sizeFbo;

		//-----------SLIDER-----------//
		ofxGuiGroup gui;

		
		void setup();
		void update();
		void draw();

		//-----------FOR-LIB-----------//
		void setupFbos();
		void runFbos();
		void drawFbos();
		void setupFbo(const int& _index);
		void runFbo(const int& _index);
		void drawFbo(const int& _index);

		void resizeFbos();
		void resizeFbo(const int& _index);

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
		void windowResized(int w, int h) {
			gk.resizeGUI(gui);
		}
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}
		
};
