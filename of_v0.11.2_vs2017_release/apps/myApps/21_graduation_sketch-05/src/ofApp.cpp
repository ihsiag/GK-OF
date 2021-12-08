#include "ofApp.h"


void ofApp::setup(){
    //-----------DEFAULT-----------//
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);
    gk.setGUI(gui,13);
    //glEnable(GL_DEPTH_TEST);
    resetCamera();

    //-----------LOADING-----------//
    loadMeshes();
    numSmallScreens = 16;
    for (int i = 0; i < numSmallScreens; i++) {
        setupSmallScreen(i);
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
    for (auto& smallScreen : smallScreens) {
        smallScreen.run();
    }   
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

    //gui.draw();
}


//-----------FOR-LIB-----------//

void ofApp::setupSmallScreen(const int& _index) {
    Class_SmallScreen _smallScreen;
    glm::vec2 _pos = gk.getPosLayout4x4(_index);
    glm::vec2 _size = glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.25);
    if(_index<meshes.size()){ 
        _smallScreen.setup(_pos, _size, &meshes[_index],&meshNames[_index]);
    }
    else {
        _smallScreen.setup(_pos, _size);
    }
    smallScreens.push_back(_smallScreen);
}

void ofApp::resizeSmallScreen(const int& _index) {
    glm::vec2 _pos = gk.getPosLayout4x4(_index);
    glm::vec2 _size = glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.25);
    smallScreens[_index].onWindowResized(_pos,_size);
}

//-----------THIS-TIME-FUNCS-----------//
void ofApp::resetCamera() {
    cam.enableOrtho();
    cam.setPosition(glm::vec3(0,0,500));
    cam.setVFlip(true);
    cam.lookAt(ofVec3f(0,0,0),glm::vec3(0,-1,0));
    cam.disableMouseInput();
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

    /*
    _ssDebug << "AMOUT-CAN: " << ofToString(models.size(), 0) << endl;
    _ssDebug << "AMOUT-CRASHER: " << ofToString(rigidBodies.size(), 0) << endl;
    for (int i = 0; i < models.size(); i++) {
        _ssDebug << "MODEL ID: " << ofToString(i, 3) << " -> POSITION: " << models[i]->getPosition() << endl;
    }
    _ssDebug << "MOUSE WORLD POS: " << mouseOnWorldPlane << endl;
    _ssDebug << "MOUSE PICK POS: " << mousePickPos << endl;
    */
}

//-----------EVENT-----------//
