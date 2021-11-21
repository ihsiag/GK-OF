#include "ofApp.h"


void ofApp::setup(){
    mf.setup(&ssGlobalLog);
    mf.setCam(&cam);
    mf.setGUI(gui);
}


void ofApp::update(){
    mf.defaultUpdate(&cam, &currentFrame, &time);
}


void ofApp::draw(){

}
//-----------FOR-LIB-----------//


//-----------THIS-TIME-FUNCS-----------//
void ofApp::resetCamera() {
    
}

//-----------EVENT-----------//
