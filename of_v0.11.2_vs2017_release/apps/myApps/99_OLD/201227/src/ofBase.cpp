#include "ofBase.h"


ofColor color_outline = (255, 0, 0);
ofColor color_grid = (250,180);

void ofBase::makeOutline() {
	ofSetColor(255);
	ofSetLineWidth(5);
	float list_x[4] = { 0, ofGetWidth(),ofGetWidth(), 0 };
	float list_y[4] = { 0, 0, ofGetHeight(), ofGetHeight() };
	for (int i = 0; i < 4; i++) {
		ofPoint start, end;
		start.x = list_x[i];
		start.y = list_y[i];
		if (i < 3) {
			end.x = list_x[i + 1];
			end.y = list_y[i + 1];
		}
		else {
			end.x = list_x[0];
			end.y = list_y[0];
		}
		ofDrawLine(start, end);
	}
}




void ofBase::makeGrid(int _gridSize) {
	int size = _gridSize;
	int row = ofGetHeight() / size + 1;
	int col = ofGetWidth() / size + 1;
	ofPoint start;
	ofPoint end;
	int counter_y = 0;
	int counter_x = 0;
	for (int y = 0; y < row; y++) {
		if (counter_y % 5 == 0) {
			ofSetColor(250, 180);
			ofSetLineWidth(0.5);
		}
		else {
			ofSetColor(250, 80);
			ofSetLineWidth(0.01);
		}
		start.x = 0;
		start.y = y * size;
		end.x = ofGetWidth();
		end.y = y * size;
		ofLine(start.x, start.y, end.x, end.y);
		counter_y++;
	}
	for (int x = 0; x < col; x++) {
		if (counter_x % 5 == 0) {
			ofSetColor(250, 180);
			ofSetLineWidth(0.5);
		}
		else {
			ofSetColor(250, 80);
			ofSetLineWidth(0.01);
		}
		start.x = x * size;
		start.y = 0;
		end.x = x * size;
		end.y = ofGetHeight();
		ofLine(start.x, start.y, end.x, end.y);
		counter_x++;
	}
}


void ofBase::makeGrid_black(int _gridSize) {
	int size = _gridSize;
	int row = ofGetHeight() / size + 1;
	int col = ofGetWidth() / size + 1;
	ofPoint start;
	ofPoint end;
	int counter_y = 0;
	int counter_x = 0;
	ofSetColor(0,100);
	ofSetLineWidth(1);
	for (int y = 0; y < row; y++) {

		start.x = 0;
		start.y = y * size;
		end.x = ofGetWidth();
		end.y = y * size;
		ofLine(start.x, start.y, end.x, end.y);
		counter_y++;
	}
	for (int x = 0; x < col; x++) {
		start.x = x * size;
		start.y = 0;
		end.x = x * size;
		end.y = ofGetHeight();
		ofLine(start.x, start.y, end.x, end.y);
		counter_x++;
	}
}