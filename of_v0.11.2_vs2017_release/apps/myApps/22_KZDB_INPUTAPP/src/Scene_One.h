#pragma once
#ifndef SCENE_ONE_H  
#define SCENE_ONE_H 

#include "ofMain.h"
#include "GKScene.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

#include "Class_ImgPanel.h"
#include "Class_EditPanel.h"

class Scene_One : public GKScene{

	public:
		//-----------DEFAULT-----------//
		ofxGKUtils gk;		
		ofEasyCam cam;
		unsigned long int currentFrame;
		float time;
		stringstream ssGlobalLog;

		//-----------LIB-----------//
		unsigned int animationFrame;
		int animationIndex;
		bool bPlayAnimation;


		//-----------GLOBAL-----------//
		
		bool bDebug;

		//-----------SLIDER-----------//
		ofxGuiGroup gui;

		
		void setup();
		void resetScene();
		void update();
		void draw();

		//-----------FOR-LIB-----------//
		void initParam();
		void initGKSet();
		void resetCamera();
		/*void initAnimationClasses();
		void resetAnimationClasses();
		void manageAnimationClasses();*/
		void toggleAnimate();

	
		void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);


		//-----------THIS-TIME-FUNCS-----------//
		
		vector<ofImage> imgs;
		ofImage* selectedImg;
		vector<Class_ImgPanel> imgPanels;
		Class_EditPanel editPanel;

		void loadImgs();
		void resizeImgs();
		
		void setImgPanels();
		void resizeImgPanels();
		void drawImgPanels();

		void initEditPanel();
		void resizeEditPanel();
		void drawEditPanel();


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
				for (auto& ip : imgPanels)ip.onMouseClicked();
				editPanel.onMouseClicked();
			}
		}

		void mousePressed(int x, int y, int button) {}
		void mouseReleased(int x, int y, int button) {}
		void mouseEntered(int x, int y) {}
		void mouseExited(int x, int y) {}
		void mouseScrolled(int x, int y, float scrollX, float scrollY) {
			gk.scrollCamera(&cam,scrollY);
		}
		void windowResized(int w, int h) {
			gk.resizeGUI(gui,13);
			resizeImgPanels();
			resizeEditPanel();
		}
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}
		
};

#endif
