#pragma once

#ifndef CLASS_IMG_PANELS_PANEL_H
#define CLASS_IMG_PANELS_PANEL_H

#include "ofApp.h"
#include "ofxGKUtils.h"
#include "ofEasyCam.h"

#include "Class_Panel.h"
#include "Class_ImgButton.h"

class Class_ImgButtonsPanel :public Class_Panel {
public:
	vector<ofImage>* imgs;
	vector<string>* imgNames;
	vector<Class_ImgButton> imgButtons;
	
	ofImage** selectedImg;
	string** selectedImgID;

	bool bSelectImg;
	bool bGoBack;

	glm::vec2 pos;
	glm::vec2 size;
	

	glm::vec2 mousePosOnPanel;

	string companyID;
	string materialID;
	string projectID;

	//================

	Class_ImgButtonsPanel() {
	}

	Class_ImgButtonsPanel(ofImage** _selectedImg,string** _selectedImgID,vector<ofImage>* _imgs,vector<string>* _imgNames,const string& _companyID,const string& _materialID,const string& _projectID) {
		selectedImg = _selectedImg;
		selectedImgID = _selectedImgID;
		imgs = _imgs;
		imgNames = _imgNames;
		companyID = _companyID;
		materialID = _materialID;
		projectID = _projectID;
	}
	~Class_ImgButtonsPanel() {}
	
	//================

	void setup() {
		pos = glm::vec2(0,0);
		size = glm::vec2(ofGetWidth(), ofGetHeight());
		mousePosOnPanel = glm::vec2(0);
		bSelectImg = false;
		bGoBack = false;
		setImgButtons();
		(* selectedImg) = &imgs->at(0);
		(*selectedImg) = &imgNames->at(0);
	};

	void reset() {
		pos = glm::vec2(0, 0);
		size = glm::vec2(ofGetWidth(), ofGetHeight());
		mousePosOnPanel = glm::vec2(0);
		bSelectImg = false;
		bGoBack = false;
	}

	void update() {
		mousePosOnPanel = glm::vec2(ofGetMouseX(), ofGetMouseY())-pos;
	};

	void draw() {
		update();
		ofPushMatrix();
		ofTranslate(pos);
		for (auto& ib : imgButtons) {
			ib.draw();
		}
		ofDrawCircle(mousePosOnPanel, 10);
		ofPopMatrix();
	};

	bool IsMouseOn() { return false; };

	void mouseScrolled(const float& _scrollY) {
		float _scrollScale = 30;
		pos.y -= -_scrollScale * _scrollY;
		if (pos.y > 0)pos.y = 0;
	};

	void onMouseClicked() {
		for (auto& ib : imgButtons)ib.onMouseClicked();
	}

	void onWindowResized(const int& _w,const int& _h) {
		//pos;
		size = glm::vec2(_w,_h);
		resizeImgButtons();
	}
	
	//================
	
	void setImgButtons() {
		imgButtons.erase(imgButtons.begin(), imgButtons.end());
		for (auto& img : *imgs) {
			imgButtons.emplace_back(selectedImg,&img,&mousePosOnPanel,&bSelectImg);
		}
		resizeImgButtons();
	}

	void resizeImgButtons() {
		int columns = 4;
		glm::vec2 _sizeToDisplay = glm::vec2(ofGetWidth() / columns, ofGetHeight() / columns);
		for (int i = 0; i < imgButtons.size(); i++) {
			glm::vec2 _pos = glm::vec2(i % columns, i / columns) * _sizeToDisplay;
			imgButtons[i].onWindowResized(_pos, _sizeToDisplay);
		}
	}

	bool goNext() {
		return bSelectImg;
	}

	bool goBack() {
		return bGoBack;
	}

	void keyPressed(const int& _key) {
		switch (_key) {
		case 'b':
			bGoBack = !bGoBack;
			break;
		}
	}

};

#endif


