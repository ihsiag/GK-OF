#pragma once

#ifndef CLASS_PROJECT_LIST_PANEL_H  
#define CLASS_PROJECT_LIST_PANEL_H

#include "Class_Panel.h"
#include "Class_TxtButton.h"

class Class_ProjectListPanel:public Class_Panel {
public:
	vector<string>* projectIDs;
	vector<Class_TxtButton> projectIDButtons;
	ofTrueTypeFont* font;
	int* fontSize;
	int* fontHeight;

	glm::vec2 panelSize;
	glm::vec2 panelPos;
	glm::vec4 txtMargin;
	glm::vec2 txtPos;
	glm::vec2 txtSize;

	bool bGoBack;
	bool bGoNext;

	Class_ProjectListPanel() {}

	Class_ProjectListPanel(vector<string>* _projectIDs, ofTrueTypeFont* _font, int* _fontSize, int* _fontHeight) {
		projectIDs = _projectIDs;
		font = _font;
		fontSize = _fontSize;
		fontHeight = _fontHeight;
	}
	~Class_ProjectListPanel() {}
	
	void setup() {
		panelSize = glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.5);
		panelPos = glm::vec2(ofGetWidth() * 5 / 8, ofGetHeight() * 1 / 4);
		txtMargin = glm::vec4(10);
		txtPos = glm::vec2(txtMargin.x, txtMargin.y);
		txtSize = glm::vec2(panelSize.x - txtMargin.x - txtMargin.z, panelSize.y - txtMargin.y - txtMargin.w);
		
		projectIDButtons.erase(projectIDButtons.begin(), projectIDButtons.end());
		for (auto& id : *projectIDs) {
			projectIDButtons.emplace_back(&id,&font,&fontSize,&fontHeight,panelPos + txtPos);
		}
	};

	void reset() {
	};

	void update() {
	};

	void draw() {
		ofNoFill();
		glColor3f(0.3, 0.3, 0.3);
		glLineWidth(1);
		drawRect(panelPos, panelSize);
		ofPushMatrix();
		ofTranslate(panelPos);
		runProjectIDButtons();
		ofPopMatrix();
	};


	
	void createInfoPanel(stringstream* _info) {
	};

	void drawProjectIDButtons() {
		for (int i = 0; i < projectIDButtons.size(); i++) {
			float _y = txtPos.y + *fontHeight * (i + 1);
			if (_y > txtMargin.y && _y < txtSize.y-*fontHeight) {
				projectIDButtons[i].update(glm::vec2(txtPos.x,_y),glm::vec2(txtSize.x,*fontHeight));
			}
		}
	}
	
	void runProjectIDButtons() {
		for (int i = 0; i < projectIDButtons.size(); i++) {
			float _y = txtPos.y + *fontHeight * (i + 1);
			projectIDButtons[i].update(glm::vec2(txtPos.x, txtPos.y + *fontHeight*i), glm::vec2(txtSize.x, *fontHeight));
			if (_y > txtMargin.y && _y < txtSize.y - *fontHeight) {
				projectIDButtons[i].draw();
			}
		}
	}


	void drawRect(const glm::vec2& _pos, const glm::vec2& _size) {
		glBegin(GL_QUADS);
		glVertex2f(_pos.x, _pos.y);
		glVertex2f(_pos.x + _size.x, _pos.y);
		glVertex2f(_pos.x + _size.x, _pos.y + _size.y);
		glVertex2f(_pos.x, _pos.y + _size.y);
		glEnd();
	}
	

	bool IsMouseOn() {
		bool _b = false;
		int _mx = ofGetMouseX();
		int _my = ofGetMouseY();
		if (panelPos.x < _mx && _mx < panelPos.x + panelSize.x && panelPos.y < _my && _my < panelPos.y + panelSize.y)_b = true;
		return _b; 
	}

	void mouseScrolled(const float& _scrollY) {
		float _scrollScale = *fontHeight;
		if (IsMouseOn()) {
			txtPos.y += _scrollScale * _scrollY;
			if (txtPos.y > txtMargin.y)txtPos.y = txtMargin.y;
		}
	}

	void onMouseClicked() {
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


