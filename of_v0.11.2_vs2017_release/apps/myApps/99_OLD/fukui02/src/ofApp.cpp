#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	initSetting();
	initParam();
}

//--------------------------------------------------------------
void ofApp::update() {
	//write about fbo
	
	//fbo01
	fbo01.begin();
	ofClear(0);
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
	/*will make scene func*/
	func07();
	
	/*
	if (func06Size > ofGetWidth()/2) {
		func06(func06Size,func06Angle);
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
	*/

	func08Angle += 1;

	
	
	/*will make scanner func*/
	Y += 4;
	deltaThickness *= 1.008;
	//deltaThickness += 0.1;
	if (X > ofGetWidth()) {
		X = 0;
	}
	if (Y > ofGetHeight() * 2) {
		Y = 0;
		deltaThickness = 5;
	}
	 func02(X, Y, deltaThickness);
	

	 for (int i = 0; i < num_walker; i++) {
		 walkers[i].run();
	 }
	/*will make frame func*/
	if (tmpFrame > 240) {
		makeGrid(20);
		for (int i = 0; i < num_walker; i++) {
			func03(walkers[i].returnLoc());
		}
	}
	if (tmpFrame > 300) {
		tmpFrame = 0;
	}
	
	//walkers
	for (int i = 0; i < num_walker; i++) {
		walkers[i].display();
	}

	fbo01.draw(0, ofGetHeight()/2- fbo01.getHeight()/2, fbo01.getWidth(), fbo01.getHeight());

	//default
	tmpFrame++;
	currentFrame++;
	ui();



}
//--------------------------------------------------------------
//--------------------------------------------------------------
//my essential defs

void ofApp::initSetting() {
	ofSetFrameRate(30);
	ofSetBackgroundColor(0);
	ofEnableAntiAliasing();
	ofEnableAlphaBlending();
	//ofEnableBlendMode();
	ofEnableSmoothing();
	ofSetBackgroundAuto(true);
	ofSetCurveResolution(30);
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
	X = 0;
	Y = 0;
	deltaThickness = 5;
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
	tmpFrame = 0;
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


void ofApp::func01(float _x, float _y, float _dThickness) {
	float x = _x;
	float y = _y;
	float dThickness = _dThickness;
	float minThickness = 1;
	int num = 20;
	int dist = 20;
	float H;
	float preH;
	float preY, curY;
	ofFill();
	ofSetColor(255, 0, 0);
	for (int i = 0; i < num; i++) {
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
	ofNoFill();
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
void ofApp::func03(ofPoint _pos) {

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