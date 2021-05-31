#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	initParam();
	initSetting();
}

//--------------------------------------------------------------
void ofApp::update() {
	//write about fbo
	
	//fbo01
	fbo01.begin();
	ofClear(50, 180, 50);
	ofFill();
	ofSetColor(50, 180, 50);
	ofRect(0, 0, fbo01.getWidth(), fbo01.getHeight());
	ofNoFill();
	func08(func08Angle, func06Angle);
	fbo01.end();

	//

}

//--------------------------------------------------------------
void ofApp::draw() {
	
	//default (start)
	for (int i = 0; i < num_walker; i++) {
		walkers[i].run();
	}
	
	//
	func07();
	
	

	

	func08Angle += 1;

	


	/*
	//walkerFinder
	if (currentFrame % (4*sec) ==(4*sec-1)) {
		int id = 0;
		if (boolWalkerFinder == false && id == 0) {
			boolWalkerFinder = true;
			id = 1;
		}
		if (boolWalkerFinder == true && id == 0) {
			boolWalkerFinder = false;
			id = 1;
		}
	}
	if (boolWalkerFinder == true) {
		makeGrid(20);
		for (int i = 0; i < num_walker; i++) {
			walkerFinder(walkers[i].returnLoc());
		}
	}
	*/
	
	boolFunc06 = funcDo(boolFunc06, 8, currentFrame);
	if (boolFunc06 == true) {
		if (func06Size > ofGetWidth() / 2) {
			func06(func06Size, func06Angle);
			func06Size -= 1;
		}
		else {
			func06(func06Size, func06Angle);
			func06Angle += 0.1;
			//func06Size += 1;
		}

		if (currentFrame % 900 == 0) {
			func06Size = ofGetWidth();
		}
	}
	boolFbo01 = funcDo(boolFbo01, 16, currentFrame);
	if (boolFbo01 == true) {
		fbo01.draw(0, ofGetHeight() / 2 - fbo01.getHeight() / 2, fbo01.getWidth(), fbo01.getHeight());
	}	
	boolWalkerFinder = funcDo(boolWalkerFinder, 4, currentFrame);
	if (boolWalkerFinder == true) {
		func01();
	}



	//walkers
	for (int i = 0; i < num_walker; i++) {
		walkers[i].display();
	}

	
	func09();
	//default (end)

	if (currentFrame > 30 * sec) {
		currentFrame = 0;
	}
	else {
		currentFrame++;
	}

	ui();
}
//--------------------------------------------------------------
//--------------------------------------------------------------
//my essential defs

bool ofApp::funcDo(bool _bool, int _second, int _frame) {
	if (_frame % (_second * sec) == (_second * sec - 1)) {
		int id = 0;
		if (_bool == false && id == 0) {
			_bool = true;
			id = 1;
		}
		if (_bool == true && id == 0) {
			_bool = false;
			id = 1;
		}
	}
	return _bool;
}

void ofApp::initSetting() {
	ofSetFrameRate(sec);
	ofSetBackgroundColor(0);
	ofEnableAntiAliasing();
	ofEnableAlphaBlending();
	//ofEnableBlendMode();
	ofEnableSmoothing();
	ofSetBackgroundAuto(true);
}

void ofApp::initParam() {
	//class init
	//walker
	for (int i = 0; i < num_walker; i++) {
		int tmpX = ofRandom(0, ofGetWidth());
		int tmpY = ofRandom(0, ofGetHeight());
		walkers[i] = Walker(tmpX, tmpY);
	}


	//func param
	boolWalkerFinder = false;
	boolFunc06 = false;

	func06Size = ofGetWidth();
	func06Angle = 0;
	func08Angle = 0;

	//img

	//3d
	threeDModel.loadModel("StoneBig.3ds", 20);


	//font
	ofTrueTypeFont::setGlobalDpi(72);
	fontSize = 15;
	font.load("SourceCodePro-Light.ttf", fontSize);
	font.setLineHeight(fontSize);
	font.setLetterSpacing(1.0);
	
	//fbo
	fbo01.allocate(ofGetWidth(), ofGetHeight() / 10);


	//default
	sec = 30; // frame to second
	oneCool = 30 * sec;
	currentFrame = 0;
}

void ofApp::ui() {
	//fps
	string fpsToPrint = ofToString(ofGetFrameRate());
	ofFill();
	ofSetColor(255);
	ofRectangle bbofFPS = font.getStringBoundingBox(fpsToPrint, 50, 50);
	ofRect(bbofFPS);
	ofNoFill();
	ofSetColor(255, 0, 0);
	font.drawString(fpsToPrint, 50, 50);
	
	//dimension
	makeDimension();
}



