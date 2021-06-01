#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofEasyCam.h"
#include "ofCamera.h"


class ofApp : public ofBaseApp{

	public:
		//-----------IMPORT
		ofxAssimpModelLoader can;
		ofTrueTypeFont font;
		ofShader shader;
		ofCamera cam;

		//-----------GLOBAL
		bool initDone = false;
		float currentFrame = 0;
		int fontSize = 10;
		int uiNum = 10;

		static const int numVertexIndices = 20;
		int vertexIndices[numVertexIndices];

		//-----------STRUCTURE
		void setup() {
			std::cout << "setting up" << endl;
			
			ofSetBackgroundColor(0, 0, 0);

			//camera

			//cam.setAspectRatio(ofGetHeight()/ ofGetWidth());
			cam.setPosition(0, 0, 500);
			//cam.setFov(10);
			cam.enableOrtho();
			//3D
			can.loadModel("3D/LIXILEYE_can_obj.obj", 8);
			
			//font
			ofTrueTypeFont::setGlobalDpi(72);
			font.load("font/SourceCodePro-Light.ttf", fontSize);
			font.setLineHeight(fontSize);
			font.setLetterSpacing(1.0);
			
			//shader
			shader.load("shader/shader.vert", "shader/shader.frag");
			if (shader.isLoaded()) {
				cout << "shader loaded" << endl;
			}

		}
		//void update();
		
		void draw(){
			

			cam.begin();
			shader.begin();
			
			shader.setUniform1f("time",ofGetElapsedTimef());
			shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
				
			ofRotateX(180+25);
			ofRotateY(currentFrame / 10);
			ofSetColor(180);
			can.drawFaces();
			ofSetColor(255);
			//glEnable(GL_LINE_STIPPLE);
			//glLineStipple(1, 0x0101);
			can.drawWireframe(); 
			//glDisable(GL_LINE_STIPPLE);
			ofSetColor( 255,0, 0);
			//can.drawVertices();
			shader.end();
			cam.end();

			

			makeGrid();
			for (int i = 0; i < uiNum; i++) {
				ofVec2f uiPos = ofVec2f(ofGetWidth() / 4 * 3, ofGetHeight() / 4 + i * fontSize * 3);
				ui(uiPos);
			}
			
			
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
					vertexIndices[i] = ofRandom(can.getNumMeshes());
				}
				initDone = !initDone;
			}
			else {				
			}	
		}



		void ui(ofVec2f _pos) {
			string _posToPrint = "X:" + ofToString(_pos.x) + " , " + "Y:" + ofToString(_pos.y);
			ofRectangle _bb = font.getStringBoundingBox(_posToPrint, 0, 0);
			font.drawString(_posToPrint,_pos.x + 50,_pos.y);
		
		}

		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		
};
