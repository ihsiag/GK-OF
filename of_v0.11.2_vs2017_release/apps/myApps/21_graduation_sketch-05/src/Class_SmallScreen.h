#pragma once
#include "ofApp.h"
#include "ofxGKUtils.h"
#include "ofEasyCam.h"

class Class_SmallScreen {
public:
	Class_SmallScreen() {}
	~Class_SmallScreen() {}
	ofxGKUtils gk;

	glm::vec2 pos;
	glm::vec2 size;
	ofMesh* mesh;
	string* meshName;

	glm::vec2 mouseOnScreenPlane;
	glm::vec2 rotationAngle;

	void setup(const glm::vec2& _pos, const glm::vec2& _size, ofMesh* _mesh, string* _meshName) {
		pos = _pos;
		size = _size;
		mesh = _mesh;
		meshName = _meshName;
		//gk.setCam(&classCam);
		//resetCamera();
	}

	void setup(const glm::vec2& _pos, const glm::vec2& _size) {
		pos = _pos;
		size = _size;
		mesh = nullptr;
		meshName = nullptr;
		//gk.setCam(&classCam);
		//resetCamera();
	}
	
	void run() {
		update();
		display();
	}
	
	void update() {
		mouseOnScreenPlane = getMouseOnScreenPlane();
		rotationAngle = getRotationAngleFromMouseOnScreenPlane();
	}
	
	void display() {
		if (IsMouseOn()) {
			glColor4f(0.95,0.95,0.96,1);
		}
		else {		
			ofSetColor(10);
		}
		ofFill();
		ofPushMatrix();
		ofTranslate(pos);
		ofDrawRectangle(0,0, size.x, size.y);
		ofPushMatrix();
		ofTranslate(size / 2);
		glColor3f(1, 0, 0);
		gk.drawCross(0, 0, 15);				
		if (mesh) {
			ofRotateX(rotationAngle.y);
			ofRotateY(rotationAngle.x);
			gk.draw3DAxis(size.y*0.8,2,0.3);
			glColor3f(0.8,0.8,0.8);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			glLineWidth(0.5);
			mesh->drawFaces();
			glColor4f(0.6, 0.5, 0.5,1);
			mesh->drawWireframe();
			glPointSize(0.2);
			glDisable(GL_CULL_FACE);
		}
		stringstream _ss;
		_ss << "fileInfo" << endl;
		_ss << *meshName << endl;
		ofPopMatrix();
		gk.drawInfo(_ss, glm::vec2(size.x/2,size.y-25));
		ofPopMatrix();
		
	}

	bool IsMouseOn() {
		bool _b = false;
		if (pos.x < ofGetMouseX() && ofGetMouseX()< pos.x + size.x) {
			if (pos.y < ofGetMouseY() && ofGetMouseY()< pos.y + size.y) {
				_b = true;
			}
		}
		return _b;
	}

	glm::vec2 getMouseOnScreenPlane() {
		if (IsMouseOn()) {
			return glm::vec2(ofGetMouseX() - pos.x, ofGetMouseY() - pos.y);
		}
		else {
			return size / 2;
		}
	}

	glm::vec2 getRotationAngleFromMouseOnScreenPlane() {
		float angleX = ofMap(mouseOnScreenPlane.x, 0, size.x, -180, 180);
		float angleY = ofMap(mouseOnScreenPlane.y, size.y, 0, -180, 180);
		return glm::vec2(angleX, angleY);
	}

	void onWindowResized(const glm::vec2& _pos, const glm::vec2& _size) {
		pos = _pos;
		size = _size;
	}
};


