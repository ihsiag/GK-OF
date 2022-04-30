#pragma once

#ifndef CLASS_PANEl_STAMP_H  
#define CLASS_PANEL_STAMP_H

#include "components/panels/Class_Panel.h"

struct Ui_Stamped {
	ofImage* img;
	int initialLife;
	int lifeCounter;
	bool bAlive;
	Ui_Stamped() {
		bAlive = false;
	}
	Ui_Stamped(ofImage* _img) {
		img = _img;
		bAlive = true;
		initialLife = 60;
		lifeCounter = initialLife;
	}

	void update() {
		if(bAlive)lifeCounter -= 1;
		if (lifeCounter < 0)bAlive = false;
	}

	void draw(const glm::vec2& _pos) {
		glColor4f(1, 1, 1, float(lifeCounter) / float(initialLife));
		img->draw(_pos.x+20, _pos.y+20,img->getWidth()/2,img->getHeight()/2);
		glColor4f(1, 1, 1, 1);
	}
};

class Class_StampPanel_forSceneThree:public Class_Panel {
protected:

public:
	glm::vec2 parentGlobalPos;

	glm::vec2 panelSize;
	glm::vec2 panelPos;//relative to parentGlobalPos

	ofImage* uiElement;
	SceneAdminInfo* adminInfo;

	ofImage* img;

	float imgRatio;

	glm::vec2 imgAreaPos;
	glm::vec2 imgAreaSize;
	glm::vec2 imgPos;
	glm::vec2 imgSize;

	glm::vec2 mousePosOnPanel;
	vector<glm::vec2> selectedAreaPos;
	glm::vec2 customFormatAreaPos;

	Ui_Stamped uiStamped;

	glm::vec2 mouseDragAnchor;
	glm::vec2 panelDragAnchor;

	Class_StampPanel_forSceneThree(){}
	Class_StampPanel_forSceneThree(const glm::vec2& _parentGlobalPos, const glm::vec2& _panelPos, const glm::vec2 _panelSize,ofImage* _uiElement,SceneAdminInfo* _adminInfo, ofImage* _img) {
		parentGlobalPos = _parentGlobalPos;
		panelPos = _panelPos;
		panelSize = _panelSize;
		uiElement = _uiElement;

		adminInfo = _adminInfo;
		
		imgAreaSize = panelSize*0.8;
		imgAreaPos = panelSize / 2 - imgAreaSize / 2;
		
		img = _img;

		imgRatio = img->getWidth() / img->getHeight();

		float _w, _h;
		if (imgAreaSize.x > imgAreaSize.y) {
			_h = imgAreaSize.y;
			_w = _h * imgRatio;
		}
		else {
			_w = imgAreaSize.x;
			_h = _w / imgRatio;
		}
		imgSize = glm::vec2(_w, _h);
		imgPos = imgAreaSize / 2 - imgSize / 2;
	
		customFormatAreaPos = glm::vec2(0);

	}

	void setup() {};

	void reset() {};

	void update() {
		customFormatAreaPos = getcustomFormatAreaPos(ofGetMouseX()-parentGlobalPos.x-panelPos.x, ofGetMouseY()-parentGlobalPos.y-panelPos.y);
		if (selectedAreaPos.size())uiStamped.update();
	};

	void draw() {
		update();
		ofPushMatrix();
		ofTranslate(panelPos);
		glColor3f(1, 1, 1);
		drawImg();
		drawCurrentCircle();
		drawStampedCircle();
		ofPopMatrix();
	};

	void drawImg() {
		ofPushMatrix();
		ofTranslate(imgAreaPos + imgPos);
		img->draw(glm::vec2(0), imgSize.x, imgSize.y);
		ofPopMatrix();
	}

	void drawCurrentCircle() {
		/*ofFill();
		glColor4f(0.7, 0, 0, 0.8);
		ofDrawCircle(getDefaultFormatPos(customFormatAreaPos), 20);
		glColor4f(1, 1, 1, 1);
		ofNoFill();
		glColor3f(1, 0, 0);
		ofDrawCircle(getDefaultFormatPos(customFormatAreaPos), 20);
		glColor3f(1, 1, 1);*/
		if (glm::compMin(customFormatAreaPos) >= -1 && glm::compMax(customFormatAreaPos) <= 1) {

			glm::vec2 _mousePos = getDefaultFormatPos(customFormatAreaPos);
			glm::vec2 _minPos = getDefaultFormatPos(glm::vec2(-1, -1));
			glm::vec2 _maxPos = getDefaultFormatPos(glm::vec2(1, 1));

			glColor4f(1, 0, 0, 1);
			glPointSize(18);
			glBegin(GL_POINTS);
			glVertex2f(_mousePos.x, _mousePos.y);
			glEnd();

			glLineWidth(1);
			glBegin(GL_LINES);
			glVertex2f(_mousePos.x, _minPos.y);
			glVertex2f(_mousePos.x, _maxPos.y);
			glEnd();

			glBegin(GL_LINES);
			glVertex2f(_minPos.x, _mousePos.y);
			glVertex2f(_maxPos.x, _mousePos.y);
			glEnd();

			glColor3f(1, 1, 1);
		}
	}

