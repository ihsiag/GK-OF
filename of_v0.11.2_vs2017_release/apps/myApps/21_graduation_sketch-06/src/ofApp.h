#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

#include "Class_MyPlane.h"
#include "Class_MyNewFace.h"


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
		bool bHideAddedMesh;
		bool bHideMyPlane;


		ofMesh mainMesh;
		ofNode modifyInfo;
		glm::vec3 selectingVertexPos;

		//-----------SLIDER-----------//
		ofxGuiGroup gui;
		ofParameter<glm::vec3> rotationSlider;

		
		void setup();
		void update();
		void draw();

		//-----------FOR-LIB-----------//
		vector<Class_MyPlane> myPlanes;
		
		//-----------THIS-TIME-UTILS-----------//
		void resetCamera();
		void drawCamPosition();
		void createGUI();
		void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);
		void loadLatestMesh(const string& _dirName, ofMesh* _mesh);


		//-----------THIS-TIME-FUNCS-----------//
		void importMesh();	
		void modifyMesh();
		void updateMesh();
		glm::vec3 getCurrentVertex(const ofMesh& _mesh,stringstream& _ssDebug);
		vector < glm::vec3 > verticesPosHolder;
		void checkVerticesHolder();
		void addMyPlane();

		void draw3DBeforeModified();
		void draw3DAfterModified();
		void drawMainMesh();


		//loop-begin-任意の面が接している面すべて 
		void findPlaneIntersection(const Class_MyPlane& _myPlanePassive, const Class_MyPlane& _myPlaneActive); //return line
		void findLineIntersection(); //input intersection line & return point
		//loop-end
		void makeMyNewFace(const vector<glm::vec3>& _vertices);
		void addMyNewFace();

		//-----------DEBUG-FUNC-----------//
		void ofApp::debugDot();


		//-----------EVENT-----------//
		void keyPressed(int key) {
			//for (auto& myPlane : myPlanes) {
			//	myPlane.keyPressed(key);// used:key -> none
			//}
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
				//gk.saveMesh(generatedMesh, 1);
				break;
			case '1':
				bHideMainMesh = !bHideMainMesh;				
				break;
			case '2':
				bHideAddedMesh = !bHideAddedMesh;
				break;
			case '3':
				bHideMyPlane = !bHideMyPlane;
				break;
			case 's' :
				gk.saveImage();
				break;
			case 'z':
				if (myPlanes.size())myPlanes.pop_back();
				break;
			case 'h':
				bDebug = !bDebug;
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
		void mousePressed(ofMouseEventArgs& args) {
			if (args.button == OF_MOUSE_BUTTON_LEFT) {
				if (bModified) {
					verticesPosHolder.push_back(selectingVertexPos);
				}
			}
		}
		void windowResized(int w, int h) {
			gk.resizeGUI(gui);
		}
		
		//-----------NO-InUSE-----------//
		void keyReleased(int key) {}
		void mouseMoved(int x, int y) {}
		void mouseDragged(int x, int y, int button) {}
		void mouseReleased(int x, int y, int button) {}
		void mouseEntered(int x, int y) {}
		void mouseExited(int x, int y) {}		
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}	
};
