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
    //-----------INIT-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;

    //-----------PROCESS-----------//

    //-----------3D-LAYER-----------//
    cam.begin();
    gk.draw3DAxis();
    cam.end();
    gk.drawGrid();

    //-----------2D-LAYER-----------//

    //-----------INFO-----------//
    createInfo(ssInstruct, ssProgramInfo, ssDebug);

    //-----------FRONT-LAYER-----------//
    gk.drawGrid();
    gk.drawInfo(ssInstruct, 0);
    gk.drawInfo(ssProgramInfo, 1);
    gk.drawInfo(ssDebug, 4);
    gk.drawInfo(ssGlobalLog, 5);
}
//-----------FOR-LIB-----------//

//-----------THIS-TIME-UTILS-----------//
void ofApp::resetCamera() {
    cam.setDistance(14);
    cam.enableOrtho();
    cam.setPosition(glm::vec3(0, 0, 500));
    cam.lookAt(ofVec3f(0, 0, 0));
}

void ofApp::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
    //-----------INFO-----------//--later put into update func.
    _ssInstruct << "INSTRUCTIONS: " << endl;
    _ssInstruct << "> DEBUG               - H" << endl;
    _ssInstruct << "> FULL-SCREEN         - F" << endl;
    _ssInstruct << "> ROTATE CAMERA       - RIGHT-BUTTON" << endl;
    _ssInstruct << "> MOVE CAMERA         - SHIFT + RIGHT-BUTTON" << endl;
    _ssInstruct << "> RESET CAMERA        - R" << endl;
    _ssInstruct << "> UPDATE MESH         - U" << endl;
    _ssInstruct << "> HIDE MAIN-MESH      - 1" << endl;
    _ssInstruct << "> HIDE ADDED-MESH     - 2" << endl;
    _ssInstruct << "> HIDE FLAT-SRF       - 3" << endl;
    _ssInstruct << "> BACK                - Z" << endl;
    _ssInstruct << "> SAVE IMG            - S" << endl;
    _ssInstruct << "> SAVE GENERATED-MESH - M" << endl;
    _ssInstruct << "> CLEAR GLOBAL LOG    - L" << endl;

    _ssProgramInfo << "PROGRAM: " << "EPHEMERAL-TMP" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    _ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;
    _ssProgramInfo << "CAMERA LOOK DIR: " << cam.getLookAtDir() << endl;

    _ssDebug << "DEBUG-STATE: " << bDebug << endl;
    _ssDebug << "CURRENT MY-PLANE NUM: " << gkPlanes.size() << endl;
    _ssDebug << "HIDE MAIN-MESH: " << bHideMainMesh << endl;
    _ssDebug << "HIDE ADDED-MESH: " << bHideAddedMesh << endl;
    _ssDebug << "HIDE FLAT-SRF: " << bHideGKPlane << endl;
}

//-----------THIS-TIME-FUNCS-----------//

//-----------DEBUG-FUNC-----------//

//-----------EVENT-----------//
