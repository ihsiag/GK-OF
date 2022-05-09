#pragma once
#ifndef SCENE_TWO_H  
#define SCENE_TWO_H 

#include "scenes/GKScene.h"
#include "scenes/sceneTwo/Class_Zone_Index_forSceneTwo.h"
#include "scenes/sceneTwo/Class_Zone_HeadTitle_forSceneTwo.h"
#include "scenes/sceneTwo/Class_Zone_Content_forSceneTwo.h"

class Scene_Two : public GKScene{

	public:
public:
	//-----------DEFAULT-----------//	
	unsigned long int currentFrame;
	float time;
	int globalMargin = 40;

	void initScene();
	void resetScene();
	void update();
	void draw();

	//-----------FOR-DEFAULT-----------//
	void initParam();

	//-----------FOR-SCENE-GLOBAL-VALUE-----------//		
	DataSet* dataSet;
	SceneAdminInfo adminInfo;
	vector<ofImage> imgsInPrj;
	vector<string> imgInPrjNames;

	//-----------FOR-SCENE-ZONE-----------//
	vector<Class_Zone*> zones;
	Class_IndexZone_forSceneTwo indexZone;
	Class_HeadTitleZone_forSceneTwo headTitleZone;
	Class_ContentZone_forSceneTwo contentZone;
	//Class_LinkButton_forSceneTwo linkButton;

	//-----------FOR-SCENE-SET-----------//
	void setDataSet(DataSet* _dataSet);
	void loadImgsInPrj();

	void setZones();
	void setButtons();

	//-----------FOR-SCENE-UPDATE-----------//
	void runZones();
	void runButtons();
	void showCurrentDataSet() {
		stringstream _ss;
		_ss << "prjId : " << dataSet->prjId << endl;
		_ss << "imgId : " << dataSet->imgId << endl;
		_ss << "posX : " << dataSet->posX << endl;
		_ss << "posY : " << dataSet->posY << endl;
		ofFill();
		glColor3f(0, 0, 0);
		ofDrawRectangle(glm::vec2(0), 400, 200);
		gk.drawInfo(_ss, glm::vec2(0));
	}

	//-----------FOR-SCENE-RESIZED-----------//
	void resizeZones();
	void resizeButtons();

	//-----------FOR-SCENE-EVENT-----------//
	bool goBack() {
		return adminInfo.bBack;
	};

	bool goNext() {
		//*dataSet = adminInfo.dataSet;
		return adminInfo.bGo;
	};

	DataSet setBackDataSet() {
		return adminInfo.dataSet;
	};

	//or write into "EVENT" below

	//-----------EVENT-----------//
	void keyPressed(int key) {
		switch (key) {// s,f,h already in use
		case' ':
			break;
		}
	}
	void keyReleased(int key) {}
	void mouseMoved(int x, int y) {}
	void mouseDragged(int x, int y, int button) {}
	void mousePressed(ofMouseEventArgs& args) {
		if (args.button == OF_MOUSE_BUTTON_LEFT) {
			for (auto& zone : zones)zone->onMouseClicked();
		}
	}

	void mousePressed(int x, int y, int button) {}
	void mouseReleased(int x, int y, int button) {}
	void mouseEntered(int x, int y) {}
	void mouseExited(int x, int y) {}
	void mouseScrolled(int x, int y, float scrollX, float scrollY) {
		for (auto& zone : zones)zone->mouseScrolled(scrollY);
	}
	void windowResized(int w, int h) {
		indexZone.onWindowResized(w - globalMargin * 2, h);
		headTitleZone.onWindowResized(w - globalMargin * 2, h);
		contentZone.onWindowResized(w - globalMargin * 2, h);
	}
	void dragEvent(ofDragInfo dragInfo) {}
	void gotMessage(ofMessage msg) {}	
};

#endif
