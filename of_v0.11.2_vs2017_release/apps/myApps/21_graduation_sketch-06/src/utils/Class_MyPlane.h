#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofEvents.h"
#include "Class_MyLineSimple.h"

class Class_MyPlane {
	public:
		int ID;
		glm::vec3 normal;
		glm::vec3 centroid;
		vector<glm::vec3> vertices;
		vector<Class_MyLineSimple> edges;
		float scaleFactor;

		Class_MyPlane() {}
		~Class_MyPlane() {}
		
		void setup(const ofMesh& _inputMesh,const int& _index,stringstream* _ssLog) {
			originalMesh = _inputMesh;
			ID = _index;
			ssLog = _ssLog;
			centroid = originalMesh.getCentroid();
			getNormal();
			modifyInfo.setGlobalPosition(0,0,0);
			bMadeMyPlane = false;
			makeMyPlane();
			getMyPlaneEdges();
		};
				
		//-----------THIS-TIME-UTILS-----------//
		void drawInputMesh() {
			glColor4f(0, 1, 1, 0.5);
			originalMesh.drawFaces();
			glColor4f(1, 1, 0, 1);
			glLineWidth(2);
			originalMesh.drawWireframe();
		};
		void drawInputMeshVertices() {
			glColor4f(0.6, 0.6, 0.9, 1);
			glPointSize(10);
			originalMesh.drawVertices();
		}
		void drawMyPlane() {
			if (bMadeMyPlane) {
				ofFill();
				glColor4f(0.8, 0.2, 0.2, 1);

				//ofPushMatrix();
				//ofMultMatrix(modifyInfo.getGlobalTransformMatrix());
				//ofDrawCircle(0,0, 20);
				//ofPopMatrix();


				glBegin(GL_POLYGON);
				for (auto& vertex : vertices) {
					glVertex3f(vertex.x, vertex.y, vertex.z);
				}
				glEnd();
				ofNoFill();
				glColor4f(1, 0.4, 0.4, 1);
				glLineWidth(2);
				glBegin(GL_LINE_LOOP);
				for (auto& vertex : vertices) {
					glVertex3f(vertex.x, vertex.y, vertex.z);
				}
				glEnd();
				glColor4f(1, 0.4, 0.4, 1);
				glPointSize(4);
				glBegin(GL_POINTS);
				for (auto& vertex : vertices) {
					glVertex3f(vertex.x, vertex.y, vertex.z);
				}
				glEnd();
			}
		}
		void drawMyPlaneNormal() {
			glBegin(GL_LINES);
			glLineWidth(3);
			glColor4f(1, 0, 1, 0.8);
			glVertex3f(centroid.x, centroid.y, centroid.z);
			glVertex3f(centroid.x + normal.x*10, centroid.y + normal.y*10, centroid.z + normal.z*10);
			glEnd();
		}
		void drawMyPlaneCentroid() {
			ofPushMatrix();
			ofMultMatrix(modifyInfo.getGlobalTransformMatrix());
			glColor3f(1, 0, 1);
			gk.drawCross(0, 0, 10);
			ofPopMatrix();
		}
		
		//-----------EVENT-----------//
		void keyPressed(const int& key) {
			switch (key) {
			//case ' ':
			//	break;
			}
		};
	
	private:
		ofxGKUtils gk;
		stringstream* ssLog;		
		ofMesh originalMesh;
		ofNode modifyInfo;
		bool bMadeMyPlane;

		//-----------THIS-TIME-UTILS-----------//
		void getNormal() {
			normal = glm::cross(originalMesh.getVertex(0) - originalMesh.getVertex(1), originalMesh.getVertex(0) - originalMesh.getVertex(2));
			normal = glm::normalize(normal);
		}
		void makeMyPlane() {
			glm::vec3 _centroid = originalMesh.getCentroid();
			modifyInfo.resetTransform();
			modifyInfo.lookAt(normal);
			modifyInfo.move(_centroid);
			float _dist = 0;
			float _maxDist = _dist;
			for (auto& _v : originalMesh.getVertices()) {
				_dist = glm::distance(_v, _centroid);
				if (_dist > _maxDist)_maxDist = _dist;
			}
			vector<glm::vec3> _vertices;
			_vertices.push_back(glm::vec3(-_maxDist, -_maxDist, 0));
			_vertices.push_back(glm::vec3(-_maxDist, _maxDist, 0));
			_vertices.push_back(glm::vec3(_maxDist, _maxDist, 0));
			_vertices.push_back(glm::vec3(_maxDist, -_maxDist, 0));
			if (vertices.size())vertices.erase(vertices.begin(), vertices.end());
			vertices = gk.getModifiedVertices(&_vertices, modifyInfo);
			_vertices.erase(_vertices.begin(), _vertices.end());
			bMadeMyPlane = true;
			*ssLog << "MADE MY-PLANE" << endl;
		}
		void getMyPlaneEdges() {
			edges.reserve(vertices.size());				
			for (int i = 0; i < vertices.size(); i++) {
				Class_MyLineSimple _edge;
				if (i + 1 < vertices.size()) {
					_edge.setup(vertices[i], vertices[i + 1]);
				}
				else {
					_edge.setup(vertices[i], vertices[0]);
				}
				edges.push_back(_edge);
			}
		}
};