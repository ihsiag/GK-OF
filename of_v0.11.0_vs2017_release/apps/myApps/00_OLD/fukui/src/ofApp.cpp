#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	initSetting();
	initParam();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	//makeGrid(20);
	makeDimension();
	Y += 4;
	deltaThickness *= 1.008;
	//deltaThickness += 0.1;
	
	if (X > ofGetWidth()) {
		X = 0;
	}
	if (Y > ofGetHeight()*2) {
		Y = 0;
		deltaThickness = 5;
	}
	
	func02(X, Y, deltaThickness);

	
	for (int i = 0; i < num_pt; i++) {
		float max = ofGetWidth();
		pt[i].x += ofRandom(-1, 1);
		max = ofGetHeight();
		pt[i].y += ofRandom(-1, 1);
		func03(pt[i]);
	}

	if (tmpFrame > 240) {
		makeGrid(20);
	}
	if (tmpFrame > 300) {
		tmpFrame = 0;
	}
	/*
	ofVec2f mousePos = ofVec2f(mouseX, mouseY);
	walker.seek(mousePos);
	walker.update();
	walker.output();
	*/
	func04();
	tmpFrame ++;
	currentFrame++;

}

//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//my defs

void ofApp::initSetting() {
	ofSetBackgroundColor(0);
	ofEnableAntiAliasing();
	ofEnableAlphaBlending();
	//ofEnableBlendMode();
	ofEnableSmoothing();
}

void ofApp::initParam() {
	currentFrame = 0;
	X = 0;
	Y = 0;
	deltaThickness = 5;
	for (int i = 0; i < num_pt; i++) {
		float max = ofGetWidth();
		pt[i].x = ofRandom(max);
		max = ofGetHeight();
		pt[i].y = ofRandom(max);
	}
	
	//walker = ofWalker(200,200);
	tmpFrame = 0;
}

void ofApp::makeGrid(int _gridSize) {
	int size = _gridSize;
	int row = ofGetHeight() / size + 1;
	int col = ofGetWidth() / size + 1;
	int thickLine_per = 10;
	
	ofPoint start;
	ofPoint end;
	int counter_y = 0;
	int counter_x = 0;
	for (int y = 0; y < row; y++) {
		if (counter_y % thickLine_per == 0) {
			ofSetColor(250, 180);
			ofSetLineWidth(2);
		}
		else {
			ofSetColor(250, 80);
			ofSetLineWidth(1);
		}
		start.x = 0;
		start.y = y * size;
		end.x = ofGetWidth();
		end.y = y * size;
		ofLine(start.x, start.y, end.x, end.y);
		counter_y++;
	}
	for (int x = 0; x < col; x++) {
		if (counter_x % thickLine_per == 0) {
			ofSetColor(250, 180);
			ofSetLineWidth(2);
		}
		else {
			ofSetColor(250, 80);
			ofSetLineWidth(1);
		}
		start.x = x * size;
		start.y = 0;
		end.x = x * size;
		end.y = ofGetHeight();
		ofLine(start.x, start.y, end.x, end.y);
		counter_x++;
	}
}
void ofApp::makeDimension() {
	//local param

	int dim_large = 100;
	int dim_middle = 50;
	int dim_small = 5;

	int length_large = 16;
	int length_middle = 10;
	int length_small = 5;


	//upper

	for (int x = 0; x < ofGetWidth(); x++) {
		if (x % dim_large == 0) {
			int length = length_large;
			ofPoint start, end;
			start.x = x;
			start.y = 0;
			end.x = x;
			end.y = start.y + length;
			ofSetLineWidth(1);
			ofSetColor(255);
			ofDrawLine(start, end);

		}
		else if (x % dim_middle == 0) {
			int length = length_middle;
			ofPoint start, end;
			start.x = x;
			start.y = 0;
			end.x = x;
			end.y = start.y + length;
			ofSetLineWidth(1);
			ofSetColor(255);
			ofDrawLine(start, end);

		}
		else if (x % dim_small == 0) {
			int length = length_small;
			ofPoint start, end;
			start.x = x;
			start.y = 0;
			end.x = x;
			end.y = start.y + length;
			ofSetColor(255);
			ofSetLineWidth(0.25);
			ofDrawLine(start, end);
		}
	}

	//lower
	for (int x = 0; x < ofGetWidth(); x++) {
		if (x % dim_large == 0) {
			int length = length_large;
			ofPoint start, end;
			start.x = x;
			start.y = ofGetHeight();
			end.x = x;
			end.y = start.y-length;
			ofSetLineWidth(1);
			ofSetColor(255);
			ofDrawLine(start, end);

		}
		else if (x % dim_middle == 0) {
			int length = length_middle;
			ofPoint start, end;
			start.x = x;
			start.y = ofGetHeight();
			end.x = x;
			end.y = start.y-length;
			ofSetLineWidth(1);
			ofSetColor(255);
			ofDrawLine(start, end);

		}
		else if (x % dim_small == 0) {
			int length = length_small;
			ofPoint start, end;
			start.x = x;
			start.y = ofGetHeight();
			end.x = x;
			end.y = start.y-length;
			ofSetColor(255);
			ofSetLineWidth(0.25);
			ofDrawLine(start, end);
		}
	}

	//left
	for (int y = 0; y < ofGetHeight(); y++) {
		if (y % dim_large == 0) {
			int length = length_large;
			ofPoint start, end;
			start.x = 0;
			start.y = y;
			end.x = start.x+length;
			end.y = start.y;
			ofSetLineWidth(1);
			ofSetColor(255);
			ofDrawLine(start, end);

		}
		else if (y % dim_middle == 0) {
			int length = length_middle;
			ofPoint start, end;
			start.x = 0;
			start.y = y;
			end.x = start.x + length;
			end.y = start.y;
			ofSetLineWidth(1);
			ofSetColor(255);
			ofDrawLine(start, end);

		}
		else if (y % dim_small == 0) {
			int length = length_small;
			ofPoint start, end;
			start.x = 0;
			start.y = y;
			end.x = start.x + length;
			end.y = start.y;
			ofSetColor(255);
			ofSetLineWidth(0.25);
			ofDrawLine(start, end);
		}
	}


	//right
	for (int y = 0; y < ofGetHeight(); y++) {
		if (y % dim_large == 0) {
			int length = length_large;
			ofPoint start, end;
			start.x = ofGetWidth();
			start.y = y;
			end.x = start.x - length;
			end.y = start.y;
			ofSetLineWidth(1);
			ofSetColor(255);
			ofDrawLine(start, end);

		}
		else if (y % dim_middle == 0) {
			int length = length_middle;
			ofPoint start, end;
			start.x = ofGetWidth();
			start.y = y;
			end.x = start.x - length;
			end.y = start.y;
			ofSetLineWidth(1);
			ofSetColor(255);
			ofDrawLine(start, end);

		}
		else if (y % dim_small == 0) {
			int length = length_small;
			ofPoint start, end;
			start.x = ofGetWidth();
			start.y = y;
			end.x = start.x - length;
			end.y = start.y;
			ofSetColor(255);
			ofSetLineWidth(0.25);
			ofDrawLine(start, end);
		}
	}

}


