#include "ofApp.h"



void ofApp::initSetting() {
	ofSetFrameRate(sec);
	ofSetBackgroundColor(0);
	ofEnableAntiAliasing();
	//ofEnableAlphaBlending();
	//ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnableSmoothing();
	ofSetCircleResolution(64);

	id_init = 0;
}



void ofApp::initParam() {
	//init once
	if (id_init == 0) {
		//walker
		boolWalkerDisplay = false;

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
		fbo01.allocate(ofGetWidth(), ofGetHeight() / 10,GL_RGB);

		id_init = 1;
	}
	//-----------------------------------
	//-----------------------------------
	//-----------------------------------	
	//init when called
	

	//func param
	boolWalkerFinder = false;
	boolFunc04 = false;
	boolFunc06 = false;
	boolFunc07 = false;
	boolFunc11 = false;

	func01T = 0;
	func06T = 0;
	func06Angle = 0;
	func08Angle = 0;
	func09T = 0;
	
	
	//init particle
	int _seed = ofRandom(0, 100);
	for (int i = 0; i < num_particle; i++) {
		ofPoint tmpPos = ofPoint(ofRandom(-ofGetWidth()*0.5, ofGetWidth()*1.5), ofRandom(-ofGetHeight()*0.5, ofGetHeight()*1.5));
		particles[i] = Particle(tmpPos);
		particles[i].incr_locus = _seed;
	}
	ringCenter_particleArray.clear();


	//default
	sec = 30; // frame to second
	oneCool = 60;
	currentFrame = 0;
	ofSetBackgroundAuto(true);
}


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
	ofClear(0);
	ofFill();
	ofSetColor(0);
	ofRect(0, 0, fbo01.getWidth(), fbo01.getHeight());
	ofNoFill();
	ofSetColor(255,255,255);
	func08(func08Angle, func06Angle);
	func08Angle++;
	fbo01.end();

	//

}

//--------------------------------------------------------------
void ofApp::draw() {
	update();
	//-----------------------------------
	//-----------------------------------
	//-----------------------------------	
	//default (start)
	ofSetBackgroundColor(0);
	for (int i = 0; i < walkerArray.size(); i++) {
		walkerArray[i].readyToShow();
	}

	//-----------------------------------
	//-----------------------------------
	//-----------------------------------



	//timeline
	
	boolFunc11 = funcDo(boolFunc11, 0, oneCool, 0, 20, currentFrame);
	if (boolFunc11 == true){
		func11();
	}
	boolFunc09 = funcDo(boolFunc09, 0, oneCool, 32, 36, currentFrame);
	if (boolFunc09 == true) {
		func09(func09T);
		func09T += 0.09;
	}
	boolFunc06 = funcDo(boolFunc06, 0, oneCool, 20, 28, currentFrame);
	if (boolFunc06 == true) {
		func06T += 0.01;
		float func06Size = ofGetWidth() + ofGetWidth() / 2 * -sin(func06T);
		if (func06Size < ofGetWidth() / 4 * 3) {
			//func06Angle += 0.1;
		}
		func06(func06Size, func06Angle);
	}
	boolFbo01 = funcDo(boolFbo01, 0, oneCool, 28, 32, currentFrame);
	if (boolFbo01 == true) {
		for (int i = 0; fbo01.getHeight() * i < ofGetHeight(); i++) {
			fbo01.draw(0, fbo01.getHeight() * i, fbo01.getWidth(), fbo01.getHeight());
		}
		ofSetColor(150, 10, 10);
		func01(func01T);
		float inc = ofGetWidth() / (3 * sec);
		func01T+= inc;
	}
	boolFunc04 = funcDo(boolFunc04, 0, oneCool, 30, 31, currentFrame);
	if (boolFunc04 == true) {
		func04();
	}
	boolWalkerFinder = funcDo(boolWalkerFinder, 0, oneCool, 41, 44, currentFrame);
	if (boolWalkerFinder == true) {
		ofBackground(0);
		makeGrid();
		makeDimension();
		for (int i = 0; i < walkerArray.size(); i++) {
			walkerFinder(walkerArray[i].returnPos());
		}
	}
	boolFunc07 = funcDo(boolFunc07, 0, oneCool, 36, 40, currentFrame);
	if (boolFunc07 == true) {
		func07();
	}
	
	boolFunc10 = funcDo(boolFunc10, 0, oneCool, 44,60, currentFrame);
	if (boolFunc10 == true) {
		func10();
	}
	
	


	//-----------------------------------
	//-----------------------------------
	//-----------------------------------
	//walkers
	if (boolWalkerDisplay == true) {
		for (int i = 0; i < walkerArray.size(); i++) {
			walkerArray[i].show();
		}
	}

	//default (end)

	currentFrame++;
	if (currentFrame > oneCool * sec) {
		initParam();
	}

	ui();
	//-----------------------------------
	//-----------------------------------
	//-----------------------------------
}








