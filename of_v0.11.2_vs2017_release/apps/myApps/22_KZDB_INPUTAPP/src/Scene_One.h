#pragma once
#ifndef SCENE_ONE_H  
#define SCENE_ONE_H 

#include "GKScene.h"
#include "ofxCsv.h"

class Scene_One : public GKScene{

	public:
		//-----------DEFAULT-----------//	
		unsigned long int currentFrame;
		float time;
		stringstream ssGlobalLog;

		//-----------GLOBAL-----------//	
		bool bDebug;
		ofTrueTypeFont fontM,fontL;
		int fontMSize, fontLSize;
		int fontMHeight, fontLHeight;

		//-----------SLIDER-----------//
		ofxGuiGroup gui;

		
		void setup();
		void resetScene();
		void update();
		void draw();

		//-----------FOR-DEFAULT-----------//
		void initParam();
		void initGKSet();
		void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);

		//-----------LIB-----------//
	

		//-----------FOR-LIB-----------//
		DataSet* dataSet;
		void setDataSet(DataSet* _dataSet);
		void updateDataSet() {
			(* dataSet).companyID = "company-A";
			(* dataSet).materialID = "material-001";
		}



		//-----------THIS-TIME-FUNCS-----------//
		

		//-----------THISTIME-SCENE-BRIDGE-----------//
		
		//-----------EVENT-----------//
		void keyPressed(int key) {
			switch (key) {
			case ' ':
				//toggleAnimate();
				break;
			case 'f':
				ofToggleFullscreen();
				break;
			case 'h':
				bDebug = !bDebug;
				break;
			case 'r':
				//resetAnimationClasses();
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
				cout << "=========================================" << endl;
				cout << "Scene_One : clicked" << endl;
			}
		}

		void mousePressed(int x, int y, int button) {}
		void mouseReleased(int x, int y, int button) {}
		void mouseEntered(int x, int y) {}
		void mouseExited(int x, int y) {}
		void mouseScrolled(int x, int y, float scrollX, float scrollY) {
		}
		void windowResized(int w, int h) {
			gk.resizeGUI(gui,13);
		}
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}
		
};

#endif
