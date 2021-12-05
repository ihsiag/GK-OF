#pragma once
#ifndef GK_PLANE_H
#define GK_PLANE_H

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxGKUtils.h"
#include "GKLineSimple.h"




class GKPlane  {
	public:
		//int ID;
		int state;
		glm::vec3 normal;
		glm::vec3 centroid;
		vector<glm::vec3> vertices;
		vector<GKLineSimple> edges;
		ofNode modifyInfo;
		float scaleFactor;

		GKPlane() {
			state = 0;
		}
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
			modifyInfo.setGlobalPosition(0, 0, 0);
			bMadeGKPlane = false;
			makeGKPlaneFromVertices();
			getGKPlaneEdges();
		}
				
		//-----------THIS-TIME-UTILS-----------AUTO//
		void drawGKPlane() {
			if (bMadeGKPlane) {
				//ofPushMatrix();
				//ofMultMatrix(modifyInfo.getGlobalTransformMatrix());
				//ofDrawCircle(0,0, 20);
				//ofPopMatrix();
				ofFill();
				glBegin(GL_POLYGON);				
				glColor4f(0.6, 0.0, 0.0, 0.8);
				for (auto& vertex : vertices) {
					glVertex3f(vertex.x, vertex.y, vertex.z);
				}
				glEnd();				
				glBegin(GL_LINE_LOOP);
				ofNoFill();
				glColor4f(1, 0.4, 0.4, 1);
				glLineWidth(2);
				for (auto& vertex : vertices) {
					glVertex3f(vertex.x, vertex.y, vertex.z);
				}
				glEnd();
				glPointSize(2);
				glBegin(GL_POINTS);
				glColor4f(1, 0.4, 0.4, 1);			
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
				gkDrawCross(0, 0, 10); //clonedFrom ofxGKUtils
				ofPopMatrix();
			}
		}	
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
		bool hasInside(const glm::vec3& _vertex) {
			bool _result = true;
			glm::vec3 _mainDir;
			for (int i = 0; i < vertices.size() - 1; i++) {
				glm::vec3 _dir = glm::normalize(glm::cross(vertices[i + 1] - vertices[i], _vertex - vertices[i + 1]));
				if (i == 0) {
					_mainDir = _dir;
				}
				else {
					if (glm::angle(_dir, _mainDir) > PI / 4) {
						_result = false;
						break;
					}
				}
			}
			return _result;
		}
		ofMesh convertToMesh() {
			ofMesh _meshContainer;
			for (int i = 0; i < vertices.size();i++) {
				ofMesh _fragment;
				_fragment.addVertex(centroid);
				_fragment.addVertex(vertices[i]);
				_fragment.addVertex(vertices[(i + 1)%vertices.size()]);
				_meshContainer.append(_fragment);
			}
			return _meshContainer;
		}
		//-----------THIS-TIME-UTILS-----------CUSTOM//
		void drawGKPlane(const glm::vec4& _faceCol, const glm::vec4& _edgeCol, const float& _lineWidth) {
			if (bMadeGKPlane) {
				ofFill();
				glBegin(GL_POLYGON);
				glColor4f(_faceCol.r, _faceCol.g, _faceCol.b, _faceCol.a);
				for (auto& vertex : vertices) {
					glVertex3f(vertex.x, vertex.y, vertex.z);
				}
				glEnd();
				ofNoFill();						
				glBegin(GL_LINE_LOOP);
				glColor4f(_edgeCol.r, _edgeCol.g, _edgeCol.b, _edgeCol.a);
				glLineWidth(_lineWidth);
				for (auto& vertex : vertices) {
					glVertex3f(vertex.x, vertex.y, vertex.z);
				}
				glEnd();
				glPointSize(_lineWidth * 2);
				glBegin(GL_POINTS);
				glColor4f(_edgeCol.r, _edgeCol.g, _edgeCol.b, _edgeCol.a);			
				for (auto& vertex : vertices) {
					glVertex3f(vertex.x, vertex.y, vertex.z);
				}
				glEnd();
			}
		}
		void drawGKPlaneNormal(const glm::vec4& _debugCol, const float& _size,const float& _lineWidth) {
			if (bMadeGKPlane) {
				glBegin(GL_LINES);
				glLineWidth(_lineWidth);
				glColor4f(_debugCol.r, _debugCol.g, _debugCol.b, _debugCol.a);
				glVertex3f(centroid.x, centroid.y, centroid.z);
				glVertex3f(centroid.x + normal.x * _size, centroid.y + normal.y * _size, centroid.z + normal.z * _size);
				glEnd();
			}
		}
		void drawGKPlaneCentroid(const glm::vec4& _debugCol, const float& _size, const float& _lineWidth) {
			if (bMadeGKPlane) {
				ofPushMatrix();
				ofMultMatrix(modifyInfo.getGlobalTransformMatrix());
				glColor4f(_debugCol.r, _debugCol.g, _debugCol.b, _debugCol.a);
				gkDrawCross(0, 0, _size); //clonedFrom ofxGKUtils
				ofPopMatrix();
			}
		}
		void drawInputMesh(const glm::vec4& _faceCol, const glm::vec4& _edgeCol, const float& _lineWidth) {
			if (originalMesh.hasVertices()) {
				glColor4f(_faceCol.r, _faceCol.g, _faceCol.b, _faceCol.a);
				originalMesh.drawFaces();
				glColor4f(_edgeCol.r, _edgeCol.g, _edgeCol.b, _edgeCol.a);
				glLineWidth(_lineWidth);
				originalMesh.drawWireframe();
			}
		};
		void drawInputMeshVertices(const glm::vec4& _vertexCol, const float& _pointSize) {
			if (originalMesh.hasVertices()) {
				glColor4f(_vertexCol.r, _vertexCol.g, _vertexCol.b, _vertexCol.a);
				glPointSize(_pointSize);
				originalMesh.drawVertices();
			}
		}
		//-----------EVENT-----------//
		void keyPressed(const int& key) {
			switch (key) {
			//case ' ':
			//	break;
			}
		};

		bool operator == (const GKPlane& _gpl) const {
			return state == _gpl.state;
		}

		bool operator < (const GKPlane& _gpl) const{
			return state < _gpl.state;
		}
		
	
	private:
		ofMesh originalMesh;
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
			vertices = gkGetModifiedVertices(_vertices, modifyInfo); //cloned From ofxGKUtils
			_vertices.erase(_vertices.begin(), _vertices.end());
			bMadeGKPlane = true;
		}
		void makeGKPlaneFromVertices() {
			modifyInfo.resetTransform();
			modifyInfo.lookAt(normal);
			modifyInfo.move(centroid);
			bMadeGKPlane = true;
		}
		//not work ^
		void getGKPlaneEdges() {
			edges.reserve(vertices.size());				
			for (int i = 0; i < vertices.size(); i++) {
				GKLineSimple _edge;
				_edge.setup(vertices[i], vertices[(i + 1)%vertices.size()]);
				edges.push_back(_edge);
			}
		}


		//cloneed from ofxGKUtils
		void gkDrawCross(const int& _x, const int& _y, const int& _size) { //clonedFrom ofxGKUtils
			glLineWidth(1);
			ofPushMatrix();
			ofTranslate(_x, _y);
			glBegin(GL_LINES);
			glVertex2f(-_size / 2, 0);
			glVertex2f(_size / 2, 0);
			glEnd();
			glBegin(GL_LINES);
			glVertex2f(0, -_size / 2);
			glVertex2f(0, _size / 2);
			glEnd();
			ofPopMatrix();
		}
		vector<glm::vec3> gkGetModifiedVertices(const vector<glm::vec3>& _inputVertices, const ofNode& _modifyInfo) {
			vector<glm::vec3> _vertices = _inputVertices;
			auto mat = _modifyInfo.getGlobalTransformMatrix();
			for (auto& v : _vertices) {
				v = glm::vec3(mat * glm::vec4(v, 1));
			}
			/*
			auto mat2 = _modifyInfo.getOrientationQuat();
			for (auto& v : *_normals) {
				v = glm::vec3(mat2 * glm::vec4(v, 1));
			}
			*/
			return _vertices;
		}
};

#endif