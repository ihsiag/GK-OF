#pragma once

#include "ofMain.h"
#include "ofApp.h"

#define M_PI 3.141592


//====================================================================================================================================
//====================================================================================================================================
//====================================================================================================================================
class Class_DelaCircle{
private:
	float triR;

public:
	vector<glm::vec2> triVertices;
	glm::vec2 triCenter;
	int shareside[3]; //01:0 12:1 20:2
	int sharepoint[3];

	Class_DelaCircle() {
		triVertices.reserve(3);
	};
	~Class_DelaCircle() {};
	
	void setup(vector<glm::vec2> _triVertices) {

		//外接円のパラメータの計算(３つの点から中心を求める)
		triVertices = _triVertices;
		double c = 2 * ((triVertices[1].x - triVertices[0].x) * (triVertices[2].y - triVertices[0].y) - (triVertices[1].y - triVertices[0].y) * (triVertices[2].x - triVertices[0].x));
		double x1, x2, y1, y2, xy1, xy2;
		x1 = (triVertices[2].y - triVertices[0].y);
		x2 = (triVertices[0].y - triVertices[1].y);
		y1 = (triVertices[0].x - triVertices[2].x);
		y2 = (triVertices[1].x - triVertices[0].x);
		xy1 = (pow(triVertices[1].x, 2) - pow(triVertices[0].x, 2) + pow(triVertices[1].y, 2) - pow(triVertices[0].y, 2));
		xy2 = (pow(triVertices[2].x, 2) - pow(triVertices[0].x, 2) + pow(triVertices[2].y, 2) - pow(triVertices[0].y, 2));
		
		triCenter = glm::vec2((x1 * xy1 + x2 * xy2) / c, (y1 * xy1 + y2 * xy2) / c);
		triR = glm::distance(triCenter,triVertices[0]);

		shareside[0] = 0;
		shareside[1] = 0;
		shareside[2] = 0;
	};
	void run() {
		update();
		display();
	};
	void update() {
	};
	void display() {
		drawTriangle();
		drawCircle();
		drawCenter();
	};

	void drawCenter() {
		ofFill();
		glColor3f(1, 0, 0);
		ofDrawCircle(triCenter, 2);
	};
	
	void drawCircle() {
		glLineWidth(2);
		ofNoFill();
		glColor3f(1, 1, 1);
		ofDrawCircle(triCenter, triR);
	};
	
	void drawTriangle() {
		ofMesh mesh;
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		mesh.addVertex(ofPoint(triVertices[0]));
		mesh.addVertex(ofPoint(triVertices[1]));
		mesh.addVertex(ofPoint(triVertices[2]));
		//mesh.addVertex(ofPoint(triVertices[0])); //2
		
		//glColor3f(1, 1, 1);
		//mesh.draw();
		glColor3f(0, 0, 1);
		glLineWidth(2);
		mesh.drawWireframe();
	};
	
	bool check(vector<shared_ptr<ofxBox2dCircle>>* _circles) {
		bool result = false;
		for (int i = 0; i < _circles->size(); i++){
			float dist = glm::distance(triCenter,glm::vec2(_circles->at(i)->getPosition().x, _circles->at(i)->getPosition().y));
			if (dist < triR-0.01){
				return true;
				break;
			}
		}
		return false;
	};
};



//====================================================================================================================================
//====================================================================================================================================
//====================================================================================================================================
#pragma mark Class_Delaunay
class Class_Delaunay {
public:
	ofEasyCam* ezCam;
	bool bStageEnd;
	vector<shared_ptr<ofxBox2dCircle>> *circles;
	vector<Class_DelaCircle> triCircles;

	Class_Delaunay() {}
	~Class_Delaunay() {}

	void setup(vector<shared_ptr<ofxBox2dCircle>>* _circles, ofEasyCam* _ezCam) {
		ofSetCircleResolution(36);
		ezCam = _ezCam;
		circles = _circles;
		//free
		vector<Class_DelaCircle>().swap(triCircles);
	}
	bool run() {
		update();
		ezCam->begin();
		display();
		ezCam->end();
		return bStageEnd;
	}

	void update() {
		if (circles->size() > 2) {
			vector<Class_DelaCircle>().swap(triCircles);
			getTriCircles(&triCircles);
		}
	}

	void display() {		
		for (int i = 0; i < triCircles.size(); i++){
			triCircles[i].display();
		}
	};

	void getTriCircles(vector<Class_DelaCircle> *triCircles) {
		//外接円の中に他のpointが存在しないpointの組み合わせを全探索
		for (int i = 0; i < circles->size() - 2; i++) {
			for (int j = i + 1; j < circles->size() - 1; j++) {
				for (int k = j + 1; k < circles->size(); k++) {
					vector<glm::vec2> _triVertices;
					_triVertices.push_back(glm::vec2(circles->at(i)->getPosition().x, circles->at(i)->getPosition().y));
					_triVertices.push_back(glm::vec2(circles->at(j)->getPosition().x, circles->at(j)->getPosition().y));
					_triVertices.push_back(glm::vec2(circles->at(k)->getPosition().x, circles->at(k)->getPosition().y));
					Class_DelaCircle _triCircle;
					_triCircle.setup(_triVertices);
					//外接円内に他のpointがないか確認
					if (!_triCircle.check(circles)) {
						triCircles->push_back(_triCircle);
					}
				}
			}
		}
	};
};