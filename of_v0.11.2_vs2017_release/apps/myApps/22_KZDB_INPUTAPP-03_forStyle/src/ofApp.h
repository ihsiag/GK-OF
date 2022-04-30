#pragma once

#include "ofMain.h"
#include "GKScene.h"
#include "ofxGKUtils.h"
#include "DataSet.h"


class ofApp : public ofBaseApp{
	//*work as scene manager *//
private:
	ofxGKUtils gk;
	ofApp() {}
	~ofApp() {
		for (GKScene* gs : gkScenes) {
			delete gs;
		}
	}
	static std::shared_ptr<ofApp> instance;
public:
	static std::shared_ptr<ofApp> getInstance() {
		if (instance.get() == 0) instance.reset(new ofApp(), [](ofApp* p) { delete p; });
		return instance;
	}
	vector<GKScene*> gkScenes;
	void addGKScene(GKScene* _gkScene);
	
	DataSet dataSet;
	bool bDebug = false;
	vector<ofTrueTypeFont> fonts;
	ofTrueTypeFont fontS, fontM, fontS_bold, fontL_bold;

	ofImage uiMouse;
	vector<ofImage> uiElementsForIndexZone;
	vector<ofImage> uiElementsForHeadTitleZone;
	vector<ofImage> uiElementsForContentZone;
	
	void loadFonts() {
		cout << "<BEGIN LOAD FONTS>" << endl;
		string _filePath = "./font/Noto-Sans_JP/NotoSansJP-Light.otf";
		ofTrueTypeFont::setGlobalDpi(72);//72
		
		ofTrueTypeFontSettings settings(_filePath, 12);
		settings.antialiased = true;
		settings.contours = true;
		settings.simplifyAmt = 0.5;
		settings.addRanges(ofAlphabet::Japanese);
		settings.addRange(ofUnicode::Latin);
		settings.addRange(ofUnicode::Latin1Supplement);
		//    settings.addRange(ofUnicode::NumberForms);
		//    settings.addRange(ofUnicode::MathOperators);

		fontS.load(settings); // :: 12/16/300

		_filePath = "./font/Noto-Sans_JP/NotoSansJP-Light.otf";
		settings.fontName = _filePath;
		settings.fontSize = 18;
		fontM.load(settings); // :: 18/24/300

		_filePath = "./font/Noto-Sans_JP/NotoSansJP-Bold.otf";
		settings.fontName = _filePath;
		settings.fontSize = 12;
		fontS_bold.load(settings); // :: 12/16/700

		_filePath = "./font/Noto-Sans_JP/NotoSansJP-Black.otf";
		settings.fontName = _filePath;
		settings.fontSize = 24;
		fontL_bold.load(settings); // :: 24/32/800

		fonts.erase(fonts.begin(), fonts.end());
		fonts.push_back(fontS);
		fonts.push_back(fontM);
		fonts.push_back(fontS_bold);
		fonts.push_back(fontL_bold);
		cout << "<END LOAD FONTS>" << endl;
		cout << "= = = = = = = = = = =" << endl;
	}
	void loadUiElements() {
		cout << "<BEGIN LOAD UI-ELEMENTS>" << endl;
		uiMouse.loadImage("./ui/cursor/clickable.png");

		uiElementsForIndexZone.erase(uiElementsForIndexZone.begin(), uiElementsForIndexZone.end());
		ofImage _img;
		string _filePath;
		_filePath = "./ui/elements/index_selectProject.png";
		_img.loadImage(_filePath);
		uiElementsForIndexZone.push_back(_img);

		_filePath = "./ui/elements/index_selectImage.png";
		_img.loadImage(_filePath);
		uiElementsForIndexZone.push_back(_img);

		_filePath = "./ui/elements/index_selectPosition.png";
		_img.loadImage(_filePath);
		uiElementsForIndexZone.push_back(_img);

		uiElementsForHeadTitleZone.erase(uiElementsForHeadTitleZone.begin(), uiElementsForHeadTitleZone.end());

		_filePath = "./ui/elements/head_selectProject.png";
		_img.loadImage(_filePath);
		uiElementsForHeadTitleZone.push_back(_img);

		_filePath = "./ui/elements/head_selectImage.png";
		_img.loadImage(_filePath);
		uiElementsForHeadTitleZone.push_back(_img);

		_filePath = "./ui/elements/head_selectPosition.png";
		_img.loadImage(_filePath);
		uiElementsForHeadTitleZone.push_back(_img);

		uiElementsForContentZone.erase(uiElementsForContentZone.begin(), uiElementsForContentZone.end());

		_filePath = "./ui/elements/element_copied_en_styled.png";
		_img.loadImage(_filePath);
		uiElementsForContentZone.push_back(_img);

		/*_filePath = "./ui/elements/element_copied_ja.png";
		_img.loadImage(_filePath);
		uiElementsForContentZone.push_back(_img);*/
		cout << "<END LOAD UI-ELEMENTS>" << endl;
		cout << "= = = = = = = = = = =" << endl;
	}
	;

