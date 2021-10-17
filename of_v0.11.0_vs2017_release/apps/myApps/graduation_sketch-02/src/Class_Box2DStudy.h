#pragma once

#include "ofMain.h"
#include "ofApp.h"
#include "ofxBox2d.h"


class Class_Box2dStudy {
public:
	ofEasyCam* ezCam;

	ofxBox2d box2d; //world
	ofxBox2dEdge edge;
	vector<shared_ptr<ofxBox2dCircle>> circles;
	vector<glm::vec3> posArr;

	int elementR = 30;
	int resolution = 60;
	float edgeR = ofGetHeight()/4;

	int count = 0;

	Class_Box2dStudy() {
	}

	~Class_Box2dStudy() {
	}

	void setup(ofEasyCam* _ezCam) {
		ezCam = _ezCam;
		ofSetLogLevel(OF_LOG_NOTICE);

		box2d.init();
		box2d.setGravity(0, 0);
		box2d.setFPS(60.0);
		box2d.registerGrabbing();

		ofPolyline _edgeLine;
		for (int i = 0; i <= resolution; i++) {
			glm::vec2 _center = glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2);
			glm::vec2 _pos = glm::vec2(edgeR * cos(2 * PI / resolution * i), edgeR * sin(2 * PI / resolution * i));
			_edgeLine.addVertex(_pos.x, _pos.y);
		}
		_edgeLine.close();
		edge.addVertexes(_edgeLine);
		edge.create(box2d.getWorld());

		
	}


	void run() {
		update();
		ezCam->begin();
		display();
		ezCam->end();
		showInfo();
	}

	void update() {
		//ofRemove(circles, removeShapeOffScreen);
		//ofRemove(posArr,removeShapeOffScreen);
		int elementN = 43;
		if (count < elementN) {
			addElement(glm::vec2(ofRandom(-1, 1), ofRandom(-1, 1)));
		}
		count++;
		box2d.update();
	}

	void display() {
		if (circles.size() > 0) {
			for (auto& circle : circles) {
				ofFill();
				glLineWidth(1);
				//glColor3f(0.5,0.7,0.9);
				glColor3f(1, 0, 0);
				circle->draw();
			}
		}
		glLineWidth(2);
		glColor3f(1,1,1);
		edge.draw();
	}


	void showMesh() {
	}


	void createMesh() {
		if (posArr.size() > 0) {

		}
	}

	void showInfo() {
		string info = "";
		info += "Total Bodies: " + ofToString(box2d.getBodyCount()) + "\n";
		info += "Total Joints: " + ofToString(box2d.getJointCount()) + "\n\n";
		glColor3f(1, 1, 1);
		ofDrawBitmapString(info, 60, ofGetHeight()*0.25);
	}

	void addElement(const glm::vec2& _pos) {
		if (edge.inside(_pos.x, _pos.y)) {
			auto circle = make_shared<ofxBox2dCircle>();
			circle->setPhysics(3.0, 0.53, 0.1);
			circle->setup(box2d.getWorld(), _pos.x, _pos.y, elementR);
			circles.push_back(circle);
			posArr.push_back((glm::vec3(circle->getPosition().x, circle->getPosition().y,0)));
		}
	}

	static bool removeShapeOffScreen(shared_ptr<ofxBox2dBaseShape> shape) {
		if (!ofRectangle(0, -400, ofGetWidth(), ofGetHeight() + 400).inside(shape.get()->getPosition())) {
			return true;
		}
		return false;
	}
};