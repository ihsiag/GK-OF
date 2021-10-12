#pragma once

#include "ofMain.h"
#include "ofApp.h"


class Class_ScanModel {
public:
	ofMesh* mesh;
	ofEasyCam* ezCam;
	int numVertex;
	int indexVertex;
	bool bScanEnd;
	
	Class_ScanModel() {

	}

	void setup(ofMesh* _mesh,ofEasyCam* _ezCam) {
		mesh = _mesh;
		ezCam = _ezCam;
		numVertex = mesh->getNumVertices();
		indexVertex = 0;
		bScanEnd = false;
	}

	bool run() {
		update();
		display();
		return bScanEnd;
	}

	void update() {
		if (indexVertex < numVertex - 1) {
			indexVertex++;
		}
		else {
			bScanEnd = true;
		}
	}

	void display() {
		ezCam->begin();
		showMesh(); //3D
		ezCam->end();
		showNotation(); //2D
		showOneDim(); //2D
	}

	void showMesh() {
		glLineWidth(1);
		glColor3f(0.6, 0.6, 0.6);
		mesh->drawWireframe();
		glPointSize(2);
		glColor3f(1, 1, 1);
		mesh->drawVertices();
	}

	void showNotation() {
		glm::vec3 screenPosVertex = ezCam->worldToScreen(mesh->getVertex(indexVertex));
		glm::vec2 posConsole = glm::vec2(ofGetWidth() * 0.75, ofGetHeight() * 0.25);
		ofNoFill();
		glColor3f(1, 1, 0);
		glLineWidth(2);
		ofDrawCircle(screenPosVertex, 4);

		glColor3f(1, 0, 0);
		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex2f(screenPosVertex.x,screenPosVertex.y);
		glVertex2f(posConsole.x,posConsole.y);
		glEnd();

		ofDrawBitmapStringHighlight(ofToString(indexVertex), posConsole + glm::vec2(0, 10));
		ofDrawBitmapStringHighlight(ofToString(mesh->getVertex(indexVertex)), posConsole + glm::vec2(0, 30));
	}

	void showOneDim() {
		glLineWidth(2);
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		for (int i = 0; i < indexVertex-1; i++) {
			glVertex2f(i, ofGetHeight() / 2 + mesh->getVertex(i).z);
			glVertex2f(i + 1, ofGetHeight() / 2 + mesh->getVertex(i + 1).z);
		}
		glEnd();
	}


};