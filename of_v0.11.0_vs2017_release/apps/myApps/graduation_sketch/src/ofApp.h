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

		static const int numControllers = 16;
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
			ofVec2f controllerAreaNW = ofVec2f(ofGetWidth() * 3 / 4, ofGetHeight() * 1 / 4);
			ofVec2f controllerAreaSE = ofVec2f(ofGetWidth(), ofGetHeight() * 3 / 4);
			
			controllers[0].init(0,"shaderAlpha", 0, 1, controllerAreaNW,controllerAreaSE);
			controllers[1].init(1, "nothing", 0, 100, controllerAreaNW, controllerAreaSE);
			controllers[2].init(2, "nothing", 0, 45, controllerAreaNW, controllerAreaSE);
			controllers[3].init(3, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[4].init(4, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[5].init(5, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[6].init(6, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[7].init(7, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[8].init(8, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[9].init(9, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[10].init(10, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[11].init(11, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[12].init(12, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[13].init(13, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[14].init(14, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);
			controllers[15].init(15, "nothing", 0, 50, controllerAreaNW, controllerAreaSE);

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
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			//glEnable(GL_DEPTH_TEST);
			shader.begin();
			
			//modelMatrix
			ofMatrix4x4 modelMatrix;
			modelMatrix.translate(0, 0, 0);
			modelMatrix.rotate(currentFrame / 10, 0, 1, 0);
			modelMatrix.rotate(25,1, 0,0);
			modelMatrix.scale(4.0, 4.0, 4.0);

			ofMatrix4x4 viewMatrix;
			viewMatrix = ofGetCurrentViewMatrix();

			ofMatrix4x4 projectionMatrix;
			projectionMatrix = cam.getProjectionMatrix();

			ofMatrix4x4 modelViewProjectionMatrix;
			modelViewProjectionMatrix = modelMatrix * viewMatrix * projectionMatrix;
			
			//uniforms
			shader.setUniform1f("alpha", controllers[0].bridgeValue());
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
			//controller-begin
			for (int i = 0; i < numControllers; i++) {
				controllers[i].mouseIsDragged = true;
				controllers[i].mouseX = _x;
				controllers[i].mouseY = _y;
			}
			//controller-end
		}
		void mousePressed(int _x, int _y, int _button){
		}
		void mouseReleased(int _x, int _y, int _button) {
			//controller-begin
			for (int i = 0; i < numControllers; i++) {
				controllers[i].mouseIsDragged = false;
			}
			//controller-end
		}
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h) {
			
			//controller-begin
			ofVec2f controllerAreaNW = ofVec2f(ofGetWidth() * 3 / 4, ofGetHeight() * 1 / 4);
			ofVec2f controllerAreaSE = ofVec2f(ofGetWidth(), ofGetHeight() * 3 / 4);
			for (int i = 0; i < numControllers; i++) {
				controllers[i].windowResizeEvent(i,controllerAreaNW,controllerAreaSE);
			}
			//controller-end
			
		}
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		
};
