#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofEasyCam.h"
#include "ofCamera.h"
#include "ofxGui.h"
#include "ofxPostProcessing.h"

//
#include "Class_Analysis.h"




class ofApp : public ofBaseApp {

public:
	//-----------IMPORT
	Class_Analysis analysis;
	ofCamera cam;
	ofEasyCam ezCam;
	ofTrueTypeFont font;
	ofShader shaderMesh;
	ofShader shaderPost;
	ofxPostProcessing post;

	ofxPanel gui;
	
	ofMesh meshScan;
	ofMesh meshCreate;
	//ofxAssimpModelLoader model;
	vector < glm::vec3> listPosVertexScan;
	vector <glm::vec2> myArr;
	
	//ofVboMesh vboMesh;
	ofFbo fbo;
	ofPixels pixels;

	//-----------GLOBAL
	float time;
	float currentFrame = -1.0;
	int fontSize = 10;
	ofImage imgToSave;

	bool scanEnd = false;
	bool createEnd = false;

	bool IsUpdateCamera = true;

	//-----------Sliders
	ofxFloatSlider modelShaderAlpha;




	//-----------STRUCTURE
	void setup() {
		ofSetVerticalSync(true);
		
		//ezCam.setNearClip(0.1);
		//ezCam.setFarClip(100000);
		//ezCam.setPosition(0, 0, 0);
		//ezCam.lookAt(glm::vec3(0, 0, 0),glm::vec3(0,0,1));
		//ezCam.enableOrtho();
		//ezCam.disableMouseInput();
		//ezCam.enableMouseInput();
		//ezCam.enableMouseMiddleButton();

		meshScan.load("./3D/can_piece_remesh02.ply");

				
	}

	void update() {
		currentFrame += 1.0;
		//ofSetWindowTitle(ofToString(ofGetFrameRate()));
		time = ofGetElapsedTimef();
		ofSetWindowTitle(ofToString(time));
		readyForDraw();
		if(IsUpdateCamera)updateCamera();
	}

	void draw() {
		
		//update();	
		
		ezCam.begin();//-----------camBEGIN	
		if (!scanEnd && !createEnd) {
			glColor3f(0.6, 0.6, 0.6);
			meshScan.drawWireframe();
			glPointSize(2);
			glColor3f(1, 1, 1);
			meshScan.drawVertices();
		}
		if (scanEnd && !createEnd) {
			if (!analysis.calcEnd) {
				analysis.setup(listPosVertexScan);
				myArr = analysis.calcLeastSquaresMethod();
			}
		}
		if (createEnd) {
			glColor3f(0.6, 0.6, 0.6);
			meshCreate.drawWireframe();
			glPointSize(2);
			glColor3f(1, 1, 1);
			meshCreate.drawVertices();
		}

		
		ezCam.end();//-----------camEND
		
		if (analysis.calcEnd) {
			analysis.display();
		}
		if (!createEnd && analysis.displayEnd) {
			createMesh();
		}
		

		//-----------PrepairBEGIN
		int numVertexScan = meshScan.getNumVertices();
		//int indexVertexScan = int(currentFrame) % numVertexScan;
		int indexVertexScan = int(currentFrame);	
		//-----------PrepairEND

		if (indexVertexScan < numVertexScan) {//----------ScanBEGIN --Content: 1Dim,Notation
			
			//-----------1DimBEGIN
			listPosVertexScan.push_back(meshScan.getVertex(indexVertexScan));
			if (listPosVertexScan.size() > 1) {
				glLineWidth(2);
				glColor3f(1, 0, 0);
				glBegin(GL_LINES);
				for (int i = 0; i < listPosVertexScan.size()-1; i++) {
					glVertex2f(i, ofGetHeight() / 2 + listPosVertexScan[i].z);
					glVertex2f(i + 1, ofGetHeight() / 2 + listPosVertexScan[i + 1].z);
				}
				glEnd();
			}
			//-----------1DimEND

			//-----------NotationBEGIN
			glm::vec3 screenPosVertexScan = ezCam.worldToScreen(meshScan.getVertex(indexVertexScan));
			ofNoFill();
			glColor3f(1, 1, 0);
			glLineWidth(2);
			ofDrawCircle(screenPosVertexScan, 4);
			ofSetLineWidth(1);

			glm::vec2 posConsole = glm::vec2(ofGetWidth() * 0.75, ofGetHeight() * 0.25);

			ofSetColor(ofColor::red);
			ofDrawLine(screenPosVertexScan, posConsole);

			ofDrawBitmapStringHighlight(ofToString(indexVertexScan), posConsole + glm::vec2(0, 10));
			ofDrawBitmapStringHighlight(ofToString(meshScan.getVertex(indexVertexScan)), posConsole + glm::vec2(0, 30));
			//-----------NotationEND
		
		}
		else {
			scanEnd = true;
		}//----------ScanEND --Content: 1Dim,Notation

		//-----------LayoutBEGIN
		makeGrid();
		//-----------LayoutEND
		
	}

