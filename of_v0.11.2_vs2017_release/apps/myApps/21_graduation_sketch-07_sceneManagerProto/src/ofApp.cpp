#include "ofApp.h"

std::shared_ptr<ofApp> ofApp::instance;


void ofApp::addGKScene(GKScene* _gkScene) {
		gkScenes.push_back(_gkScene);
}


//--------------------------------------------------------------
void ofApp::setup(){
	currentSceneIndex = 0;
	for (GKScene* gs : gkScenes) {
		glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		//ofPushStyle();
		gs->setup();
		//ofPopStyle();
		glPopAttrib();
		glPopClientAttrib();
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	GKScene* gs = gkScenes[currentSceneIndex];
	gs->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	GKScene* gs = gkScenes[currentSceneIndex];
	gs->draw();
}

//--------------------------------------------------------------
//void ofApp::keyPressed(int key){
//
//}

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
