#pragma once

#include "ofMain.h"
#include "ofApp.h"

#define M_PI 3.141592


//====================================================================================================================================
//====================================================================================================================================
//====================================================================================================================================
class Class_Buckling{
private:

public:
	ofMesh* mesh;
	ofEasyCam* ezCam;

	Class_Buckling() {
	};
	~Class_Buckling() {};
	
	void setup(ofMesh* _mesh, ofEasyCam* _ezCam) {
		mesh = _mesh;
		ezCam = _ezCam;

	};
	void run() {
		update();
		display();
	};
	void update() {
	};
	void display() {

	};
};

class Class_Mover {
private:

public:
	void setup();
	void run() {
		update();
		display();
	};
	void update();
	void display();
};

class Class_Spring {
private:

public:
	void setup();
	void run() {
		update();
		display();
	};
	void update();
	void display();
};
