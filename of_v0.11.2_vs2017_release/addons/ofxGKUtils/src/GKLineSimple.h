#pragma once
#ifndef GK_LINE_SIMPLE_H
#define GK_LINE_SIMPLE_H

#include "ofMain.h"
#include "ofxGKUtils.h"

#endif

class GKLineSimple {
	public:
		glm::vec3 a, b;

		GKLineSimple() {}
		GKLineSimple(const glm::vec3& _a, const glm::vec3& _b) {
			a = _a;
			b = _b;
		}
		~GKLineSimple() {}
		void setup(const glm::vec3& _a, const glm::vec3& _b) {
			a = _a;
			b = _b;
		}
				
		//-----------THIS-TIME-UTILS-----------//	
		void drawLine() {
			glBegin(GL_LINES);
			glVertex3f(a.x, a.y, a.z);
			glVertex3f(b.x, b.y, b.z);
			glEnd();
		}

		void drawVertices() {
			glBegin(GL_POINTS);
			glVertex3f(a.x, a.y, a.z);
			glVertex3f(b.x, b.y, b.z);
			glEnd();
		}

		vector<glm::vec3> getVertices() {
			vector<glm::vec3> _vertices;
			_vertices.reserve(2);
			_vertices.push_back(a);
			_vertices.push_back(b);
			return _vertices;
		}

		float getLength() {
			return glm::distance(a, b);
		}

		glm::vec3 getCenter() {
			return (a + b) / 2;
		}
	
private:
};