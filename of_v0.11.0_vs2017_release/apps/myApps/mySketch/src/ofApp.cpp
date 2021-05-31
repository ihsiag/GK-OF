#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	circleSize = 50;
	box2d.init();
	box2d.setFPS(15);
	box2d.setGravity(0, 0);
	ofBackground(0, 0, 0);
	box2d.createBounds(0, 0, ofGetWidth(), ofGetHeight());

}

//--------------------------------------------------------------
void ofApp::update(){
	box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 150, 150);
	for (int i = 0; i < circles.size(); i++) {
		circles[i].get()->draw();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	ofPtr<ofxBox2dCircle> circle = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
	circle.get()->setPhysics(1.0, 0.5, 0.1); //density, bounce, friction
	circle.get()->setup(box2d.getWorld(), mouseX, mouseY, circleSize);
	circles.push_back(circle);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
