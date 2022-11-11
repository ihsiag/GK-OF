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
	void setup(stringstream* _ssGlobalLog, const int& _frameRate);
	void setup(const int& _frameRate);
	void setCam(ofEasyCam* _cam);
	void scrollCamera(ofEasyCam *_cam,const int& _scrollY);
	void defaultUpdate(unsigned long int* _currentFrame, float* _time);
	void defaultUpdate(unsigned long int* _currentFrame, float* _time, const glm::vec4& _col);
	void defaultUpdate(ofEasyCam* _cam, unsigned long int* _currentFrame, float* _time);
	void defaultUpdate(ofEasyCam* _cam, unsigned long int* _currentFrame, float* _time, const glm::vec4& _col);
	glm::vec2 getPosLayout4x4(const int& _index);
	glm::vec2 getPosLayout4x4Inverse(const int& _index);


//-------------------------------------------------------HELPER_GUI-------------------------------------------------------//
	
	glm::vec3 myGUIPos(const int& _indexPos);
	float myGUIWidth();
	void setGUI(ofxGuiGroup& _gui,const int& _posIndex);
	void resizeGUI(ofxGuiGroup& _gui, const int& _posIndex);
	void setGraphGUI(const int& _indexPos, const glm::vec2& _size, const glm::vec2& _originalSize);
	void drawMouseOnGraphGUI(const int& _indexPos, const glm::vec2& _size, const glm::vec2& _originalSize, glm::vec2* _mouseOnWorldPlane);
	void drawEachDataOnGraphGUI(const int& _indexPos, const glm::vec2& _size, const glm::vec2& _originalSize, glm::vec3& _data, const glm::vec3& _normalOfData);


//-------------------------------------------------------HELPER_2D-------------------------------------------------------//
	void drawInfo(const stringstream& _ss, const int& _indexPos, const ofTrueTypeFont& _font, const int& _fontSize);
	void drawInfo(const stringstream& _ss, const int& _indexPos);
	void drawInfo(const stringstream& _ss, const int& _indexPos, const bool& _bSetMargin, const glm::vec2& _margin);
	void drawInfo(const stringstream& _ss, const glm::vec2& _xyPos);
	void drawInfo(const string& _s, const glm::vec2& _xyPos);
	void drawInfo(const stringstream& _ss, const glm::vec2& _xyPos ,const ofTrueTypeFont& _font, const int& _fontSize);
	void manageInfoLimit(stringstream* _ss,const float& _height); // <- still blanc
	void manageInfoLimit(stringstream* _ss, const int& _numOfGrids); // <-still blanc
	void drawGrid();
	void drawCross(const int& _x, const int& _y, const int& _size);
	void drawCross(const glm::vec3& _normalPlaneToDraw, const int& _x, const int& _y, const int& _size);


//-------------------------------------------------------HELPER_3D-------------------------------------------------------//
	void draw3DAxis();
	void draw3DAxis(const float& _size,const float& _lineWidth,const float& _alpha);
	void draw3DPlaneGrid(const float& _sizeUnit, const int& _numUnit, const glm::vec3& _normalPlaneToDraw, const float& _lineWidth, const glm::vec4& _col);
	void draw3DBox(const glm::vec3& _center, const float& _sizeW, const float& _sizeH, const float& _sizeD, const float& _lineWidth, const glm::vec4& _lineColor);
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

//-------------------------------------------------------HELPER_IMPORT-------------------------------------------------------//
	string findLatestFilePath(const string& _dirPath, const string& _fileType);
	string extractFilePathWithoutExt(const string& _filePath);
	void loadImgsInDir(vector<ofImage>* _imgs, const string& _dirPath);
	void loadImgsInDir(vector<ofImage>* _imgs,vector<string>* _names, const string& _dirPath);
	void importGK3D(const string& _url, ofMesh& _meshToPass, vector<GKPlane>& _gkPlanesCreatedFromMeshToPass, vector<GKPlane>& _gkPlanesCreatedManuallyToPass);


//-------------------------------------------------------HELPER_SAVE-------------------------------------------------------//
	void saveVideo(const float& _currentFrame);
	
	stringstream makeFileName(const string& _folderName, const string& _fileType);
	void saveImage();
	void saveImage(const string& _url);
	void saveFBOtoImage(ofFbo* _fbo);
	void saveFBOtoImage(ofFbo* _fbo, const string& _url);
	void saveMesh(ofMesh& _mesh, const float& _scaleFactor);
	void saveMesh(ofMesh& _mesh, const float& _scalefactor, const string& _url);
	void saveGK3D(const string& _url, ofMesh& _originalMesh,vector<GKPlane> &_gkPlanesCreatedFromMesh, vector<GKPlane>& _gkPlanesCreatedManually);
};
#endif