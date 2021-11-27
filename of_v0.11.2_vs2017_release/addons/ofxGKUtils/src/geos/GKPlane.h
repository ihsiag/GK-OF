#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofEvents.h"
#include "GKLineSimple.h"

class GKPlane : public ofxGKUtils {
	public:
		//int ID;
		int state;
		glm::vec3 normal;
		glm::vec3 centroid;
		vector<glm::vec3> vertices;
		vector<GKLineSimple> edges;
		float scaleFactor;

		GKPlane() {}
		~GKPlane() {}
		
		void setup(const ofMesh& _inputMesh,const int& _state) {
			originalMesh = _inputMesh;
			state = _state;
			//ID = _index;
			centroid = originalMesh.getCentroid();
			getNormalFromMesh();
			modifyInfo.setGlobalPosition(0,0,0);
			bMadeGKPlane = false;
			makeGKPlaneFromMesh();
			getGKPlaneEdges();
		};
		void setup(const vector<glm::vec3>& _sortedVertices, const int& _state) {
			vertices = _sortedVertices;
			state = _state;
			//ID = _index;
			centroid = getCentroidFromVertices();
			getNormalFromVertices();
			
			bMadeGKPlane = false;
			makeGKPlaneFromVertices();
			getGKPlaneEdges();
		}
				
		//-----------THIS-TIME-UTILS-----------//
		void drawInputMesh() {
			if (originalMesh.hasVertices()) {
				glColor4f(0, 1, 1, 0.5);
				originalMesh.drawFaces();
				glColor4f(1, 1, 0, 1);
				glLineWidth(2);
				originalMesh.drawWireframe();
			}	
		};
		void drawInputMeshVertices() {
			if (originalMesh.hasVertices()) {
				glColor4f(0.6, 0.6, 0.9, 1);
				glPointSize(10);
				originalMesh.drawVertices();
			}
		}
		void drawGKPlane() {
			if (bMadeGKPlane) {
				ofFill();
				glColor4f(0.8, 0.2, 0.2, 0.8);

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
		void drawGKPlaneNormal() {
			if (bMadeGKPlane) {
				glBegin(GL_LINES);
				glLineWidth(3);
				glColor4f(1, 0, 1, 0.8);
				glVertex3f(centroid.x, centroid.y, centroid.z);
				glVertex3f(centroid.x + normal.x * 10, centroid.y + normal.y * 10, centroid.z + normal.z * 10);
				glEnd();
			}
		}
		void drawGKPlaneCentroid() {
			if (bMadeGKPlane) {
				ofPushMatrix();
				ofMultMatrix(modifyInfo.getGlobalTransformMatrix());
				glColor3f(1, 0, 1);
				drawCross(0, 0, 10);
				ofPopMatrix();
			}
		}
		
		bool hasInside(const glm::vec3& _vertex) {
			bool _result = true;
			glm::vec3 _preDir;
			for (int i = 0; i < vertices.size(); i++) {
				glm::vec3 _dir = glm::normalize(glm::cross(vertices[i + 1] - vertices[i], _vertex - vertices[i+1]));
				if (i!=0 && _preDir != _dir) {
					_result = false;
					break;
				}
				else {
					_preDir = _dir;
				}
			}
			return _result;
		}
		//-----------EVENT-----------//
		void keyPressed(const int& key) {
			switch (key) {
			//case ' ':
			//	break;
			}
		};
	
	private:		
		ofMesh originalMesh;
		ofNode modifyInfo;
		bool bMadeGKPlane;

		//-----------THIS-TIME-UTILS-----------//
		glm::vec3 getCentroidFromVertices() {
			glm::vec3 _centroid = glm::vec3(0);
			for (auto& vertex : vertices) {
				_centroid += vertex;
			}
			return _centroid / vertices.size();
		}
		void getNormalFromMesh() {
			normal = glm::cross(originalMesh.getVertex(0) - originalMesh.getVertex(1), originalMesh.getVertex(0) - originalMesh.getVertex(2));
			normal = glm::normalize(normal);
		}
		void getNormalFromVertices() {
			normal = glm::cross(vertices[0] - vertices[1], vertices[0] - vertices[2]);
			glm::normalize(normal);
		}
		void makeGKPlaneFromMesh() {
			modifyInfo.resetTransform();
			modifyInfo.lookAt(normal);
			modifyInfo.move(centroid);
			float _dist = 0;
			float _maxDist = _dist;
			for (auto& _v : originalMesh.getVertices()) {
				_dist = glm::distance(_v, centroid);
				if (_dist > _maxDist)_maxDist = _dist;
			}
			vector<glm::vec3> _vertices;
			_vertices.push_back(glm::vec3(-_maxDist, -_maxDist, 0));
			_vertices.push_back(glm::vec3(-_maxDist, _maxDist, 0));
			_vertices.push_back(glm::vec3(_maxDist, _maxDist, 0));
			_vertices.push_back(glm::vec3(_maxDist, -_maxDist, 0));
			if (vertices.size())vertices.erase(vertices.begin(), vertices.end());
			vertices = getModifiedVertices(_vertices, modifyInfo);
			_vertices.erase(_vertices.begin(), _vertices.end());
			bMadeGKPlane = true;
			*ssLog << "MADE MY-PLANE" << endl;
		}
		void makeGKPlaneFromVertices() {
			modifyInfo.resetTransform();
			modifyInfo.lookAt(normal);
			modifyInfo.move(centroid);
			bMadeGKPlane = true;
			*ssLog << "MADE MY-PLANE" << endl;
		}
		//not work ^
		void getGKPlaneEdges() {
			edges.reserve(vertices.size());				
			for (int i = 0; i < vertices.size(); i++) {
				GKLineSimple _edge;
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