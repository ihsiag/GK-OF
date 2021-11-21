#include "ofApp.h"


void ofApp::setup(){
    //-----------DEFAULT-----------//
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);
    gk.setGUI(gui);
    resetCamera();

    //-----------LOADING-----------//
    loadMeshes();


}


void ofApp::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
}


void ofApp::draw(){
    cam.begin();
    gk.draw3DAxis();
    cam.end();
}
//-----------FOR-LIB-----------//
void ofApp::setupFbos() {
    sizeFbo = glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.25);
    for (int i; i < numFbos; i++) {
        setupFbo(i);
    }
}

void ofApp::setupFbo(const int& _index) {

}

void ofApp::runFbos() {
    for (int i; i < numFbos; i++) {
        runFbo(i);
    }
}

void ofApp::runFbo(const int& _index) {

}

//-----------THIS-TIME-FUNCS-----------//
void ofApp::resetCamera() {
    cam.setDistance(14);
    cam.enableOrtho();
    cam.setPosition(glm::vec3(0,0,500));
    cam.lookAt(ofVec3f(0,0,0));
}

void ofApp::loadMeshes() {
	string _dirName = "./meshExport/";
	ofDirectory _dir(_dirName);
	_dir.allowExt("ply");//only show {}file ex)png,mp3,css
	//_dir.sort();
	_dir.listDir();
	for (int i = 0; i < _dir.size(); i++) {
		ofMesh _mesh;
		_mesh.load(_dir.getPath(i));
		meshes.push_back(_mesh);
	}
}

//-----------EVENT-----------//