	//-----------CUSTOM-FUNCS
	void makeGrid() {
		//
		ofNoFill();
		ofSetColor(50);
		ofDrawLine(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() / 2);
		ofDrawLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());

		//
		ofNoFill();
		ofSetColor(50);
		int margin = 8;
		ofDrawRectangle(margin, margin, ofGetWidth() - margin * 2, ofGetHeight() - margin * 2);

		//
		ofFill();
		ofSetColor(255);
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		for (int y = -1; y < 2; y++) {
			for (int x = -1; x < 2; x++) {
				if (y != 0) {
					if (x != 0) {
						drawCross(x * ofGetWidth() / 4, y * ofGetHeight() / 4, 10);
					}
				}
			}
		}
		ofPopMatrix();

		//

	}

	void drawCross(int _x, int _y, int _size) {
		ofPushMatrix();
		ofTranslate(_x, _y);
		ofDrawLine(-_size / 2, 0, _size / 2, 0);
		ofDrawLine(0, -_size / 2, 0, _size / 2);
		ofPopMatrix();
	}


	void updateCamera() {
		int camValue = 200;
		float camRotationSpeed = currentFrame / 360;
		ezCam.setPosition(camValue * sin(camRotationSpeed), camValue * cos(camRotationSpeed), camValue);
		ezCam.lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
	}

	void readyForDraw() {
		ofBackground(10);
		ofSetColor(255);
	}

	void createMesh() {
		int cols = 20;
		int rows = 20;
		int size = 8;
		int count = 0;
		for (int col = 0; col < cols; col++) {
			for (int row = 0; row < rows; row++) {
				float positionZ = myArr[count+300].y*0.8;
				std::cout << positionZ << std::endl;
				positionZ += ofMap(ofNoise(float(col)/2, float(row)/2), 0, 1, 0, 10);
				std::cout << "+noise"<<positionZ << std::endl;
				meshCreate.addVertex(glm::vec3(col*size - cols*size / 2, row*size - rows*size / 2,positionZ));
				count+=1;
			}
		}

		for (int x = 0; x < cols - 1; x++) {
			for (int y = 0; y < rows - 1; y++) {
				meshCreate.addIndex(x + y * rows);
				meshCreate.addIndex((x + 1) + y * rows);
				meshCreate.addIndex(x + (y + 1) * cols);
				meshCreate.addIndex((x + 1) + y * cols);
				meshCreate.addIndex((x + 1) + (y + 1) * rows);
				meshCreate.addIndex(x + (y + 1) * rows);
			}
		}

		createEnd = true;
		/*
		string name;
		if (currentFrame < 10) {
			name = "000"+ofToString(currentFrame);
		}
		else if (currentFrame < 100) {
			name = "00" + ofToString(currentFrame);
		}
		else if (currentFrame < 1000) {
			name = "0" + ofToString(currentFrame);
		}
		else {
			name = ofToString(currentFrame);
		}
		string fileName = "./screenShotForMovie/" + name + ".png";
		imgToSave.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		imgToSave.save(fileName, OF_IMAGE_QUALITY_BEST);
		*/
	}




	void saveImage() {
		string fileName = "./screenShot/" + ofToString(ofGetMonth()) + ofToString(ofGetDay()) + ofToString(ofGetHours()) + ofToString(ofGetMinutes()) + ofToString(ofGetSeconds()) + ".png";
		imgToSave.grabScreen(0,0,ofGetWidth(), ofGetHeight());
		imgToSave.save(fileName, OF_IMAGE_QUALITY_BEST);
		std::cout << "img : " + fileName + " -exported" << std::endl;
	}

	void saveFBOtoImage() {
		string fileName = "../EXPORTED/screenShots/" + ofToString(ofGetMonth()) + ofToString(ofGetDay()) + ofToString(ofGetHours()) + ofToString(ofGetMinutes()) + ofToString(ofGetSeconds()) + ".png";
		fbo.readToPixels(pixels);
		imgToSave.setFromPixels(pixels);
		imgToSave.save(fileName, OF_IMAGE_QUALITY_BEST);
		std::cout << "img : " + fileName + " -exported" << std::endl;
	}

	void keyPressed(int key) {
		if (key == 's') {
			saveImage();
		}
	}
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int _x, int _y, int _button) {
	}
	void mousePressed(int _x, int _y, int _button) {
		IsUpdateCamera = false;
	}
	void mouseReleased(int _x, int _y, int _button) {
		IsUpdateCamera = true;
	}
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h) {
	}
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


};
