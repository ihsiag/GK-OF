#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

#include "Class_Delaunay.h"
#include "Class_GKDelaunay.h"
#include "Class_GKSplit.h"
#include "Class_GKNetwork.h"



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
		bool bHideSelectedPoint;
		bool bHideMainMesh;
		bool bHideAddedMesh;
		bool bHideGKPlane;
		bool bHideNetwork;
		bool bHideGKPlaneNew;
		bool bHideLight;
		

		ofLight light;
		ofMesh mainMesh;
		ofNode modifyInfo;
		glm::vec3 selectingVertexPos;

		ofMesh meshToSave;

		//-----------SLIDER-----------//
		ofxGuiGroup gui;
		ofParameter<glm::vec3> rotationSlider;
		
		void setup();
		void update();
		void draw();

		//-----------FOR-LIB-----------//		
		GKDelaunay3d gkDela;
		vector<DelaTriangle> gkDelaTriangles;

		GKSplit gkSplitUtil;
		
		vector<GKLineSimple> gkIntersectLines;
		vector<GKPlane> gkPlanes;
		vector<GKPlane> gkPlanesNew;
		vector<GKSplit> gkSplits;
		vector<GKNetwork> gkNets;

		//-----------THIS-TIME-INITS-----------//
		void initParam();
		void initSet();
		void initSliders();
		void resetCamera();


		//-----------THIS-TIME-UTILS-----------//
		void drawCamPosition();		
		void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);
		void loadLatestMesh(const string& _dirName, ofMesh* _mesh);
		ofMesh getMeshFromGKPlanes(vector<GKPlane>* _gkPlanes);


		//-----------THIS-TIME-FUNCS-----------//
		void importMesh();	
		void modifyMesh();
		void updateMesh();
		glm::vec3 getCurrentVertex(const ofMesh& _mesh,stringstream& _ssDebug);
		vector < glm::vec3 > verticesPosHolder;
		void checkVerticesHolder();
		void addGKPlane();

		void draw3DBeforeModified();
		void draw3DAfterModified();
		void drawMainMesh();
		void drawGKPlanes();
	
		void setGKSplits();
		void runGKSplits();
		
		void splitIntersectPlanes(GKPlane* _planeB,GKPlane* _planeA);
		void runSplitIntersectPlanes();
		void drawNetwork();
		void drawgkIntersectLines();
		void drawGKPlanesNew();

		//-----------DEBUG-FUNC-----------//
		void ofApp::debugDot();


		//-----------EVENT-----------//
		void keyPressed(int key) {
			//for (auto& gkPlane : gkPlanes) {
			//	gkPlane.keyPressed(key);// used:key -> none
			//}
			switch (key) {
			case 'h':
				bDebug = !bDebug;
				break;
			case 'f':
				ofToggleFullscreen();
				break;
			case 'r':
				resetCamera();
				break;
			case 'u':
				updateMesh();
				break;
			case '1':
				bHideMainMesh = !bHideMainMesh;
				break;
			case '2':
				bHideAddedMesh = !bHideAddedMesh;
				break;
			case '3':
				bHideGKPlane = !bHideGKPlane;
				break;
			case '4':
				bHideNetwork = !bHideNetwork;;
				break;
			case '5':
				bHideGKPlaneNew = !bHideGKPlaneNew;
				break;
			case '6':
				bHideSelectedPoint = !bHideSelectedPoint;
				break;
			case '7':
				bHideLight = !bHideLight;
				break;
			case 'z':
				if (gkPlanes.size())gkPlanes.pop_back();
				if (gkPlanesNew.size())gkPlanesNew.pop_back();
				if (gkIntersectLines.size())gkIntersectLines.pop_back();
				break;

			case 'l':
				ssGlobalLog.str("");
				ssGlobalLog.clear(std::stringstream::goodbit);
				ssGlobalLog << "CLEARED LOG" << endl;
				break;
			case 'c':
				gkPlanes.erase(gkPlanes.begin(), gkPlanes.end());
				gkIntersectLines.erase(gkIntersectLines.begin(), gkIntersectLines.end());
				gkPlanesNew.erase(gkPlanesNew.begin(), gkPlanesNew.end());
				bModified = !bModified;
				ssGlobalLog.str("");
				ssGlobalLog.clear(std::stringstream::goodbit);
				ssGlobalLog << "CLEARED LOG" << endl;
				ssGlobalLog << "CLEARED-ARRAYS" << endl;
				break;
			case 's':
				gk.saveImage();
				break;
			case 'm':
				meshToSave = getMeshFromGKPlanes(&gkPlanesNew);
				gk.saveMesh(meshToSave, 1);
				break;
			case ' ':
				//findPlaneIntersectionsBeta();
				setGKSplits();
				runGKSplits();
				break;
			case 'b':
				runSplitIntersectPlanes();
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
