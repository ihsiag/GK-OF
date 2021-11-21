#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofEasyCam.h"
#include "ofCamera.h"
#include "ofxGui.h"
#include "ofxPostProcessing.h"

//
#include "myController.h"


class ofApp : public ofBaseApp{

	public:
		//-----------IMPORT
		ofCamera cam;
		ofEasyCam ezCam;
		ofTrueTypeFont font;
		ofShader modelShader;
		ofShader postShader;
		ofxAssimpModelLoader model;
		ofVboMesh vboMesh;
		ofxPanel gui;
		ofxPostProcessing post;

		//-----------GLOBAL
		float time;
		float currentFrame = 0.0;
		int fontSize = 10;
		ofImage imgToSave;

		float tmpShaderScannerPosY;

		//-----------Sliders
		ofxFloatSlider modelShaderAlpha;
		ofxFloatSlider shaderScannerPosY;
		ofxFloatSlider modelShaderScannerWidth;
		ofxFloatSlider modelShaderColWhenBright;
		ofxFloatSlider modelShaderColWhenDark;




		//-----------STRUCTURE
		void setup() {
			std::cout << "setting up" << std::endl;

			//initParams
			tmpShaderScannerPosY = 100;

			//controller
			gui.setup();
			gui.add(modelShaderAlpha.setup("modelShaderAlpha", 1.00, 0.00, 1.00));
			gui.add(modelShaderScannerWidth.setup("modelShaderScannerWidth", 3.5, 30.00, 0.00));
			gui.add(modelShaderColWhenBright.setup("modelShaderColWhenBright", 0.75, 0.00, 1.00));
			gui.add(modelShaderColWhenDark.setup("modelShaderColWhenDark", 0.25, 0.00, 1.00));
			

			
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
			modelShader.load("shader/model.vert", "shader/model.frag");
			postShader.load("shader/post.vert", "shader/post.frag");

			//post
			post.init(ofGetWidth(), ofGetHeight());
			//post.createPass<GodRaysPass>();

		}

		void update() {
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
			time = ofGetElapsedTimef();
		}
		
		void draw(){
			

			ofEnableDepthTest();
			post.begin(cam);
			cam.begin();
			

			//glEnable(GL_BLEND);
			//glFrontFace(GL_CW);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			//glEnable(GL_DEPTH_TEST);
			modelShader.begin();
			
			//matrix
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
			modelShader.setUniform1f("alpha",modelShaderAlpha);
			modelShader.setUniform1f("time", time);
			modelShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
			modelShader.setUniformMatrix4f("modelViewProjectionMatrix", modelViewProjectionMatrix);
			modelShader.setUniform1f("scannerPosY", tmpShaderScannerPosY);
			modelShader.setUniform1f("scannerWidth", modelShaderScannerWidth);
			modelShader.setUniform1f("colWhenBright", modelShaderColWhenBright);
			modelShader.setUniform1f("colWhenDark", modelShaderColWhenDark);

			
			//draw model
			//model.drawFaces();
			model.drawWireframe();
			
			modelShader.end();
			cam.end();
			post.end();
			ofDisableDepthTest();
			
			makeGrid();
			gui.draw();
			drawScannerBar();
			currentFrame++;
			tmpShaderScannerPosY -= 0.5;
			if (tmpShaderScannerPosY < -100) {
				tmpShaderScannerPosY = 100;
			}
			


		}

		//-----------CUSTOM-FUNCS
		void makeGrid() {
			//
			ofNoFill();
			ofSetColor(50, 50, 50);
			ofDrawLine(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() / 2);
			ofDrawLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());

			//
			ofNoFill();
			ofSetColor(200);
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


		void makeNotation() {
		}

		void drawScannerBar() {
			ofTranslate(ofGetWidth() *3/ 4, ofGetHeight() / 4);
			ofVec2f SP = ofVec2f(0.0, 0.0);
			ofVec2f EP = ofVec2f(0.0, ofGetHeight()/2);
			ofNoFill();
			ofSetColor(255);
			ofDrawLine(SP, EP);

			float posY = ofMap(tmpShaderScannerPosY, 100, -100, 0, ofGetHeight() / 2);
			int _size = 10;
			SP = ofVec2f(-_size/2, posY);
			EP = ofVec2f(_size/2, posY);
			ofDrawLine(SP, EP);
		}

		void getBoundingBox() {

		}


		
		void keyPressed(int key) {
			if (key == 's') {
				imgToSave.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
				imgToSave.save("ofScreenShot.png");
			}
		}
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int _x, int _y, int _button) {
		}
		void mousePressed(int _x, int _y, int _button){
		}
		void mouseReleased(int _x, int _y, int _button) {
		}
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h) {			
		}
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		
};