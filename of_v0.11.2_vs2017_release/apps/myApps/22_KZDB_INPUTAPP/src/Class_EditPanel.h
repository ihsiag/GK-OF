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

	/*glm::vec2 imgPos;
	glm::vec2 imgSize;*/

	glm::vec2 selectedImgPos;
	glm::vec2 selectedImgSize;
	


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
		
		selectedImg = _selectedImg;	
		selectedImgID = _selectedImgID;

		selectedImgSize = panelSize/2;
		selectedImgPos = panelSize/2-selectedImgSize/2;

		bGoNext = false;
		bGoBack = false;

		bMouseDisabled = true;
		customFormatAreaPos = glm::vec2(0);
	}
	~Class_EditPanel() {}
	
	void setup() {
		selectedAreas.erase(selectedAreas.begin(), selectedAreas.end());
		readCsv();
	};

	void reset() {
		panelPos = glm::vec2(0);
		panelSize = glm::vec2(ofGetWidth(), ofGetHeight());
		selectedImgSize = panelSize / 2;
		selectedImgPos = panelSize / 2 - selectedImgSize / 2;
		bGoNext = false;
		bGoBack = false;

		bMouseDisabled = true;
		customFormatAreaPos = glm::vec2(0);

		readCsv();
	}

	void update() {
		customFormatAreaPos = getcustomFormatAreaPos(ofGetMouseX(), ofGetMouseY());
	}

	void draw() {
		ofFill();
		glColor4f(0, 0, 0, 0.6);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(ofGetWidth(), 0);
		glVertex2f(ofGetWidth(), ofGetHeight());
		glVertex2f(0, ofGetHeight());
		glEnd();

		glColor4f(1, 1, 1, 1);
		ofNoFill();
		(*selectedImg)->draw(selectedImgPos, selectedImgSize.x, selectedImgSize.y);

		stringstream info;
		createInfoPanel(&info);
		gk.drawInfo(info, glm::vec2(ofGetWidth()/4, ofGetHeight()*3/4));

		drawCurrentCircle();	
		drawStampedCircle();
	};

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
		glm::vec2 _range = glm::vec2(panelSize / selectedImgSize);
		return glm::vec2(ofMap(_mousePosX, 0,panelSize.x, -_range.x, _range.x), ofMap(_mousePosY,0, panelSize.y, _range.y, -_range.y));
	}

	glm::vec2 getDefaultFormatPos(const glm::vec2& _customFormatPos) {
		glm::vec2 _range = glm::vec2(panelSize / selectedImgSize);
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
		selectedImgSize.x += _scrollScale*_scrollY;
		selectedImgSize.y += _scrollScale*_scrollY;
		selectedImgPos = glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2) - selectedImgSize / 2;
	}

	void onMouseClicked() {
		if (glm::compMin(customFormatAreaPos) >= -1 && glm::compMax(customFormatAreaPos) <= 1) {
			selectedAreas.push_back(customFormatAreaPos);
		}
	}

	void onWindowResized(const int& _w,const int& _h) {
		//panelPos;
		panelSize = glm::vec2(_w,_h);
		selectedImgSize = panelSize / 2;
		selectedImgPos = panelPos/2 - selectedImgSize / 2;
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


