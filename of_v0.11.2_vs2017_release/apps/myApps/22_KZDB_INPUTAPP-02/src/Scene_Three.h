#pragma once
#ifndef SCENE_THREE_H  
#define SCENE_THREE_H 

#include "GKScene.h"

#include "Class_ImgButtonsPanel.h"
#include "Class_EditPanel.h"


class Scene_Three : public GKScene{

	public:
		//-----------DEFAULT-----------//
		unsigned long int currentFrame;
		float time;
		stringstream ssGlobalLog;

		//-----------GLOBAL-----------//	
		bool bDebug;
		ofTrueTypeFont fontM, fontL;

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
		DataSet* dataSet;
		
		vector<ofImage> imgs;
		vector<string> imgNames;
		ofImage* selectedImg;
		string* selectedImgID;

		vector<Class_Panel*> panels;		
		Class_ImgButtonsPanel imgButtonsPanel;
		Class_EditPanel editPanel;
		int currentPanelIndex;

		//-----------FOR-LIB-----------//
		void setDataSet(DataSet* _dataSet);
		void loadFont();
		void loadImgs();
		void inheriteCsv(); //here created this time
		void initPanels();
		void resetPanels();
		void managePanels();
		void runPanel();



		//-----------THIS-TIME-FUNCS-----------//
		

		//-----------THISTIME-SCENE-BRIDGE-----------//
		
		//-----------EVENT-----------//
		void keyPressed(int key) {
			panels[currentPanelIndex]->keyPressed(key);
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
				cout << "Scene_Three : clicked" << endl;
				panels[currentPanelIndex]->onMouseClicked();
			}
		}

		void mousePressed(int x, int y, int button) {}
		void mouseReleased(int x, int y, int button) {}
		void mouseEntered(int x, int y) {}
		void mouseExited(int x, int y) {}
		void mouseScrolled(int x, int y, float scrollX, float scrollY) {
			panels[currentPanelIndex]->mouseScrolled(scrollY);
		}
		void windowResized(int w, int h) {
			gk.resizeGUI(gui,13);
			panels[currentPanelIndex]->onWindowResized(w,h);
		}
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}
		
};

#endif