//--------------------------------------------------------------
//--------------------------------------------------------------
//my defs

void ofApp::makeGrid(int _gridSize) {
	int size = _gridSize;
	int row = ofGetHeight() / size + 1;
	int col = ofGetWidth() / size + 1;
	int thickLine_per = 10;

	ofPoint start;
	ofPoint end;
	int counter_y = 0;
	int counter_x = 0;
	int greyScale = 130;
	
	for (int y = 0; y < row; y++) {
		if (counter_y % thickLine_per == 0) {
			ofSetColor(greyScale, 180);
			ofSetLineWidth(2);
		}
		else {
			ofSetColor(greyScale, 80);
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
			ofSetColor(greyScale, 180);
			ofSetLineWidth(2);
		}
		else {
			ofSetColor(greyScale, 80);
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
			end.y = start.y - length;
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
			end.y = start.y - length;
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
			end.y = start.y - length;
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
			end.x = start.x + length;
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


void ofApp::func01() {
	makeGrid(20);
	for (int i = 0; i < num_walker; i++) {
		walkerFinder(walkers[i].returnLoc());
	}
} 
void ofApp::func02(float _x, float _y, float _dThickness) {
	float x = _x;
	float y = _y;
	float dThickness = _dThickness;
	float minThickness = 1;
	int num = 10;
	int dist = 20;
	float H;
	float preH;
	float preY, curY;

	for (int i = 0; i < num; i++) {
		ofSetColor(255, 0, 0);
		H = 100 - dThickness * 5;
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
void ofApp::walkerFinder(ofPoint _pos) {

	ofPoint origin = _pos;
	int size = 30;
	ofPoint corner;
	corner.x = origin.x - size / 2;
	corner.y = origin.y - size / 2;
	ofNoFill();
	ofSetLineWidth(2);
	ofSetColor(255, 0, 0);
	ofRect(corner, size, size);
	ofPoint s, e;
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


	string posToPrint = "X:" + ofToString(_pos.x) + " , " +  "Y:" + ofToString(_pos.y);
	ofRectangle bb = font.getStringBoundingBox(posToPrint, 0, 0);
	font.drawString(posToPrint, _pos.x+size/2+fontSize,_pos.y+size/2+fontSize);
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
void ofApp::func06(float _size,float _angle) {
	ofPoint posCorner;
	posCorner = ofPoint(-_size / 2, -_size / 2);
	ofSetBackgroundColor(170);
	ofSetColor(0);
	ofFill();
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofRotate(_angle);
	ofRect(posCorner.x, posCorner.y, _size, _size);
	//func08(func08Angle, _angle);
	ofSetColor(255, 0, 0);
	ofNoFill();
	ofPopMatrix();
	ofNoFill();
}
void ofApp::func07() {
	int size = 6;
	int margin = size + 2;
	int row = ofGetHeight() / (size + margin) + 1;
	int col = ofGetWidth() / (size + margin) + 1;
	int powerR = 60;
	int greyScale = 180; //30


	for (int rowCounter = 0; rowCounter < row; rowCounter++) {
		for (int colCounter = 0; colCounter < col; colCounter++) {
			int changedSize = size;
			int lineThickness = 1;
			int lineAlpha = 50;
			ofPoint posCenter = ofPoint(rowCounter * (size + margin), colCounter * (size + margin));
			for (int i = 0; i < num_walker; i++) {
				float dist = (posCenter - walkers[i].returnLoc()).length();
				dist = powerR - dist;
				if (dist < powerR) {
					
					changedSize += dist/10;
					lineThickness = 3;
					lineAlpha = 220;
				}
			}
			ofSetColor(greyScale, lineAlpha);
			ofSetLineWidth(lineThickness);
			ofNoFill();
			ofRect(posCenter.x-changedSize/2,posCenter.y -changedSize/2, changedSize, changedSize);
			
		}
	}
}

void ofApp::func08(float _threeDModel_angle, float _angle) {
	float scale = 3;
	float angle = _threeDModel_angle;
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofRotate(_angle);
	ofRotateX(angle/2);
	ofRotateY(angle/2);
	ofRotateZ(-angle/5);
	ofSetColor(255, 0, 0);
	ofNoFill();
	threeDModel.setScale(scale,scale,scale);
	threeDModel.drawWireframe();
	ofPopMatrix();
}
void ofApp::func09() {
	int size = 6;
	int dist = size * 3;
	for (int _y = 0; _y < ofGetHeight(); _y+= dist){
		for (int _x = 0; _x < ofGetWidth(); _x+= dist) {
			ofPoint _center = ofPoint(_x, _y);
			ofDrawCircle(_center, size);


		}
}


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
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}