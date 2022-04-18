#pragma once

#ifndef CLASS_MAT_BUTTON_PANELS_PANEL_H
#define CLASS_MAT_BUTTON_PANELS_PANEL_H

#include "Class_Panel.h"
#include "Class_MatButton.h"

class Class_MatButtonsPanel :public Class_Panel {
public:
	ofTrueTypeFont* font;

	vector<ofImage>* imgs;
	vector<string>* imgNames;
	vector<Class_MatButton> matButtons;
	
	bool bGoNext;
	bool bGoBack;

	glm::vec2 panelPos;
	glm::vec2 panelSize;
	
	int margin;

	string companyID;
	string materialID;

	//================

	Class_MatButtonsPanel() {
	}

	Class_MatButtonsPanel(ofTrueTypeFont* _font,vector<ofImage>* _imgs,vector<string>* _imgNames,DataSet** _dataSet) {
		font = _font;
		imgs = _imgs;
		imgNames = _imgNames;
	}
	~Class_MatButtonsPanel() {}
	
	//================

	void setup() {
		margin = 10;
		panelSize = glm::vec2(ofGetWidth()*3/4, ofGetHeight()*3/4);
		panelPos = glm::vec2((ofGetWidth()-panelSize.x)/2, ofGetHeight() / 8);
		
		bGoNext = false;
		bGoBack = false;
		setMatButtons();
	};

	void reset() {
		panelSize = glm::vec2(ofGetWidth() * 3 / 4, ofGetHeight()*3/4);
		panelPos = glm::vec2((ofGetWidth() - panelSize.x) / 2, ofGetHeight() / 8);
		
		bGoNext = false;
		bGoBack = false;
	}

	void update() {
	};

	void draw() {
		update();
		ofPushMatrix();
		ofTranslate(panelPos);
		drawTitle(glm::vec2(0, -margin - font->getSize()));
		for (auto& ib : matButtons) {
			ib.draw();
		}
		ofPopMatrix();
	};

	void drawTitle(const glm::vec2& _pos) {
		font->drawString("SELECT-MATERIAL OR ADD-NEW-MATERIAL", _pos.x, _pos.y + font->getSize());
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
			for (auto& btn : matButtons)btn.mouseScrolled(_scrollY);
		}
	};

	void onMouseClicked() {
		for (auto& btn : matButtons)btn.onMouseClicked();
	}

	void onWindowResized(const int& _w,const int& _h) {
		setup();
	}
	
	//================
	
	void setMatButtons() {
		matButtons.erase(matButtons.begin(), matButtons.end());
		int _columns = 4;
		for (int i = 0; i < imgs->size(); i++) {
			float _w = panelSize.x / _columns;
			float _h = _w * 2 / 3;
			glm::vec2 _buttonSize = glm::vec2(_w,_h);
			glm::vec2 _buttonPos = glm::vec2(_w*(i%_columns),_h*(i/_columns));
			matButtons.emplace_back(&imgs->at(i), &imgNames->at(i),&bGoNext, _buttonPos, _buttonSize, panelPos, panelSize);
		}
		//panelSize.y = (imgs->size() - 1) / _columns * (panelSize.x / _columns);
		for (auto& bttn : matButtons)bttn.setup();
	}


	bool goNext() {
		return bGoNext;
	}

	bool goBack() {
		return bGoBack;
	}

	void keyPressed(const int& _key) {
		switch (_key) {
		case 'b':
			bGoBack = !bGoBack;
			break;
		case 'i':
			cout << IsMouseOn() << endl;
			break;
		}
	}
};

#endif


