#include "ofApp.h"

//--------------------------------------------------------------





int counter_frame;
int counter_scan;

ofPoint pos_scanner;
ofPoint pos_scanner_vertical;

int gridSize;
float radius;


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	ofSetCircleResolution(64);
	ofEnableAntiAliasing();
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	pos_scanner.x = 0;
	pos_scanner.y = 0;
	counter_frame = 0;
	counter_scan = 0;

	gridSize = 50;
	radius = 60;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	refresh();
	//base.makeOutline();
	base.makeGrid_black(10);
	base.makeGrid(gridSize);
	makeDimension();
	//makeCircle(radius);
	scanner();
	scanner_vertical();


	counter_frame += 1;
}


//--------------------------------------------------------------





void ofApp::makeDimension() {
	//upper
	for (int x = 0; x < ofGetWidth(); x++) {
		if (x % 100 == 0) {
			int length = 16;
			ofPoint start, end;
			start.x = x;
			start.y = 0;
			end.x = x;
			end.y = length;
			ofSetLineWidth(0.25);
			ofSetColor(255);
			ofDrawLine(start, end);

		} else if (x % 50 == 0) {
			int length = 10;
			ofPoint start, end;
			start.x = x;
			start.y = 0;
			end.x = x;
			end.y = length;
			ofSetLineWidth(0.25);
			ofSetColor(255);
			ofDrawLine(start, end);

		} else if (x % 5 == 0) {
			int length = 3;
			ofPoint start, end;
			start.x = x;
			start.y = 0;
			end.x = x;
			end.y = length;
			ofSetColor(255);
			ofSetLineWidth(0.25);
			ofDrawLine(start, end);
		}
		
	}

}
//--------------------------------------------------------------
void ofApp::makeCircle(float _radius) {
	ofSetColor(150, 0, 0);
	float r = _radius;
	float x = ofGetWidth() / 2;
	float y = ofGetHeight() / 2;
	ofCircle(x, y, r);
}
//--------------------------------------------------------------
void ofApp::scanner() {
	if (counter_frame % ofGetWidth() == 0) {
		counter_scan++;
	}
	pos_scanner.x = 4*counter_frame%(ofGetWidth()+gridSize*2) - gridSize * 5;
	pos_scanner.y = 0;
	ofSetColor(230,230,255,3);
	for (int i = 1; i <6* gridSize; i +=2) {
		ofRect(pos_scanner, -6*2*gridSize+i*2, ofGetHeight());
	}
}

void ofApp::scanner_vertical() {
	pos_scanner_vertical.x = 0;
	pos_scanner_vertical.y = 7*counter_frame%ofGetHeight();
	ofSetColor(220, 0, 0, 200);
	for (int i = 1; i < gridSize / 15; i++) {
		ofRect(pos_scanner_vertical,ofGetWidth(), -1*int(gridSize/15) + i);
	}


}

void ofApp::refresh() {
	int alpha;
	alpha = 255 - 3*counter_frame % 1800;
	ofSetColor(255, alpha);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}






//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
