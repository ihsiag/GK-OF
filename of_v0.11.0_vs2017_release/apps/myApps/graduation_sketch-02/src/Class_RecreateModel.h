#pragma once

#include "ofMain.h"
#include "ofApp.h"


class Class_RecreateModel {
public:
	//using Ptr = shared_ptr<Class_Analysis>;
	vector<glm::vec3> arrPos;
	ofMesh* mesh;
	ofEasyCam* ezCam;

	Class_RecreateModel() {

	}

	void setup(ofMesh* _mesh, const vector<glm::vec3>& _resultArr, ofEasyCam* _cam) {
		mesh = _mesh;
		arrPos = _resultArr;
		ezCam = _cam;
	}


	void run() {
		std::cout <<"yeah"<< std::endl;
		createMesh();
		display();
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
		int cols = 20;
		int rows = 20;
		int size = 8;
		int count = 0;
		for (int col = 0; col < cols; col++) {
			for (int row = 0; row < rows; row++) {
				float positionZ = arrPos[count + 300].y * 0.8;
				std::cout << positionZ << std::endl;
				positionZ += ofMap(ofNoise(float(col) / 2, float(row) / 2), 0, 1, 0, 10);
				std::cout << "+noise" << positionZ << std::endl;
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
	}
};