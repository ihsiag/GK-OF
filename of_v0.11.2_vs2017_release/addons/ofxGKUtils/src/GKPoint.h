#pragma once

#ifndef GK_POINT_H
#define GK_POINT_H

#include "ofMain.h"
#include "ofxGKUtils.h"



class GKPoint {
	public:
		// int ID;
		int state;
		glm::vec3 pos;
		GKPoint(){
			state = 0;
		}
		GKPoint(const glm::vec3& _vertex) {
			pos = _vertex;
			state = 0;
		}
		GKPoint(const float& _x, const float& _y, const float& _z) {
			pos = glm::vec3(_x, _y, _z);
			state = 0;
		}
		GKPoint(const glm::vec3& _vertex,const int& _state) {
			pos = _vertex;
			state = _state;
		}
		GKPoint(const float& _x, const float& _y, const float& _z,const int& _state) {
			pos = glm::vec3(_x, _y, _z);
			state = _state;
		}
		~GKPoint() {}
		
		//-----------THIS-TIME-UTILS-----------//	
		void setState(const int& _state) {
				state = _state;
		}
		void resetState() {
			state = 0;
		}
		void drawGKPoint() {
			glBegin(GL_POINT);
			glPointSize(10);
			glColor4f(0.6, 0.6, 0.9, 1);
			glVertex3f(pos.x, pos.y, pos.z);
			glEnd();			
		}
		

		//-----------OPERATOR-----------// -> mainly For Sort Algo.

		bool operator==(const GKPoint& _gp) const{
			return pos.x == _gp.pos.x && pos.y == _gp.pos.y && pos.z == _gp.pos.z;
		}

		bool operator<(const GKPoint& _gp) const {
			return pos.x != _gp.pos.x ? pos.x < _gp.pos.x :
				pos.y != _gp.pos.y ? pos.y < _gp.pos.y :
				pos.z < _gp.pos.z;
		}


private:
	

	
};
#endif