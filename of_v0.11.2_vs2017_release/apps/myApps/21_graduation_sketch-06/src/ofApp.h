#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"



class ofApp : public ofBaseApp{

	public:
		vector<glm::vec3> special;
		vector<glm::vec3> specialTwo;

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
		bool bHideGKPlane;
		bool bHideGKPlaneScaled;
		bool bHideGKPlaneNew;


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
		vector<GKPlane> gkPlanes;
		vector<GKPlane> gkPlanesNew;
		
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
		void addGKPlane();

		void draw3DBeforeModified();
		void draw3DAfterModified();
		void drawMainMesh();

		vector<GKLineSimple> intersectLines;
		//loop-begin-îCà”ÇÃñ Ç™ê⁄ÇµÇƒÇ¢ÇÈñ Ç∑Ç◊Çƒ
		void findPlaneIntersections();
		void findPlaneIntersectionsBeta();
		vector<glm::vec3> getPlaneIntersection(const GKPlane& _gkPlaneCutter, const GKPlane& _gkPlane); //return line (point&vector)
		void scalePlaneEdge(GKLineSimple* _edge, const glm::vec3& _scalCenter, const float& _scaleFactor);
		
		void splitPlanes();
		GKPlane splitPlaneWithIntersectLine(const GKPlane& _gkPlane,const GKLineSimple& _gkLine);

		void findLineIntersection(); //input intersection line & return point
		//loop-end
		void makeMyNewFace(const vector<glm::vec3>& _vertices);
		void addMyNewFace();

		void drawIntersections();
		//-----------DEBUG-FUNC-----------//
		void ofApp::debugDot();


		//-----------EVENT-----------//
		void keyPressed(int key) {
			//for (auto& gkPlane : gkPlanes) {
			//	gkPlane.keyPressed(key);// used:key -> none
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
				bHideGKPlane = !bHideGKPlane;
				break;
			case '4':
				bHideGKPlaneScaled = !bHideGKPlaneScaled;
				break;
			case 's' :
				gk.saveImage();
				break;
			case 'z':
				if (gkPlanes.size())gkPlanes.pop_back();
				if (intersectLines.size())intersectLines.pop_back();
				break;
			case 'h':
				bDebug = !bDebug;
				break;
			case 'l':
				ssGlobalLog.str("");
				ssGlobalLog.clear(std::stringstream::goodbit);
				ssGlobalLog << "CLEARED LOG" << endl;
				break;
			case ' ':
				//findPlaneIntersections();
				findPlaneIntersectionsBeta();

				break;
			case 'c':
				gkPlanes.erase(gkPlanes.begin(), gkPlanes.end());
				intersectLines.erase(intersectLines.begin(), intersectLines.end());
				bModified = !bModified;
				ssGlobalLog << "CLEARED-ARRAYS" << endl;
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
