#pragma once
#ifndef OFX_GKUTILS_H
#define OFX_GKUTILS_H

#include "ofMain.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

using namespace std;

#endif

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
	glm::vec2 getPosLayout4x4(const int& _index);


//-------------------------------------------------------HELPER_GUI-------------------------------------------------------//
	glm::vec3 myGUIPos();
	float myGUIWidth();
	void setGUI(ofxGuiGroup& _gui);
	void resizeGUI(ofxGuiGroup& _gui);
	void setGraphGUI(const int& _indexPos, const glm::vec2& _size, const glm::vec2& _originalSize, glm::vec2* _mouseOnWorldPlane);
	void putEachDataOnGraphGUI(const int& _indexPos, const glm::vec2& _size, const glm::vec2& _originalSize, glm::vec3& _data, const glm::vec3& _normalOfData);


//-------------------------------------------------------HELPER_2D-------------------------------------------------------//
	void drawInfo(const stringstream& _ss, const int& _indexPos, const ofTrueTypeFont& _font, const int& _fontSize);
	void drawInfo(const stringstream& _ss, const int& _indexPos);
	void drawGrid();
	void drawCross(const int& _x, const int& _y, const int& _size);


//-------------------------------------------------------HELPER_3D-------------------------------------------------------//
	void draw3DAxis();
	float* getBoundingBox(ofMesh& _mesh);
	void drawFoundCenterTo3D(const glm::vec3& _pos, glm::vec2 _size, const glm::vec3& _normalPlaneToDraw);
	void drawFoundCenterTo2D(const glm::vec3& _pos, glm::vec2 _size, const glm::vec3& _normalOfData);


//-------------------------------------------------------HELPER_SAVE-------------------------------------------------------//
	void saveVideo(const float& _currentFrame);
	
	stringstream makeFileName(const string& _folderName, const string& _fileType);
	void saveImage();
	void saveFBOtoImage(ofFbo* _fbo);
	void saveMesh(ofMesh& _mesh, const float& _scaleFactor);
};