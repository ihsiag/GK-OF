#pragma once
#ifndef OFX_GKUTILS_H
#define OFX_GKUTILS_H

#include "ofMain.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

#include "GKPoint.h"
#include "GKPlane.h"
#include "GKLineSimple.h"


using namespace std;

class ofxGKUtils {
public:
	ofxGKUtils() {
	}
	~ofxGKUtils() {
	}

//-------------------------------------------------------GLOBAL-------------------------------------------------------//
	int margin;
	stringstream* ssLog;


//-------------------------------------------------------HELPER_DEFAULT-------------------------------------------------------//
	void setup(stringstream* _ssGlobalLog);
	void setCam(ofEasyCam* _cam);
	void defaultUpdate(ofEasyCam* _cam, unsigned long int* _currentFrame, float* _time);
	void defaultUpdate(ofEasyCam* _cam, unsigned long int* _currentFrame, float* _time, const glm::vec4& _col);
	glm::vec2 getPosLayout4x4(const int& _index);


//-------------------------------------------------------HELPER_GUI-------------------------------------------------------//
	
	glm::vec3 myGUIPos(const int& _indexPos);
	float myGUIWidth();
	void setGUI(ofxGuiGroup& _gui);
	void resizeGUI(ofxGuiGroup& _gui);
	void setGraphGUI(const int& _indexPos, const glm::vec2& _size, const glm::vec2& _originalSize);
	void drawMouseOnGraphGUI(const int& _indexPos, const glm::vec2& _size, const glm::vec2& _originalSize, glm::vec2* _mouseOnWorldPlane);
	void drawEachDataOnGraphGUI(const int& _indexPos, const glm::vec2& _size, const glm::vec2& _originalSize, glm::vec3& _data, const glm::vec3& _normalOfData);


//-------------------------------------------------------HELPER_2D-------------------------------------------------------//
	void drawInfo(const stringstream& _ss, const int& _indexPos, const ofTrueTypeFont& _font, const int& _fontSize);
	void drawInfo(const stringstream& _ss, const int& _indexPos);
	void drawInfo(const stringstream& _ss, const glm::vec2& _xyPos);
	void drawGrid();
	void drawCross(const int& _x, const int& _y, const int& _size);


//-------------------------------------------------------HELPER_3D-------------------------------------------------------//
	void draw3DAxis();
	void draw3DAxis(const float& _size,const float& _lineWidth,const float& _alpha);
	void draw3DPlaneGrid(const float& _sizeUnit, const int& _numUnit, const glm::vec3& _normalPlaneToDraw, const float& _lineWidth, const glm::vec4& _col);
	float* getBoundingBox(const ofMesh& _mesh);
	float* getBoundingBox(const ofMesh& _mesh,const glm::vec3& _planeNormal); //not work need help
	void drawFoundCenterTo3D(const glm::vec3& _pos, glm::vec2 _size, const glm::vec3& _normalPlaneToDraw);
	void drawFoundCenterTo2D(const glm::vec3& _pos, glm::vec2 _size, const glm::vec3& _normalOfData);
	ofMesh getModifiedMesh(const ofMesh& _mesh, const ofNode& _modifyInfo);
	vector<glm::vec3> getModifiedVertices(const vector<glm::vec3>& _vertices, const ofNode& _modifyInfo);
	vector<glm::vec3> getOnPlaneVertices(const vector<glm::vec3>& _vertices, const ofNode& _modifyInfo); //not work need help
	glm::vec3 getPolarFromRectangular(const glm::vec3& _coord);//->glm::polar(v)
	glm::vec3 getPolarFromRectangular(const GKPoint& _gkPoint); //->glm::polar(v)
	glm::vec3 getRectangularFromPolar(const glm::vec3& _coord);//->glm::euclidean(v)
	glm::vec3 getRectangularFromPolar(const GKPoint& _gkPoint);//->glm::euclidean(v)
	void sortPolars(vector<glm::vec3>* _coords);
	void sortPolars(vector<GKPoint>* _gkPoints);
//-------------------------------------------------------HELPER_CALC-------------------------------------------------------//
	int factorial(int _n);
	int totalNumCombination(int _n, int _r);
	vector<glm::vec2> getIndexList_nC2(int _n);

//-------------------------------------------------------HELPER_SAVE-------------------------------------------------------//
	void saveVideo(const float& _currentFrame);
	
	stringstream makeFileName(const string& _folderName, const string& _fileType);
	void saveImage();
	void saveFBOtoImage(ofFbo* _fbo);
	void saveMesh(ofMesh& _mesh, const float& _scaleFactor);
};
#endif