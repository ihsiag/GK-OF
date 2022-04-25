#pragma once

#ifndef CLASS_PROJECT_BUTTONS_PANEL_H  
#define CLASS_PROJECT_BUTTONS_PANEL_H

#include "Class_Panel.h"
#include "Class_ProjectButton.h"

class Class_ProjectButtonsPanel:public Class_Panel {
public:
	DataSet** dataSet;
	vector<string>* projectIDs;
	vector<Class_ProjectButton> projectIDButtons;
	ofTrueTypeFont* font;

	glm::vec2 panelSize;
	glm::vec2 panelPos;

	int margin;

	glm::vec2 txtAreaPos;
	glm::vec2 txtAreaSize;

	bool bGoBack;
	bool bGoNext;

	Class_ProjectButtonsPanel() {}

	Class_ProjectButtonsPanel(DataSet** _dataSet,vector<string>* _projectIDs, ofTrueTypeFont* _font) {
		dataSet = _dataSet;
		projectIDs = _projectIDs;
		font = _font;
	}
	~Class_ProjectButtonsPanel() {}
	
	void setup() {
		panelSize = glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.5);
		panelPos = glm::vec2(ofGetWidth() * 5 / 8, ofGetHeight() * 1 / 4);
		
		margin = 10;
		
		txtAreaSize = panelSize-glm::vec2(2*margin);
		txtAreaPos = glm::vec2(margin);
		
		projectIDButtons.erase(projectIDButtons.begin(), projectIDButtons.end());
		/*for (int i = 0; projectIDs->size(); i++) {
			projectIDButtons.emplace_back(&projectIDs->at(i), &font, &fontSize, panelPos + txtAreaPos + glm::vec2(0, *fontSize * i), txtAreaSize);
		}*/
		int _index = 0;
		for (auto&id:*projectIDs) {
			projectIDButtons.emplace_back(dataSet,&id, &font, glm::vec2(0, _index * font->getSize()), panelPos + txtAreaPos,txtAreaSize);
			_index++;
		}
		for (auto& bttn : projectIDButtons)bttn.setup();
	};

	void reset() {
	};

	void update() {

	};

	void draw() {
		ofNoFill();
		glColor3f(0.7, 0.3, 0.3);
		glLineWidth(1);
		drawOutline(panelPos, panelSize);
		ofPushMatrix();
		ofTranslate(panelPos);
		drawProjectIDButtons();
		glColor3f(1, 1, 1);
		drawTitle(glm::vec2(0, -margin - font->getSize()));
		ofPopMatrix();
	};
	
	void drawProjectIDButtons() {
		ofPushMatrix();
		ofTranslate(txtAreaPos);
		for (auto& btn : projectIDButtons) {
			if (btn.buttonLocalPos.y >= 0 && btn.buttonLocalPos.y + btn.buttonSize.y < txtAreaSize.y) {
				btn.draw();
			}
		}
		ofPopMatrix();
	}


	void drawOutline(const glm::vec2& _pos, const glm::vec2& _size) {
		glBegin(GL_QUADS);
		glVertex2f(_pos.x, _pos.y);
		glVertex2f(_pos.x + _size.x, _pos.y);
		glVertex2f(_pos.x + _size.x, _pos.y + _size.y);
		glVertex2f(_pos.x, _pos.y + _size.y);
		glEnd();
	}

	void drawTitle(const glm::vec2& _pos) {
		font->drawString("SELECT PROJECT BELOW", _pos.x, _pos.y + font->getSize());
	}
	

	bool IsMouseOn() {
		bool _b = false;
		int _mx = ofGetMouseX();
		int _my = ofGetMouseY();
		if (panelPos.x < _mx && _mx < panelPos.x + panelSize.x && panelPos.y < _my && _my < panelPos.y + panelSize.y)_b = true;
		return _b; 
	}

	void mouseScrolled(const float& _scrollY) {
		if (IsMouseOn()) {
			for (auto& btn : projectIDButtons)btn.mouseScrolled(_scrollY);
		}
	}

	void onMouseClicked() {
		//if (IsMouseOn()) {
			for (auto& btn : projectIDButtons)btn.onMouseClicked();
		//}
	}

	void onWindowResized(const int& _w,const int& _h) {
		setup();
	}

	bool goNext() { return bGoNext; }

	bool goBack() { return bGoBack; }

	void keyPressed(const int& _key) {
		switch (_key) {
		case 'e':
			break;
		case 'b':
			break;
		}	
	}
};

#endif