void ofApp::func01(float _x, float _y, float _dThickness) {
	float x = _x;
	float y = _y;
	float dThickness = _dThickness;
	float minThickness = 1;
	int num = 20;
	int dist = 20;
	float H;
	float preH;
	float preY,curY;
	
	for (int i = 0; i < num; i++) {
		ofSetColor(255,0,0);
		H = dThickness + i * dThickness;
		if (i == 0) {
			curY = y;
		}
		else {
			//curY = preY + preH + dist;
			curY = preY + preH + preH; // dist = preH
		}
		ofRect(x, curY, ofGetWidth() * 2, H);
		preY = curY;
		preH = H;
	}
	

}
void ofApp::func02(float _x, float _y,float _dThickness) {
	float x = _x;
	float y = _y;
	float dThickness = _dThickness;
	float minThickness = 1;
	int num = 10;
	int dist = 20;
	float H;
	float preH;
	float preY,curY;
	
	for (int i = 0; i < num; i++) {
		ofSetColor(255, 0, 0);
		H = 100 -  dThickness*5;
		if (H < minThickness) {
			H = minThickness;
		}
		if (i == 0) {
			curY = y;
		}
		else {
			//curY = preY + preH + dist;
			curY = preY - preH - preH; // dist = preH
		}
		ofRect(x, curY, ofGetWidth() * 2, -H);
		preY = curY;
		preH = H;
	}
}
void ofApp::func03(ofPoint _pos) {
	ofPoint origin = _pos;
	int size = 30;
	ofPoint corner;
	corner.x = origin.x - size / 2;
	corner.y = origin.y - size / 2;
	ofNoFill();
	ofSetColor(255, 0, 0);
	ofRect(corner, size, size);
	ofPoint s,e;
	s.x = 0;
	e.x = ofGetWidth();
	s.y = origin.y;
	e.y = origin.y;
	ofLine(s, e);
	s.x = origin.x;
	e.x = origin.x;
	s.y = 0;
	e.y = ofGetHeight();
	ofLine(s, e);

}
void ofApp::func04() {
	ofSetColor(0, 150, 0);
	ofFill();
	ofRect(80, 50, 180, 180);
	ofNoFill();
}
void ofApp::func05(ofPoint _pos) {
	ofPoint pos = _pos;
	pos.x += 10;
	pos.y = 0;
	ofSetColor(0, 50, 50);
	ofRect(pos.x, pos.y, 5, 5);
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}