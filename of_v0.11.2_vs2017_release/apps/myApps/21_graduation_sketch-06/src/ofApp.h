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
		ofMesh importedMesh;
		ofMesh checkedMesh;
		ofNode transformInfo;

		//-----------SLIDER-----------//
		ofxGuiGroup gui;
		ofParameter<glm::vec3> rotationSlider;

		
		void setup();
		void update();
		void draw();

		//-----------FOR-LIB-----------//


		//-----------THIS-TIME-FUNCS-----------//
		void resetCamera();
		void loadMesh(const string& _dirName,ofMesh* _mesh);
		void createGUI();
		void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);
		void resetMeshMatrix(ofMesh* _mesh);

		//-----------EVENT-----------//
		void keyPressed(int key) {
			switch (key) {
			case 'f':
				ofToggleFullscreen();
				break;
			case 'r':
				resetCamera();
				break;
			case 'm':
				resetMeshMatrix(&importedMesh);
				gk.saveMesh(importedMesh, 1);
				break;
			case 't':
				loadMesh("./meshExport/", &checkedMesh);
				importedMesh.clear();
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
