#pragma once

#ifndef CLASS_EDIT_PANEL_H  
#define CLASS_EDIT_PANEL_H

#include "Class_Panel.h"
#include "ofxCsv.h"

class Class_EditPanel:public Class_Panel {
public:
	ofxCsv csvToExport;
	string companyID;
	string materialID;
	string projectID;

	ofImage** selectedImg;
	string** selectedImgID;
	
	glm::vec2 panelPos;
	glm::vec2 panelSize;

	int margin;

	glm::vec2 imgAreaPos;
	glm::vec2 imgAreaSize;
	glm::vec2 imgPos;
	glm::vec2 imgSize;
	
	float imgRatio;

	bool bGoNext;
	bool bGoBack;

	bool bMouseDisabled;

	glm::vec2 customFormatAreaPos;
	vector<glm::vec2> selectedAreas;
	
	Class_EditPanel() {}

	Class_EditPanel(ofImage** _selectedImg, string ** _selectedImgID, const string& _companyID,const string& _materialID, const string& _projectID) {
		companyID = _companyID;
		materialID = _materialID;
		projectID = _projectID;
		
		panelPos = glm::vec2(0);
		panelSize = glm::vec2(ofGetWidth(), ofGetHeight());

		margin = 0;

		imgAreaSize = panelSize / 2;
		imgAreaPos = panelSize / 2 - imgAreaSize / 2;
		
		selectedImg = _selectedImg;	
		selectedImgID = _selectedImgID;

		bGoNext = false;
		bGoBack = false;

		bMouseDisabled = true;
		customFormatAreaPos = glm::vec2(0);
	}
	~Class_EditPanel() {}
	
	void setup() {
		imgRatio = (*selectedImg)->getWidth() / (*selectedImg)->getHeight();

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

		selectedAreas.erase(selectedAreas.begin(), selectedAreas.end());
		readCsv();
	};

	void reset() {
		bGoNext = false;
		bGoBack = false;

		bMouseDisabled = true;
		customFormatAreaPos = glm::vec2(0);

		imgRatio = (*selectedImg)->getWidth() / (*selectedImg)->getHeight();

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

		readCsv();
	}

	void update() {
		customFormatAreaPos = getcustomFormatAreaPos(ofGetMouseX(), ofGetMouseY());
	}

	void draw() {
		glColor4f(1, 1, 1, 1);
		ofNoFill();
		drawImg();

		stringstream info;
		createInfoPanel(&info);
		gk.drawInfo(info, glm::vec2(ofGetWidth()/4, ofGetHeight()*3/4));

		drawCurrentCircle();	
		drawStampedCircle();
	};

	void drawImg() {
		ofPushMatrix();
		ofTranslate(imgAreaPos+imgPos);
		(*selectedImg)->draw(glm::vec2(0), imgSize.x, imgSize.y);
		ofPopMatrix();
	}

	void drawCurrentCircle() {
		ofFill();
		glColor4f(0.7, 0,0, 0.8);
		ofDrawCircle(getDefaultFormatPos(customFormatAreaPos), 20);
		glColor4f(1, 1, 1,1);
		ofNoFill();
		glColor3f(1, 0, 0);
		ofDrawCircle(getDefaultFormatPos(customFormatAreaPos),20);
		glColor3f(1, 1, 1);
	}

	void drawStampedCircle() {
		for (auto& sa : selectedAreas) {
			ofFill();
			glColor4f(0.7, 0, 0.7, 0.8);
			ofDrawCircle(getDefaultFormatPos(sa), 20);
			glColor4f(1, 1, 1, 1);
			ofNoFill();
			glColor3f(1, 0, 1);
			ofDrawCircle(getDefaultFormatPos(sa), 20);
			glColor3f(1, 1, 1);
		}
	}
	
	void createInfoPanel(stringstream* _info) {
		*_info << "CURSOR-POS : " << customFormatAreaPos << endl;
		*_info << "AREA-NUM : " << selectedAreas.size() << endl;
		for (auto& sa: selectedAreas)*_info << "AREA-POS : " << sa << endl;
	}

	glm::vec2 getcustomFormatAreaPos(const float& _mousePosX, const float& _mousePosY) {
		glm::vec2 _range = glm::vec2(panelSize / imgSize);
		return glm::vec2(ofMap(_mousePosX, 0,panelSize.x, -_range.x, _range.x), ofMap(_mousePosY,0, panelSize.y, _range.y, -_range.y));
	}

	glm::vec2 getDefaultFormatPos(const glm::vec2& _customFormatPos) {
		glm::vec2 _range = glm::vec2(panelSize / imgSize);
		return glm::vec2(ofMap(_customFormatPos.x, -_range.x, _range.x, 0, panelSize.x), ofMap(_customFormatPos.y, _range.y, -_range.y, 0, panelSize.y));
	}

	void readCsv() {
		/*for (auto& line : lines) {
			selectedAreas.push_back(x, y);
		}*/
	}


	void writeCsv() {
		csvToExport.createFile("./" + companyID + "/OUTPUT/B.csv");
		for (auto& sa : selectedAreas) {
			ofxCsvRow row;
			row.setString(0, materialID);
			row.setString(1, projectID);
			row.setString(2, *(*selectedImgID));
			row.setFloat(3, sa.y);
			row.setFloat(4, sa.y);
			csvToExport.addRow(row);
		}
		csvToExport.save("./" + companyID + "/OUTPUT/B.csv");
		selectedAreas.erase(selectedAreas.begin(), selectedAreas.end());
	}

	bool IsMouseOn() { return false; }

	void mouseScrolled(const float& _scrollY) {
		float _scrollScale = 30;
		imgSize.y += _scrollScale*_scrollY;
		imgSize.x = imgSize.y * imgRatio;
		imgPos = imgAreaSize/2 - imgSize / 2;
	}

	void onMouseClicked() {
		if (glm::compMin(customFormatAreaPos) >= -1 && glm::compMax(customFormatAreaPos) <= 1) {
			selectedAreas.push_back(customFormatAreaPos);
		}
	}

	void onWindowResized(const int& _w,const int& _h) {
		panelPos = glm::vec2(0);
		panelSize = glm::vec2(_w,_h);
		imgSize = panelSize / 2;
		imgPos = panelPos/2 - imgSize / 2;
	}

	bool goNext() { return bGoNext; }

	bool goBack() { return bGoBack; }

	void keyPressed(const int& _key) {
		switch (_key) {
		case 'e':
			writeCsv();
			bGoNext = !bGoNext;
			break;
		case 'b':
			writeCsv();
			bGoBack = !bGoNext;
			break;
		}	
	}
};

#endif


