#pragma once

#include "ofMain.h"

class Class_MyLineSimple {
	public:
		glm::vec3 a, b;

		Class_MyLineSimple() {}
		~Class_MyLineSimple() {}
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

		void drawVertex() {
			glBegin(GL_POINTS);
			glVertex3f(a.x, a.y, a.z);
			glVertex3f(b.x, b.y, b.z);
			glEnd();
		}

		float getLength() {
			return glm::distance(a, b);
		}

		glm::vec3 getCenter() {
			return (a + b) / 2;
		}
	
private:
};