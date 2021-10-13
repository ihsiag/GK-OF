#pragma once

#include "ofMain.h"
#include "ofApp.h"


class Class_RecreateModel {
public:
	//using Ptr = shared_ptr<Class_Analysis>;
	vector<glm::vec3>* arrPos;
	ofMesh* mesh;
	ofEasyCam* ezCam;
	bool bFirst, bSecond;

	Class_RecreateModel() {
	}

	~Class_RecreateModel() {
	}

	void setup(ofMesh* _mesh, vector<glm::vec3>* _data, ofEasyCam* _cam) {
		mesh = _mesh;
		arrPos = _data;
		ezCam = _cam;
		bFirst = true;
		bSecond = false;
	}


	void run() {
		if(bFirst)createMesh();
		if(bSecond)display();
	}

	void update() {
	}

	void display() {
		ezCam->begin();
		showMesh();
		ezCam->end();
	}


	void showMesh() {
		glLineWidth(1);
		glColor3f(0.6, 0.6, 0.6);
		mesh->drawWireframe();
		glPointSize(2);
		glColor3f(1, 1, 1);
		mesh->drawVertices();
	}

	void createMesh() {
		int cols = 40;
		int rows = 40;
		int size = 2;
		int count = 0;
		for (int col = 0; col < cols; col++) {
			for (int row = 0; row < rows; row++) {
				float positionZ = arrPos->at(count).y*1.2;
				//positionZ += ofMap(ofNoise(float(col) / 2, float(row) / 2), 0, 1, 0, 10);
				mesh->addVertex(glm::vec3(col * size - cols * size / 2, row * size - rows * size / 2, positionZ));
				count += 1;
			}
		}
		for (int x = 0; x < cols - 1; x++) {
			for (int y = 0; y < rows - 1; y++) {
				mesh->addIndex(x + y * rows);
				mesh->addIndex((x + 1) + y * rows);
				mesh->addIndex(x + (y + 1) * cols);
				mesh->addIndex((x + 1) + y * cols);
				mesh->addIndex((x + 1) + (y + 1) * rows);
				mesh->addIndex(x + (y + 1) * rows);
			}
		}
		bFirst = false;
		bSecond = true;
	}
};