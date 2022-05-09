#pragma once
#ifndef SCENE_THREE_H  
#define SCENE_THREE_H 

#include "scenes/GKScene.h"
#include "scenes/sceneThree/Class_Zone_Index_forSceneThree.h"
#include "scenes/sceneThree/Class_Zone_HeadTitle_forSceneThree.h"
#include "scenes/sceneThree/Class_Zone_Content_forSceneThree.h"

class Scene_Three : public GKScene{

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
	ofImage imgToStamp;

	//-----------FOR-SCENE-ZONE-----------//
	vector<Class_Zone*> zones;
	Class_IndexZone_forSceneThree indexZone;
	Class_HeadTitleZone_forSceneThree headTitleZone;
	Class_ContentZone_forSceneThree contentZone;
	//Class_LinkButton_forSceneThree linkButton;

	//-----------FOR-SCENE-SET-----------//
	void setDataSet(DataSet* _dataSet);
	void loadImgToStamp();

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
	void mouseDragged(int x, int y, int button) {
		for (auto& zone : zones)zone->mouseDragged(x,y,button);
	}
	void mousePressed(ofMouseEventArgs& args) {
		if (args.button == OF_MOUSE_BUTTON_LEFT) {
			for (auto& zone : zones)zone->onMouseClicked();
			*dataSet = adminInfo.dataSet;
			string _outputString = dataSet->prjId + "=" + dataSet->imgId + "=" + dataSet->posX + "=" + dataSet->posY;
			if (dataSet->posX != "not selected") {
				ofGetWindowPtr()->setClipboardString(_outputString);
				cout << "- - " << _outputString << endl;
				cout << "<! INFO COPIED TO YOUR CLIPBOARD  !>" << endl;
			}
		}
		if (args.button == OF_MOUSE_BUTTON_RIGHT) {
			for (auto& zone : zones)zone->onMouseRightClicked();
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
		//for (auto& zone : zones)zone->onWindowResized(w-globalMargin*2, h);
		indexZone.onWindowResized(w - globalMargin * 2, h);
		headTitleZone.onWindowResized(w - globalMargin * 2,h);
		contentZone.onWindowResized(w - globalMargin * 2,h);
	}
	void dragEvent(ofDragInfo dragInfo) {}
	void gotMessage(ofMessage msg) {}
		
};

#endif
