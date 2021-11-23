#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofEvents.h"

class Class_MyFace {
	public:
		glm::vec3 normal;
		vector<glm::vec3> vertices;

		void setup(vector< glm::vec3> _vertices) {
			vertices = _vertices;
		};
		void update();
		void display() {
			ofFill();
			glColor4f(0, 1, 1, 0.5);
			glBegin(GL_POLYGON);
			for (auto& vertex : vertices) {
				glVertex3f(vertex.x, vertex.y, vertex.z);
			}
			glEnd();
			glColor4f(0, 0, 0,1);
			glLineWidth(2);
			ofNoFill();
			glBegin(GL_LINES);
			for (auto& vertex : vertices) {
				glVertex3f(vertex.x, vertex.y, vertex.z);
			}
			glEnd();
		};
		
		bool mousePressed(ofMouseEventArgs& args);
};