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
		float size = 2;
		int count = 0;
		for (int col = 0; col < cols; col++) {
			for (int row = 0; row < rows; row++) {
				float positionZ = arrPos->at(count).y*0.1;
				glm::vec3 pos = glm::vec3((col * size+ofRandom(-1,1) - cols * size / 2), (row * size+ofRandom(-1,1) - rows * size / 2), positionZ);
				mesh->addVertex(pos);
				count += 1;
			}
		}
		for (int col = 0; col < cols - 1; col++) {
			for (int row = 0; row < rows - 1; row++) {
				mesh->addIndex(col + rows*row);
				mesh->addIndex((col + 1) + rows * row);
				mesh->addIndex(col + rows*(row + 1));
				mesh->addIndex((col + 1) + rows * row);
				mesh->addIndex((col + 1) + rows * (row + 1));
				mesh->addIndex(col +  rows*(row + 1));
			}
		}
		bFirst = false;
		bSecond = true;
	}
};