	void drawStampedCircle() {
		for (auto& sap : selectedAreaPos) {
			/*ofFill();
			glColor4f(0.7, 0, 0.7, 0.8);
			ofDrawCircle(getDefaultFormatPos(sap), 20);
			glColor4f(1, 1, 1, 1);
			ofNoFill();
			glColor3f(1, 0, 1);
			ofDrawCircle(getDefaultFormatPos(sap), 20);
			glColor3f(1, 1, 1);*/
			glm::vec2 _pos = getDefaultFormatPos(sap);
			glm::vec2 _minPos = getDefaultFormatPos(glm::vec2(-1, -1));
			glm::vec2 _maxPos = getDefaultFormatPos(glm::vec2(1, 1));

			glColor4f(1, 0, 1, 1);
			glPointSize(30);
			glBegin(GL_POINTS);
			glVertex2f(_pos.x, _pos.y);
			glEnd();

			glColor4f(1, 0, 1, 0.5);
			glLineWidth(1);
			glBegin(GL_LINES);
			glVertex2f(_pos.x, _minPos.y);
			glVertex2f(_pos.x, _maxPos.y);
			glEnd();

			glBegin(GL_LINES);
			glVertex2f(_minPos.x, _pos.y);
			glVertex2f(_maxPos.x, _pos.y);
			glEnd();

			glColor4f(1, 1, 1,1);
			if(uiStamped.bAlive)uiStamped.draw(getDefaultFormatPos(sap));
		}
	}

	glm::vec2 getcustomFormatAreaPos(const float& _mousePosX, const float& _mousePosY) {
		glm::vec2 _range = glm::vec2(panelSize / imgSize);
		return glm::vec2(ofMap(_mousePosX, 0, panelSize.x, -_range.x, _range.x), ofMap(_mousePosY, 0, panelSize.y, _range.y, -_range.y));
	}

	glm::vec2 getDefaultFormatPos(const glm::vec2& _customFormatPos) {
		glm::vec2 _range = glm::vec2(panelSize / imgSize);
		return glm::vec2(ofMap(_customFormatPos.x, -_range.x, _range.x, 0, panelSize.x), ofMap(_customFormatPos.y, _range.y, -_range.y, 0, panelSize.y));
	}

	bool IsMouseOn() {
		bool _b = false;
		int _mx = ofGetMouseX();
		int _my = ofGetMouseY();
		if (parentGlobalPos.x + panelPos.x < _mx && _mx < parentGlobalPos.x + panelPos.x + panelSize.x && parentGlobalPos.y + panelPos.y < _my && _my < parentGlobalPos.y + panelPos.y + panelSize.y)_b = true;
		return _b;
	};

	void mouseScrolled(const float& _scrollY) {
		float _scrollScale = 30;
		imgSize.y += _scrollScale * _scrollY;
		imgSize.x = imgSize.y * imgRatio;
		imgPos = imgAreaSize / 2 - imgSize / 2;
	};

	void mouseDragged(const int& _x, const int& _y, const int& _button) {
		if (_button == 2) {//right
			glm::vec2 _currentMousePos = glm::vec2(ofGetMouseX(), ofGetMouseY());
			glm::vec2 _dif = _currentMousePos - mouseDragAnchor;
			panelPos = panelDragAnchor + _dif;
		}
	}

	void onMouseClicked() {
		if (glm::compMin(customFormatAreaPos) >= -1 && glm::compMax(customFormatAreaPos) <= 1) {
			selectedAreaPos.erase(selectedAreaPos.begin(), selectedAreaPos.end());
			selectedAreaPos.push_back(customFormatAreaPos);
			uiStamped = Ui_Stamped(uiElement);
			adminInfo->dataSet.posX = ofToString(selectedAreaPos[0].x);
			adminInfo->dataSet.posY = ofToString(selectedAreaPos[0].y);
		}
	};

	void onMouseRightClicked(){
		mouseDragAnchor = glm::vec2(ofGetMouseX(), ofGetMouseY());
		panelDragAnchor = panelPos;
	}

	void onWindowResized(const int& _w, const int& _h) {
		panelPos = glm::vec2(0);
		panelSize = glm::vec2(_w, _h);
		imgAreaSize = panelSize * 0.8;
		imgAreaPos = panelSize / 2 - imgAreaSize / 2;

		imgRatio = img->getWidth() / img->getHeight();

		float _iw, _ih;
		if (imgAreaSize.x > imgAreaSize.y) {
			_ih = imgAreaSize.y;
			_iw = _ih * imgRatio;
		}
		else {
			_iw = imgAreaSize.x;
			_ih = _iw / imgRatio;
		}
		imgSize = glm::vec2(_iw, _ih);
		imgPos = imgAreaSize / 2 - imgSize / 2;
	};

	void keyPressed(const int& _key) {};
};

#endif


