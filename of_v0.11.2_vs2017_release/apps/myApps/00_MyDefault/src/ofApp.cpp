#include "ofApp.h"


void ofApp::setup(){
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);
    gk.setGUI(gui);
    resetCamera();
}


void ofApp::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
}


void ofApp::draw(){
    cam.begin();
    gk.draw3DAxis();
    cam.end();
    gk.drawGrid();
}
//-----------FOR-LIB-----------//


//-----------THIS-TIME-FUNCS-----------//
void ofApp::resetCamera() {
    cam.setDistance(14);
    cam.enableOrtho();
    cam.setPosition(glm::vec3(0, 0, 500));
    cam.lookAt(ofVec3f(0, 0, 0));
}

//-----------EVENT-----------//
