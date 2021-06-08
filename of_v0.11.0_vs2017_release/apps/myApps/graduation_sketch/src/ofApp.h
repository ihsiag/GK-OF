#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofEasyCam.h"
#include "ofCamera.h"
//
#include "myController.h"


class ofApp : public ofBaseApp{

	public:
		//-----------IMPORT
		ofCamera cam;
		ofEasyCam ezCam;
		ofTrueTypeFont font;
		ofShader shader;
		myController controller;
		
		ofxAssimpModelLoader model;
		ofVboMesh vboMesh;

		//-----------GLOBAL
		float time;
		bool mouseIsPressed = false;
		bool mouseIsDragged = false;


		bool initDone = false;
		float currentFrame = 0.0;
		int fontSize = 10;
		int uiNum = 10;

		static const int numVertexIndices = 20;
		int vertexIndices[numVertexIndices];

		//-----------STRUCTURE
		void setup() {
			std::cout << "setting up" << std::endl;
			
			//basic
			ofSetBackgroundAuto(true);
			ofSetBackgroundColor(0, 0, 0);
			ofEnableAlphaBlending();
			//ofEnableBlendMode(); //OF_BLENDMODE_DISABLED, OF_BLENDMODE_ALPHA, OF_BLENDMODE_ADD, OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_SCREEN
			ofSetFrameRate(60);

			//camera

			int CAM_Z = 500;
			cam.setNearClip(0.1);
			cam.setFarClip(100000);
			cam.setPosition(0, 0, CAM_Z);
			cam.enableOrtho();
			//cam.setFov(15);
			//cam.disableMouseInput();
			
			
			//3D
			model.loadModel("3D/LIXILEYE_can_obj.obj", 8);
			
			//font
			ofTrueTypeFont::setGlobalDpi(72);
			font.load("font/SourceCodePro-Light.ttf", fontSize);
			font.setLineHeight(fontSize);
			font.setLetterSpacing(1.0);
			
			//shader
			shader.load("shader/shader.vert", "shader/shader.frag");
			if (shader.isLoaded()) {
				std::cout << "shader loaded" << std::endl;
			}
			else {
				std::cout << "shader loading failed" << std::endl;
			}

			//controller
			ofVec2f controllerPos = ofVec2f(ofGetWidth() / 4 * 3, ofGetHeight() / 4);
			controller.init(controllerPos.x, controllerPos.y);

		}
		void update() {
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
			time = ofGetElapsedTimef();
		}
		
		void draw(){
			
			ofEnableDepthTest();
			cam.begin();

			//glEnable(GL_BLEND);
			//glFrontFace(GL_CW);
			//glEnable(GL_CULL_FACE);
			//glCullFace(GL_BACK);
			//glEnable(GL_DEPTH_TEST);
			shader.begin();
			
			//modelMatrix
			ofMatrix4x4 modelMatrix;
			modelMatrix.translate(0, 0, 0);
			modelMatrix.rotate(0.0,0.0,0.0,1.0);
			modelMatrix.scale(4.0, 4.0, 4.0);

			// view Matrix
			ofMatrix4x4 viewMatrix;
			viewMatrix = ofGetCurrentViewMatrix();

			// projection Matrix
			ofMatrix4x4 projectionMatrix;
			projectionMatrix = cam.getProjectionMatrix();

			// mvp Matrix
			ofMatrix4x4 modelViewProjectionMatrix;
			modelViewProjectionMatrix = modelMatrix * viewMatrix * projectionMatrix;
			
			//uniforms
			shader.setUniform1f("alpha", controller.bridgeValue());
			shader.setUniform1f("time", time);
			shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
			shader.setUniformMatrix4f("projectionMatrix", projectionMatrix);
			shader.setUniformMatrix4f("modelViewProjectionMatrix", modelViewProjectionMatrix);
			
			model.drawFaces();
			//model.drawWireframe();
			shader.end();
			cam.end();
			ofDisableDepthTest();

			makeGrid();
			for (int i = 0; i < uiNum; i++) {
				ofVec2f uiPos = ofVec2f(ofGetWidth() / 4 * 3, ofGetHeight() / 4 + i * fontSize * 3);
				ui(uiPos);
			}
			showControllers();
			currentFrame++;
		}

		//-----------CUSTOM-FUNCS
		void makeGrid() {
			ofNoFill();
			ofSetColor(50, 50, 50);
			ofDrawLine(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() / 2);
			ofDrawLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());

			ofPushMatrix();
			ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
			for (int y = -1; y < 2; y++) {
				for (int x = -1; x < 2; x++) {
					if (y != 0) {
						if (x != 0) {
							makeCross(x * ofGetWidth() / 4, y * ofGetHeight() / 4, 10);
						}
					}
				}
			}
			ofPopMatrix();
		}

		void makeCross(int _x, int _y, int _size) {
			ofSetColor(255);
			ofPushMatrix();
			ofTranslate(_x, _y);
			ofDrawLine(-_size / 2, 0, _size / 2, 0);
			ofDrawLine(0, -_size / 2, 0, _size / 2);
			ofPopMatrix();
		}


		void makeNotation() {
			if (!initDone) {
				for (int i = 0; i < numVertexIndices; i++) {
					vertexIndices[i] = ofRandom(model.getNumMeshes());
				}
				initDone = !initDone;
			}
			else {				
			}	
		}



		void ui(ofVec2f _pos) {
			string _posToPrint = "X:" + ofToString(_pos.x) + " , " + "Y:" + ofToString(_pos.y);
			ofRectangle _bb = font.getStringBoundingBox(_posToPrint, 0, 0);
			font.drawString(ofToString(controller.bridgeValue()),_pos.x + 50,_pos.y);
		}

		void showControllers() {
			controller.update();
			controller.show();
		}

		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int _x, int _y, int _button) {
			controller.mouseIsDragged = true;
			controller.mouseX = _x;
			controller.mouseY = _y;
		}
		void mousePressed(int _x, int _y, int _button){
			controller.mouseIsPressed = true;
			controller.mouseX = _x;
			controller.mouseY = _y;			
		}
		void mouseReleased(int _x, int _y, int _button) {
			controller.mouseIsPressed = false;
			controller.mouseIsDragged = false;
		}
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		
};
