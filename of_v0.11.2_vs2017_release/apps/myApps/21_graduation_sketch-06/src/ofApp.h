#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

#include "Class_MyFace.h"


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
		bool bModified;
		bool bDebug;
		bool bHideMainMesh;


		ofMesh mainMesh;
		ofNode modifyInfo;
		glm::vec3 selectingVertex;

		//-----------SLIDER-----------//
		ofxGuiGroup gui;
		ofParameter<glm::vec3> rotationSlider;

		
		void setup();
		void update();
		void draw();

		//-----------FOR-LIB-----------//
		vector<Class_MyFace> myFaces;
		vector < glm::vec3 > verticesHolder;

		void checkVerticesHolder();

		//-----------THIS-TIME-UTILS-----------//
		void resetCamera();
		void drawCamPosition();
		void createGUI();
		void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);
		void loadLatestMesh(const string& _dirName, ofMesh* _mesh);
		void drawMainMesh();

		//-----------THIS-TIME-FUNCS-----------//
		void importMesh();
		void modifyMesh();
		ofMesh getModifiedMesh(ofMesh* _mesh);
		void updateMesh();

		glm::vec3 vertexPicker(const ofMesh& _mesh,stringstream& _ssDebug);
			//-----------DEBUG-FUNC-----------//
		void ofApp::debugDot();


		//-----------EVENT-----------//
		void keyPressed(int key) {
			switch (key) {
			case 'f':
				ofToggleFullscreen();
				break;
			case 'r':
				resetCamera();
				break;
			case 'u':
				updateMesh();
				break;
			case 'm' :
				gk.saveMesh(mainMesh, 1);
				break;
			case 'h':
				bHideMainMesh = !bHideMainMesh;
				//bDebug = !bDebug;
				break;
			case 's' :
				gk.saveImage();
				break;
			case 'l':
				// バッファをクリアします。
				ssGlobalLog.str("");
				// 状態をクリアします。
				ssGlobalLog.clear(std::stringstream::goodbit);
				ssGlobalLog << "CLEARED LOG" << endl;
				break;
			}
		}
		void keyReleased(int key) {}
		void mouseMoved(int x, int y) {}
		void mouseDragged(int x, int y, int button) {}
		void mousePressed(ofMouseEventArgs& args) {
			if (args.button == OF_MOUSE_BUTTON_LEFT) {
				verticesHolder.push_back(selectingVertex);
			}
		}
		void mouseReleased(int x, int y, int button) {
		}
		void mouseEntered(int x, int y) {}
		void mouseExited(int x, int y) {}
		void windowResized(int w, int h) {
			gk.resizeGUI(gui);
		}
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}
		
};