//--------------------------------------------------------------
//--------------------------------------------------------------
//my essential defs

bool ofApp::funcDo(bool _bool, float _origin, float _period, float _ss, float _es, int _currentFrame) {
	bool _doOrNot = _bool;
	int _periodFrame = _currentFrame % int((_period * sec));
	if ( _periodFrame > (_ss*sec) &&  _periodFrame < (_es*sec)){
		_doOrNot = true;
	}
	else { 
		_doOrNot = false;
	}
	return _doOrNot;
}





//--------------------------------------------------------------
//--------------------------------------------------------------
//my defs




void ofApp::func01(float _t) {
	//ofBackground(0);
	bool _vert = false;
	float _x = _t;
	float _y = _t;
	ofPoint _s, _e;
	if (_vert == true) {
		_s = ofPoint(0, _y);
		_e = ofPoint(ofGetWidth(), _y);
	}
	else {
		_s = ofPoint(_x, 0);
		_e = ofPoint(_x, ofGetHeight());
	}
	ofNoFill();
	ofSetLineWidth(1);
	ofDrawLine(_s, _e);


} 
void ofApp::func02(float _x, float _y, float _dThickness) {
	ofBackground(0);
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
void ofApp::func04() {
	ofBackground(0);
}

void ofApp::func05(ofPoint _pos) {
	ofBackground(0);
	ofPoint pos = _pos;
	pos.x += 10;
	pos.y = 0;
	ofSetColor(0, 50, 50);
	ofRect(pos.x, pos.y, 5, 5);
}
void ofApp::func06(float _size,float _angle) {
	ofBackground(0);
	ofSetBackgroundColor(0);
	ofSetColor(255);
	ofFill();
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofRotate(_angle);
	ofPoint posCorner = ofPoint(-_size / 2, -_size / 2);
	ofRect(posCorner.x, posCorner.y, _size, _size);
	ofSetColor(255, 0, 0);
	ofNoFill();
	ofPopMatrix();
	ofNoFill();
}

void ofApp::func07() {
	ofBackground(0);
	int _size = 8;
	int _margin = _size * 5;
	int _rowN = ofGetHeight() / (_size + _margin) + 1;
	int _colN = ofGetWidth() / (_size + _margin) + 1;
	int _powerR = _size * 8;
	ofSetBackgroundColor(0);
	int _greyScale = 255; //30
	int _lineThickness = 1;

	for (int row = 0; row < _rowN; row++) {
		for (int col = 0; col < _colN; col++) {

			int _lineThickness = 1;

			ofPoint _posCenter = ofPoint(row * (_size + _margin), col * (_size + _margin));
			ofNoFill();
			float _alpha = 0;
			for (int i = 0; i < walkerArray.size(); i++) {
				float _dist = (_posCenter - walkerArray[i].returnPos()).length();
				if (_dist < _powerR) {
					//ofFill();
				}
				float _tmp = ofMap(abs(_dist), 0, ofGetWidth() / 3, 250, 0);
				if (_tmp < 0) {
					_tmp = 0;
				}
				if (_tmp > 250) {
					_tmp = 250;
				}
				_alpha += _tmp;
			}
			ofSetColor(_greyScale, _alpha);
			ofSetLineWidth(_lineThickness);
			ofRect(_posCenter.x - _size, _posCenter.y - _size / 2, _size, _size);

		}
	}
}

void ofApp::func08(float _threeDModel_angle, float _angle) {
	ofBackground(0);
	float scale = 3;
	float angle = _threeDModel_angle;
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofRotate(_angle);
	ofRotateX(angle/2);
	ofRotateY(angle/2);
	ofRotateZ(-angle/5);
	ofNoFill();
	threeDModel.setScale(scale,scale,scale);
	threeDModel.drawWireframe();
	ofPopMatrix();
}
void ofApp::func09(float _t) {
	ofBackground(0);
	int _size = 8;
	int _colN = 20;
	int _rowN = 20;
	float _distY = ofGetHeight() / (_rowN+1);
	float _distX = ofGetWidth() / (_colN+1);
	ofSetBackgroundColor(0);
	ofSetColor(255);
	ofFill();
	for (int row = 0; row < _rowN; row++) {
		for (int col = 0; col < _colN; col++) {
			ofPoint _center = ofPoint((col+1) * _distX, (row+1) * _distY);
			ofDrawCircle(_center, _size/2+_size/2*sin(_t));
		}
		_t+=0.15;
	}
	ofNoFill();
}




void ofApp:: func10() {
	ofBackground(0);
	float _r = 50;
	int _maxNum = 10;


	
	if (ringCenter_particleArray.size() == 0) {
		//ringCenter_particleArray.clear();
		for (int i = 0; i < walkerArray.size(); i++) {
			ofPoint _initialCenter = walkerArray[i].returnPos();
			Particle _p = Particle(_initialCenter);
			ringCenter_particleArray.push_back(_p);
		}
	}
	if (ringCenter_particleArray.size() < walkerArray.size()) {
			ofPoint _initialCenter = walkerArray[walkerArray.size()-1].returnPos();
			Particle _p = Particle(_initialCenter);
			ringCenter_particleArray.push_back(_p);
	}


	/*
	if (ringCenter_particleArray.size() < walkerArray.size()) {
		//ringCenter_particleArray.clear();
		for (int i = 0; i < walkerArray.size(); i++) {
			ofPoint _initialCenter = walkerArray[i].returnPos();
			Particle _p = Particle(_initialCenter);
			ringCenter_particleArray.push_back(_p);
		}
	}*/




	while(ringCenter_particleArray.size() > walkerArray.size()) {
		ringCenter_particleArray.erase(ringCenter_particleArray.begin());
	}
	for(int i=0; i<ringCenter_particleArray.size();i++){
		ofPoint _posToAdd = walkerArray[i].returnPos();
		ringCenter_particleArray[i].updateArray_ring(_posToAdd);
		if (ringCenter_particleArray.size() > _maxNum) {
			ringCenter_particleArray.erase(ringCenter_particleArray.begin());
		}
		ofSetColor(255);
		ofSetLineWidth(1);
		ofNoFill();
		ringCenter_particleArray[i].putInside();
		ringCenter_particleArray[i].show_ring();
		ofNoFill();
	}	
}

void ofApp::func11() {
	ofSetBackgroundAuto(false);
	ofSetColor(0,20);
	ofFill();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	for (int i = 0; i < num_particle; i++) {
		ofFill();
		ofSetColor(255);
		particles[i].readyToShow_locus();
			particles[i].readyToShow_force(ofPoint(mouseX,mouseY));
		//particles[i].show_locus();
		ofNoFill();
	}
}












//--------------------------------------------------------------
//--------------------------------------------------------------
//my defs- base


void ofApp::makeGrid() {
	int _size = 20;
	int _row = ofGetHeight() / _size + 1;
	int _col = ofGetWidth() / _size + 1;
	int _thickLine_per = 10;

	int _counter_y = 0;
	int _counter_x = 0;
	int _greyScale = 130;

	for (int y = 0; y < _row; y++) {
		if (_counter_y % _thickLine_per == 0) {
			ofSetColor(_greyScale, 180);
			ofSetLineWidth(2);
		}
		else {
			ofSetColor(_greyScale, 80);
			ofSetLineWidth(1);
		}
		ofPoint _s = ofPoint(0, y * _size);
		ofPoint _e = ofPoint(ofGetWidth(), y * _size);
		ofDrawLine(_s, _e);
		_counter_y++;
	}
	for (int x = 0; x < _col; x++) {
		if (_counter_x % _thickLine_per == 0) {
			ofSetColor(_greyScale, 180);
			ofSetLineWidth(2);
		}
		else {
			ofSetColor(_greyScale, 80);
			ofSetLineWidth(1);
		}
		ofPoint _s = ofPoint(x*_size, 0);
		ofPoint _e = ofPoint(x*_size,ofGetHeight());
		ofDrawLine(_s, _e);
		_counter_x++;
	}
}
void ofApp::makeDimension() {
	//local param

	int _dim_large = 100;
	int _dim_middle = 50;
	int _dim_small = 5;

	int _length_large = 16;
	int _length_middle = 10;
	int _length_small = 5;


	//vert
	for (int x = 0; x < ofGetWidth(); x++) {
		int _length = 0;
		if (x % _dim_large == 0) {
			int _length = _length_large;
			ofSetLineWidth(1);
			ofSetColor(255);
		}
		else if (x % _dim_middle == 0) {
			_length = _length_middle;
			ofSetLineWidth(1);
			ofSetColor(255);
		}
		else if (x % _dim_small == 0) {
			_length = _length_small;
			ofSetColor(255);
			ofSetLineWidth(0.25);
		}
		ofPoint _start = ofPoint(x, 0);
		ofPoint _end = ofPoint(x, _start.y + _length);
		ofDrawLine(_start, _end);

		_start = ofPoint(x, ofGetHeight());
		_end = ofPoint(x, _start.y - _length);

	}


	//hori
	for (int y = 0; y < ofGetHeight(); y++) {
		int _length = 0;
		if (y % _dim_large == 0) {
			_length = _length_large;
			ofSetLineWidth(1);
			ofSetColor(255);

		}
		else if (y % _dim_middle == 0) {
			_length = _length_middle;
			ofSetLineWidth(1);
			ofSetColor(255);

		}
		else if (y % _dim_small == 0) {
			_length = _length_small;
			ofSetColor(255);
			ofSetLineWidth(0.25);
		}
		ofPoint _start = ofPoint(0, y);
		ofPoint _end = ofPoint(_start.x + _length, _start.y);
		ofDrawLine(_start, _end);

		_start = ofPoint(ofGetWidth(), y);
		_end = ofPoint(_start.x - _length, _start.y);
		ofDrawLine(_start, _end);
	}
}
void ofApp::walkerFinder(ofPoint _pos) {
	ofPoint _origin = _pos;
	int _size = 30;
	ofPoint _corner = ofPoint(_origin.x - _size / 2, _origin.y - _size / 2);
	ofNoFill();
	ofSetLineWidth(2);
	ofSetColor(255, 0, 0);
	ofRect(_corner, _size, _size);
	ofPoint _s, _e;
	_s = ofPoint(0, _origin.y);
	_e = ofPoint(ofGetWidth(), _origin.y);
	ofDrawLine(_s, _e);
	_s = ofPoint(_origin.x, 0);
	_e = ofPoint(_origin.x, ofGetHeight());
	ofDrawLine(_s, _e);

	string _posToPrint = "X:" + ofToString(_pos.x) + " , " + "Y:" + ofToString(_pos.y);
	ofRectangle _bb = font.getStringBoundingBox(_posToPrint, 0, 0);
	font.drawString(_posToPrint, _pos.x + _size / 2 + fontSize, _pos.y + _size / 2 + fontSize);
}
void ofApp::ui() {

	ofPoint _basePos = ofPoint(50, 50);
	//fps
	string fpsToPrint = ofToString(ofGetFrameRate());
	ofFill();
	ofSetColor(255);
	ofRectangle bbofFPS = font.getStringBoundingBox(fpsToPrint, _basePos.x, _basePos.y);
	ofRect(bbofFPS);
	ofNoFill();
	ofSetColor(255, 0, 0);
	font.drawString(fpsToPrint, _basePos.x, _basePos.y);

	//currentFrame
	fpsToPrint = ofToString(currentFrame / sec);
	ofFill();
	ofSetColor(255);
	bbofFPS = font.getStringBoundingBox(fpsToPrint, _basePos.x, _basePos.y + fontSize);
	ofRect(bbofFPS);
	ofNoFill();
	ofSetColor(255, 0, 0);
	font.drawString(fpsToPrint, _basePos.x, _basePos.y + fontSize);

	//scene

	//dimension
	//makeDimension();
}






























//--------------------------------------------------------------
void ofApp::keyPressed(int _key) {
	if (_key == 'r') {
		setup();
	}
	if (_key == 's') {
		int id = 0;
		if (boolWalkerDisplay == false && id == 0) {
			boolWalkerDisplay = true;
			id = 1;
		}
		if (boolWalkerDisplay == true && id == 0) {
			boolWalkerDisplay = false;
			id = 1;
		}
	}
	if (_key == 'i') {
		ofPoint _originalPos = ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
		Walker _w = Walker(_originalPos);
		walkerArray.push_back(_w); //_originalPos	
	}
	if (_key == 'd') {
		if (walkerArray.size() > 0) {
			walkerArray.erase(walkerArray.begin());
		}
	}

	if (_key == 'c') {
		float _n = ofRandom(50);
		for (int i = 0; i < num_particle; i++) {
			particles[i].incr_locus =_n;
		}	
	}
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