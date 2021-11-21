#include "ofApp.h"


void ofApp::setup(){
    mf.setup(&ssGlobalLog);
    mf.setCam(&cam);
    resetCamera();
    mf.setGUI(gui);
}


void ofApp::update(){
    mf.defaultUpdate(&cam, &currentFrame, &time);
}


void ofApp::draw(){
    cam.begin();
    mf.draw3DAxis();
    cam.end();
}
//-----------FOR-LIB-----------//


//-----------THIS-TIME-FUNCS-----------//
void ofApp::resetCamera() {
    cam.setDistance(14);
    cam.enableOrtho();
    cam.setPosition(glm::vec3(0,0,500));
    cam.lookAt(ofVec3f(0,0,0));
}

//-----------EVENT-----------//
