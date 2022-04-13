#pragma once
#ifndef SCENE_ONE_H  
#define SCENE_ONE_H 

#include "GKScene.h"
#include "ofxCsv.h"

#include "Class_MatImgPanel.h"
#include "Class_ProjectListPanel.h"


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
		string companyID = "companyA";
		string materialID = "materialA";

		//-----------FOR-LIB-----------//
		Class_MatImgPanel matImgPanel;
		Class_ProjectListPanel projectListPanel;

		vector<Class_Panel*> panels;

		ofImage matImg;
		ofxCsv csv;
		vector<string> projectIDs;

		void loadFont();
		void loadMatImg();
		void loadProjectList();
		
		void initPanels();
		void resetPanels();
		void managePanels();
		void runPanel();

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
			projectListPanel.mouseScrolled(scrollY);
		}
		void windowResized(int w, int h) {
			gk.resizeGUI(gui,13);
			for (auto& pnl : panels)pnl->onWindowResized(w, h);
		}
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}
		
};

#endif