	int currentSceneIndex;
	float currentSceneSec;
	float currentSceneFloatFrame;
	int currentSceneFrame;
	float sceneStartSec;
	float lastSec;

	void setup();
	void update();
	void draw();

	void goNextScene() {
		currentSceneIndex++;
		currentSceneIndex %= gkScenes.size();
		cout << "<! SCENE CHANGED !>" << endl;
		gkScenes[currentSceneIndex]->resetScene();
		sceneStartSec = ofGetElapsedTimef();
	}

	void goBackScene() {
		currentSceneIndex--;
		if (currentSceneIndex < 0) currentSceneIndex += gkScenes.size();
		cout << "<! SCENE CHANGED !>" << endl;
		gkScenes[currentSceneIndex]->resetScene();
		sceneStartSec = ofGetElapsedTimef();
	}

	void keyPressed(int key) {
		gkScenes[currentSceneIndex]->keyPressed(key);
		switch (key) {
		case OF_KEY_RIGHT:
			goNextScene();
			break;
		case OF_KEY_LEFT:
			goBackScene();
			break;
		case 'f':
			ofToggleFullscreen();
			break;
		case 's':
			gk.saveImage();
			break;
		case 'h':
			bDebug = !bDebug;
			break;
		}
	};
	void keyReleased(int key) {
		gkScenes[currentSceneIndex]->keyReleased(key);
	};
	void mouseMoved(int x, int y) {
		gkScenes[currentSceneIndex]->mouseMoved(x, y);
	};
	void mouseDragged(int x, int y, int button) {
		gkScenes[currentSceneIndex]->mouseDragged(x, y,button);
	};
	void mousePressed(ofMouseEventArgs& args) {
		gkScenes[currentSceneIndex]->mousePressed(args);
	}
	void mousePressed(int x, int y, int button) {
		gkScenes[currentSceneIndex]->mousePressed(x, y, button);
	};
	void mouseReleased(int x, int y, int button) {
		gkScenes[currentSceneIndex]->mouseReleased(x, y, button);
	};
	void mouseEntered(int x, int y) {
		gkScenes[currentSceneIndex]->mouseEntered(x, y);
	};
	void mouseExited(int x, int y) {
		gkScenes[currentSceneIndex]->mouseExited(x, y);
	};
	void mouseScrolled(int x, int y, float scrollX, float scrollY) {
		gkScenes[currentSceneIndex]->mouseScrolled(x, y, scrollX, scrollY);
	};

	void windowResized(int w, int h) {
		gkScenes[currentSceneIndex]->windowResized(w, h);
	};
	void dragEvent(ofDragInfo dragInfo) {
		gkScenes[currentSceneIndex]->dragEvent(dragInfo);
	};
	void gotMessage(ofMessage msg) {
		gkScenes[currentSceneIndex]->gotMessage(msg);
	};
};
