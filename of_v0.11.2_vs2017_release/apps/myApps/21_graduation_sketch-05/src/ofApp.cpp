#include "ofApp.h"


void ofApp::setup(){
    //-----------DEFAULT-----------//
    gk.setup(&ssGlobalLog);
    //gk.setCam(&cam);
    gk.setGUI(gui);
    //resetCamera();

    //-----------LOADING-----------//
    loadMeshes();
    setupFbos();

}


void ofApp::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
    runFbos();
}


void ofApp::draw(){
    drawFbos();

    //-----------FRONT-LAYER-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;
    createInfo(ssInstruct, ssProgramInfo, ssDebug);


    //-----------FRONT-LAYER-----------//
    gk.drawGrid();
    gk.drawInfo(ssInstruct, 0);
    gk.drawInfo(ssProgramInfo, 1);
    gk.drawInfo(ssDebug, 3);
    gk.drawInfo(ssGlobalLog, 4);

    //gui.draw();
}


//-----------FOR-LIB-----------//
void ofApp::setupFbos() {
    sizeFbo = glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.25);
    numFbos = 16;
    for (int i=0; i < numFbos; i++) {
        setupFbo(i);
    }
}

void ofApp::resizeFbos() {
    sizeFbo = glm::vec2(ofGetWidth() * 0.25, ofGetHeight() * 0.25);
    for (int i = 0; i < numFbos; i++) {
        resizeFbo(i);
    }
}

void ofApp::runFbos() {
    for (int i = 0; i < numFbos; i++) {
        runFbo(i);
    }
}

void ofApp::drawFbos() {
    for (int i = 0; i < numFbos; i++) {
        drawFbo(i);
    }
}

void ofApp::setupFbo(const int& _index) {
    ofFbo _fbo;
    _fbo.allocate(sizeFbo.x, sizeFbo.y);
    fbos.push_back(_fbo);
}



void ofApp::runFbo(const int& _index) {
    fbos[_index].begin();
    ofClear(0);
    ofColor _col = ofColor(ofRandom(255));
    ofSetColor(_col);
    ofFill();
    ofDrawRectangle(0, 0, fbos[_index].getWidth(), fbos[_index].getHeight());
    
    cam.begin();
    gk.draw3DAxis();
    cam.end();
    
    fbos[_index].end();
}

void ofApp::drawFbo(const int& _index) {
    fbos[_index].draw(gk.getPosLayout4x4(_index));
}


void ofApp::resizeFbo(const int& _index) {
    for (int i = 0; i < numFbos; i++) {
        fbos[_index].clear();
        if (!fbos[_index].isAllocated()) {
            fbos[_index].allocate(sizeFbo.x, sizeFbo.y);
        }
    }
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
