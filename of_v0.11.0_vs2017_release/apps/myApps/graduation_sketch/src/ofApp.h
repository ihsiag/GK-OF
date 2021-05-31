#pragma once

#include "ofMain.h"

#include "ofxAssimpModelLoader.h"
#include "ofEasyCam.h"


class ofApp : public ofBaseApp{

	public:
		//-----------IMPORT
		ofxAssimpModelLoader can;
		ofTrueTypeFont font;
		ofShader shader;
		ofEasyCam cam;

		//-----------GLOBAL
		float currentFrame = 0;
		int fontSize = 10;
		int uiNum = 10;

		//-----------STRUCTURE
		void setup() {
			std::cout << "setting up" << endl;
			
			ofSetBackgroundColor(0, 0, 0);

			//3D
			can.loadModel("3D/LIXILEYE_can_obj.obj", 10);
			
			//font
			ofTrueTypeFont::setGlobalDpi(72);
			font.load("font/SourceCodePro-Light.ttf", fontSize);
			font.setLineHeight(fontSize);
			font.setLetterSpacing(1.0);
			
			//shader
			//shader.load("shader/shader.vert", "shader/shader.frag");

		}
		//void update();
		
		void draw(){
			
			ofPushMatrix();
			shader.begin();
			ofTranslate(ofGetWidth() / 2, ofGetHeight() / 5 * 4);
			ofRotateY(currentFrame / 10);
			ofSetColor(180);
			can.drawFaces();
			ofSetColor(255);
			can.drawWireframe();
			ofSetColor(0, 255, 0);
			//can.drawVertices();
			shader.end();
			ofPopMatrix();

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
