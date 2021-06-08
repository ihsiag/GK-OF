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
		
		ofxAssimpModelLoader model;
		ofVboMesh vboMesh;

		//-----------GLOBAL
		float time;
		bool mouseIsDragged = false;


		bool initDone = false;
		float currentFrame = 0.0;
		int fontSize = 10;
		int uiNum = 10;

		static const int numControllers = 4;
		myController controllers[numControllers];

		static const int numVertexIndices = 20;
		int vertexIndices[numVertexIndices];

		//-----------STRUCTURE
		void setup() {
			std::cout << "setting up" << std::endl;

			//initParams

			
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
			for (int i = 0; i < numControllers; i++) {
				ofVec2f controllerPos = ofVec2f(ofGetWidth() / 4 * 3, ofGetHeight() / 4+30*i);
				controllers[i].init(controllerPos.x, controllerPos.y, "try");
			}
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
			modelMatrix.rotate(controllers[0].bridgeValue()*90,controllers[1].bridgeValue()*90, controllers[2].bridgeValue()*90,1.0);
			modelMatrix.scale(4.0, 4.0, 4.0);

			ofMatrix4x4 viewMatrix;
			viewMatrix = ofGetCurrentViewMatrix();

			ofMatrix4x4 projectionMatrix;
			projectionMatrix = cam.getProjectionMatrix();

			ofMatrix4x4 modelViewProjectionMatrix;
			modelViewProjectionMatrix = modelMatrix * viewMatrix * projectionMatrix;
			
			//uniforms
			shader.setUniform1f("alpha", controllers[3].bridgeValue());
			shader.setUniform1f("time", time);
			shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
			shader.setUniformMatrix4f("modelViewProjectionMatrix", modelViewProjectionMatrix);
			
			//draw model
			model.drawFaces();
			//model.drawWireframe();
			
			shader.end();
			cam.end();
			ofDisableDepthTest();

			makeGrid();
			for (int i = 0; i < numControllers; i++) {
				ofVec2f uiPos = ofVec2f(ofGetWidth() / 4 * 3, ofGetHeight() / 4 + i * fontSize * 3);
				ui(i,uiPos);
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



		void ui(int _index, ofVec2f _pos) {
			string _posToPrint = "X:" + ofToString(_pos.x) + " , " + "Y:" + ofToString(_pos.y);
			ofRectangle _bb = font.getStringBoundingBox(_posToPrint, 0, 0);
			font.drawString(ofToString(controllers[_index].bridgeValue()),_pos.x + 50,_pos.y);
		}

		void showControllers() {
			for (int i = 0; i < numControllers; i++) {
				controllers[i].update();
				controllers[i].show();
			}
		}

		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int _x, int _y, int _button) {
			for (int i = 0; i < numControllers; i++) {
				controllers[i].mouseIsDragged = true;
				controllers[i].mouseX = _x;
				controllers[i].mouseY = _y;
			}
		}
		void mousePressed(int _x, int _y, int _button){		
		}
		void mouseReleased(int _x, int _y, int _button) {
			for (int i = 0; i < numControllers; i++) {
				controllers[i].mouseIsDragged = false;
			}
		}
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		
};
