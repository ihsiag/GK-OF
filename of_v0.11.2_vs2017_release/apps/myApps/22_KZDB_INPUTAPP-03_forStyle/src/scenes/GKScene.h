#pragma once
#include "ofMain.h"
#include "ofxGKUtils.h"

#include "DataSet.h"
#include "components/buttons/Class_Button_Link.h"
#include "components/zones/Class_Zone_Index.h"
#include "components/zones/Class_Zone_HeadTitle.h"
#include "components/zones/Class_Zone_Content.h"

struct SceneAdminInfo {
	SceneAdminInfo() {
		bGo = false;
		bBack = false;
		dataSet = DataSet();
	}
	bool bGo;
	bool bBack;
	DataSet dataSet;
};

class GKScene {
public:
	virtual ~GKScene() {}
	ofxGKUtils gk;
	bool *bDebug;
	ofTrueTypeFont *fontS, *fontM, *fontS_bold, *fontL_bold;

	ofImage* uiMouse;
	vector<ofImage>* uiElementsForIndexZone;
	vector<ofImage>* uiElementsForHeadTitleZone;
	vector<ofImage>* uiElementsForContentZone;

	/*Class_IndexZone indexZone;
	Class_HeadTitleZone headTitleZone;
	Class_ContentZone contentZone;
	Class_LinkButton linkButton;*/
	

	virtual void initScene() = 0;
	virtual void resetScene() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	
	virtual DataSet setBackDataSet() = 0;
	virtual bool goNext()=0;
	virtual bool goBack()=0;

	virtual void setDataSet(DataSet* _dataSet) = 0;
	
	void setFonts(vector<ofTrueTypeFont>* _fonts) {
		fontS = &_fonts->at(0);
		fontM = &_fonts->at(1);
		fontS_bold = &_fonts->at(2);
		fontL_bold = &_fonts->at(3);
	}

	void setUiElements(ofImage* _uiMouse, vector<ofImage>* _uiElementsForIndexZone, vector<ofImage>* _uiElementsForHeadTitleZone, vector<ofImage>* _uiElementsForContentZone) {
		uiMouse = _uiMouse;
		uiElementsForIndexZone = _uiElementsForIndexZone;
		uiElementsForHeadTitleZone = _uiElementsForHeadTitleZone;
		uiElementsForContentZone = _uiElementsForContentZone;
	}

	void setBoolDebug(bool* _bDebug) {
		bDebug = _bDebug;
	}
	
	virtual void keyPressed(int key) = 0;
	virtual void keyReleased(int key) = 0;
	virtual void mouseMoved(int x, int y) = 0;
	virtual void mouseDragged(int x, int y, int button) = 0;
	virtual void mousePressed(ofMouseEventArgs& args) {};
	virtual void mousePressed(int x, int y, int button) = 0;
	virtual void mouseReleased(int x, int y, int button) = 0;
	virtual void mouseEntered(int x, int y) = 0;
	virtual void mouseExited(int x, int y) = 0;
	virtual void mouseScrolled(int x, int y, float scrollX, float scrollY) = 0;
	virtual void windowResized(int w, int h) = 0;
	virtual void dragEvent(ofDragInfo dragInfo) = 0;
	virtual void gotMessage(ofMessage msg) = 0;

private:
};
