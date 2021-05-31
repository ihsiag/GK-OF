#pragma once

#include "ofMain.h"

#include "ofxAssimpModelLoader.h"
#include "ofEasyCam.h"


class ofApp : public ofBaseApp{

	public:
		ofxAssimpModelLoader can;
		ofEasyCam cam;

		void setup() {
			ofSetBackgroundColor(0, 0, 0);
			can.loadModel("LIXILEYE_can_obj.obj", 10);
		}
		//void update();
		void draw(){
			ofPushMatrix();
			ofTranslate(ofGetWidth() / 2, ofGetHeight() / 4*3);
			can.drawWireframe();
			
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
