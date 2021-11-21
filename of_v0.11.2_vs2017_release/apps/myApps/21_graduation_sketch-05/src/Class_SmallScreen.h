#pragma once
#include "ofApp.h"
#include "ofxGKUtils.h"

class Class_SmallScreen {
public:
	Class_SmallScreen() {}
	~Class_SmallScreen() {}
	ofxGKUtils gk;

	ofEasyCam* cam;
	glm::vec2 pos;
	glm::vec2 size;
	ofMesh* mesh;

	bool bSelected;

	void setup(const glm::vec2& _pos, const glm::vec2& _size, ofMesh* _mesh,ofEasyCam* _cam) {
		pos = _pos;
		size = _size;
		mesh = _mesh;
		cam = _cam;
		bSelected = false;
	}

	void setup(const glm::vec2& _pos, const glm::vec2& _size,ofEasyCam* _cam) {
		pos = _pos;
		size = _size;
		mesh = nullptr;
		cam = _cam;
		bSelected = false;
	}

	void resize(const glm::vec2& _pos, const glm::vec2& _size) {
		pos = _pos;
		size = _size;
	}
	void run() {}
	void update() {
		glColor3f(0, 0, 0);
		glPointSize(2);
		glLineWidth(1);
	}
	void display() {
		if (bSelected) {
			glColor3f(0.5, 0.5, 0);
		}
		else {		
			ofSetColor(0);
		}
		if (mesh) {
			glColor3f(0, 0, 0);
		}
		else {
			glColor3f(1, 1, 1);
		}
		ofFill();
		ofPushMatrix();
		ofTranslate(pos);
		ofDrawRectangle(0,0, size.x, size.y);
		//ofTranslate(size / 2);
		glColor3f(1, 0, 0);
		gk.drawCross(0, 0, 15);
		gk.draw3DAxis();
				
		if (mesh) {						
			glColor3f(0.8, 0.8, 0.8);
			mesh->drawFaces();
			ofNoFill();
			glColor3f(0.5, 0.5, 0.5);
			mesh->drawWireframe();
		}
		
		ofPopMatrix();
	}
};


