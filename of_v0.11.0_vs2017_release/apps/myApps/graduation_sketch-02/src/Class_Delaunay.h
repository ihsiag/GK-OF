#pragma once

#include "ofMain.h"
#include "ofApp.h"


class Class_Delaunay {
public:
	
	bool bStageEnd;
	
	vector<glm::vec3>* vertexArr;

	Class_Delaunay() {
	}

	~Class_Delaunay() {
	}

	void setup(vector<glm::vec3>* _vertexArr) {
		vertexArr = _vertexArr;
	}
	bool run() {
		update();
		display();
		return bStageEnd;
	}

	void update() {
		makeCircumcircle();

	}

	void display() {
		glClearColor(1, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void makeCircumcircle(){
		//外接円のパラメータの計算
		/*
		double c = 2 * ((elements[1]->pos.x - elements[0]->pos.x) * (elements[2]->pos.y - elements[0]->pos.y) - (elements[1]->pos.y - elements[0]->pos.y) * (elements[2]->pos.x - elements[0]->pos.x));
		double x1, x2, y1, y2, xy1, xy2;
		x1 = (elements[2]->pos.y - elements[0]->pos.y);
		x2 = (elements[0]->pos.y - elements[1]->pos.y);
		y1 = (elements[0]->pos.x - elements[2]->pos.x);
		y2 = (elements[1]->pos.x - elements[0]->pos.x);
		xy1 = (pow(elements[1]->pos.x, 2) - pow(elements[0]->pos.x, 2) + pow(elements[1]->pos.y, 2) - pow(elements[0]->pos.y, 2));
		xy2 = (pow(elements[2]->pos.x, 2) - pow(elements[0]->pos.x, 2) + pow(elements[2]->pos.y, 2) - pow(elements[0]->pos.y, 2));
		center.x = (x1 * xy1 + x2 * xy2) / c;
		center.y = (y1 * xy1 + y2 * xy2) / c;
		radius = ofVec2f(center - elements[0]->pos).length();

		shareside[0] = 0;
		shareside[1] = 0;
		shareside[2] = 0
		*/
	}
};

class Class_DelaPoint {
public:
	glm::vec2 pos;
	Class_DelaPoint() {
	};
	void setup() {
	};
	void run() {
		update();
		display();
	};
	void update() {
	};
	void display() {
	};
	glm::vec2 getPosition() {
		return pos;
	};

};

class Class_DelaTriangle {
public:
	Class_DelaTriangle() {
	};
	void setup() {
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

class Class_DelaCircle{
private:
	float r;

public:
	vector<shared_ptr<Class_DelaPoint>>* elements;
	glm::vec2 center;
	int shareside[3]; //01:0 12:1 20:2
	int sharepoint[3];

	Class_DelaCircle() {
	};
	~Class_DelaCircle() {
	};
	
	void setup(vector<shared_ptr<Class_DelaPoint>>* _elements) {
		//外接円のパラメータの計算
		elements = _elements;
		double c = 2 * ((elements->at(1)->pos.x - elements->at(0)->pos.x) * (elements->at(2)->pos.y - elements->at(0)->pos.y) - (elements->at(1)->pos.y - elements->at(0)->pos.y) * (elements->at(2)->pos.x - elements->at(0)->pos.x));
		double x1, x2, y1, y2, xy1, xy2;
		x1 = (elements->at(2)->pos.y - elements->at(0)->pos.y);
		x2 = (elements->at(0)->pos.y - elements->at(1)->pos.y);
		y1 = (elements->at(0)->pos.x - elements->at(2)->pos.x);
		y2 = (elements->at(1)->pos.x - elements->at(0)->pos.x);
		xy1 = (pow(elements->at(1)->pos.x, 2) - pow(elements->at(0)->pos.x, 2) + pow(elements->at(1)->pos.y, 2) - pow(elements->at(0)->pos.y, 2));
		xy2 = (pow(elements->at(2)->pos.x, 2) - pow(elements->at(0)->pos.x, 2) + pow(elements->at(2)->pos.y, 2) - pow(elements->at(0)->pos.y, 2));
		center.x = (x1 * xy1 + x2 * xy2) / c;
		center.y = (y1 * xy1 + y2 * xy2) / c;
		r = ofVec2f(center - elements->at(0)->pos).length();

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
	};
	
	void drawCircle();
	void drawTriangle();
	void drawCenter();
	
	bool check(vector<shared_ptr<Class_DelaPoint>>* _points) {
		bool result = true;
		for (int i = 0; i < _points->size(); i++){
			float length = ofVec2f(center - _points->at(i)->pos).length();
			if (length < r - 0.01){
				result = false;
			}
		}
		return result;
	};
};