#pragma once

#ifndef CLASS_IMG_PANELS_PANEL_H
#define CLASS_IMG_PANELS_PANEL_H

#include "Class_Panel.h"
#include "Class_ImgButton.h"

class Class_ImgButtonsPanel :public Class_Panel {
public:
	ofTrueTypeFont* font;

	vector<ofImage>* imgs;
	vector<string>* imgNames;
	vector<Class_ImgButton> imgButtons;
	
	ofImage** selectedImg;
	string** selectedImgID;

	bool bSelectImg;
	bool bGoBack;

	glm::vec2 panelPos;
	glm::vec2 panelSize;
	
	int margin;

	glm::vec2 mousePosOnPanel;

	string companyID;
	string materialID;
	string projectID;

	//================

	Class_ImgButtonsPanel() {
	}

	Class_ImgButtonsPanel(ofTrueTypeFont* _font,ofImage** _selectedImg,string** _selectedImgID,vector<ofImage>* _imgs,vector<string>* _imgNames,const string& _companyID,const string& _materialID,const string& _projectID) {
		font = _font;
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
		margin = 10;
		panelSize = glm::vec2(ofGetWidth()*3/4, 0);
		panelPos = glm::vec2((ofGetWidth()-panelSize.x)/2, ofGetHeight() / 8);
		mousePosOnPanel = glm::vec2(0);
		
		bSelectImg = false;
		bGoBack = false;
		setImgButtons();
		(* selectedImg) = &imgs->at(0);
		(*selectedImgID) = &imgNames->at(0);
	};

	void reset() {
		panelSize = glm::vec2(ofGetWidth() * 3 / 4, 0);
		panelPos = glm::vec2((ofGetWidth() - panelSize.x) / 2, ofGetHeight() / 4);
		mousePosOnPanel = glm::vec2(0);
		bSelectImg = false;
		bGoBack = false;
	}

	void update() {
		mousePosOnPanel = glm::vec2(ofGetMouseX(), ofGetMouseY())-panelPos;
	};

	void draw() {
		update();
		ofPushMatrix();
		ofTranslate(panelPos);
		drawTitle(glm::vec2(0, -margin - font->getSize()));
		for (auto& ib : imgButtons) {
			ib.draw();
		}
		ofPopMatrix();
	};

	void drawTitle(const glm::vec2& _pos) {
		font->drawString("SELECTED-MATERIAL", _pos.x, _pos.y + font->getSize());
	}


	bool IsMouseOn() { 
		bool _b = false;
		int _mx = ofGetMouseX();
		int _my = ofGetMouseY();
		if (panelPos.x < _mx && _mx < panelPos.x + panelSize.x && panelPos.y < _my && _my < panelPos.y + panelSize.y)_b = true;
		return _b;
	};

	void mouseScrolled(const float& _scrollY) {
		if (IsMouseOn()) {
			for (auto& btn : imgButtons)btn.mouseScrolled(_scrollY);
		}
	};

	void onMouseClicked() {
		for (auto& btn : imgButtons)btn.onMouseClicked();
	}

	void onWindowResized(const int& _w,const int& _h) {
		setup();
	}
	
	//================
	
	void setImgButtons() {
		imgButtons.erase(imgButtons.begin(), imgButtons.end());
		int _columns = 4;
		for (int i = 0; i < imgs->size(); i++) {
			float _x = panelSize.x / _columns;
			glm::vec2 _buttonSize = glm::vec2(_x,_x*2/3);
			glm::vec2 _buttonPos = glm::vec2(_x*(i%_columns),_x*2/3*(i/_columns));
			imgButtons.emplace_back(selectedImg,selectedImgID, &imgs->at(i), &imgNames->at(i), &bSelectImg,_buttonPos,_buttonSize, panelPos, panelSize);
		}
		panelSize.y = (imgs->size() - 1) / _columns * (panelSize.x / _columns);
		for (auto& bttn : imgButtons)bttn.setup();
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


