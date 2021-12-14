#include "ofApp.h"


void ofApp::setup(){
    //-----------DEFAULT-----------//
    initParam();
    initGKSet();
    resetCamera();

    //-----------LOADING-----------//
    loadMeshes();
    
    if (meshes.size() < 16) {
        for (int i = 0; i < 16; i++) {
            setupSmallScreen(i);
        }
    }
    else {
        for (int i = 0; i < meshes.size(); i++) {
            setupSmallScreen(i);
        }
    }

}


void ofApp::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
}


void ofApp::draw(){
    cam.begin();
    //-----------MAIN-LAYER-----------//
    ofPushMatrix();
    ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
    drawSmallScreens();
    ofPopMatrix();
    cam.end();
    //-----------INFO-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;
    createInfo(ssInstruct, ssProgramInfo, ssDebug);


    //-----------FRONT-LAYER-----------//
    gk.drawGrid();
    gk.drawInfo(ssInstruct, 1);
    gk.drawInfo(ssProgramInfo, 2);
    gk.drawInfo(ssDebug, 5);
    gk.drawInfo(ssGlobalLog, 6);
}


//-----------FOR-LIB-----------//

void ofApp::initParam(){
    scrollUp = false;
    scrollDown = false;
}

void ofApp::initGKSet() {
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);
    gk.setGUI(gui, 13);
}

void ofApp::resetCamera() {
    cam.enableOrtho();
    cam.setPosition(glm::vec3(0, 0, 500));
    cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
    cam.disableMouseInput();
}

void ofApp::scrollCamera(const int& _scrollY) {
    int scrollScale = 30;
    if (cam.getPosition().y > -1) {
        cam.move(0, -1 * _scrollY * scrollScale, 0);
    }
    if (cam.getPosition().y < 0) {
        cam.setPosition(cam.getPosition().x, 0, cam.getPosition().z);
    }
}

void ofApp::loadMeshes() {
    string _dirName = "./meshExport/";
    ofDirectory _dir(_dirName);
    _dir.allowExt("ply");//only show {}file ex)png,mp3,css
    _dir.sort();
    _dir.listDir();
    for (int i = 0; i < _dir.size(); i++) {
        ofMesh _mesh;
        _mesh.load(_dir.getPath(i));
        meshes.push_back(_mesh);
        meshNames.push_back(_dir.getPath(i));
    }
    cout << meshes.size() << endl;
}

void ofApp::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
    //-----------INFO-----------//--later put into update func.

    _ssInstruct << "INSTRUCTIONS: " << endl;
    _ssInstruct << "> DEBUG              - H" << endl;
    _ssInstruct << "> ROTATE CAMERA      - RIGHT-BUTTON" << endl;
    _ssInstruct << "> MOVE CAMERA        - SHIFT + RIGHT-BUTTON" << endl;
    _ssInstruct << "> RESET CAMERA       - R" << endl;
    _ssInstruct << "> SAVE IMG           - S" << endl;
    _ssInstruct << "> SAVE SELECTED MESH - M" << endl;
    _ssInstruct << "> CLEAR GLOBAL LOG   - L" << endl;


    _ssProgramInfo << "PROGRAM: " << "EPHEMERAL-TMP" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    _ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;


    _ssDebug << "MOUSE POS" << ofGetMouseX() << ", " << ofGetMouseY() << endl;

}

void ofApp::setupSmallScreen(const int& _index) {
    Class_SmallScreen _smallScreen;
    glm::vec2 _pos = gk.getPosLayout4x4Inverse(_index);
    glm::vec2 _size = glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.25);
    if(_index<meshes.size()){ 
        _smallScreen.setup(&cam,_pos, _size, &meshes[_index],&meshNames[_index]);
    }
    else {
        _smallScreen.setup(&cam,_pos, _size);
    }
    smallScreens.push_back(_smallScreen);
}

void ofApp::resizeSmallScreen(const int& _index) {
    glm::vec2 _pos = gk.getPosLayout4x4Inverse(_index);
    glm::vec2 _size = glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.25);
    smallScreens[_index].onWindowResized(_pos,_size);
}

void ofApp::drawSmallScreens() {
    for (auto& smallScreen : smallScreens) {
        if (smallScreen.pos.y > cam.getPosition().y - smallScreen.size.y && smallScreen.pos.y < cam.getPosition().y + ofGetHeight()) {
            smallScreen.run();
        }
    }
}

//-----------THIS-TIME-FUNCS-----------//




//-----------EVENT-----------//
