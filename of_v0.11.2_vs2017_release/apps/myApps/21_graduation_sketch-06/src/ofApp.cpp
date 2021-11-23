#include "ofApp.h"


void ofApp::setup(){
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);
    gk.setGUI(gui);
    //glEnable(GL_DEPTH_TEST);
    createGUI();
    resetCamera();
    loadMesh("./selectedMesh/",&importedMesh);
    transformInfo.setPosition(0, 0, 0);
}


void ofApp::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
}


void ofApp::draw(){
    cam.begin();
    //-----------MAIN-LAYER-----------//
    gk.draw3DAxis();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glLineWidth(0.5);
    if(checkedMesh.hasVertices()) {
        glColor3f(0.5, 0.5, 0.5);
        checkedMesh.draw();
        glColor3f(0.8, 0.8, 0.8);
        checkedMesh.drawWireframe();
    }else
    if (importedMesh.hasVertices()) {
        ofPushMatrix();       
        ofRotateX(rotationSlider.get().x);
        ofRotateY(rotationSlider.get().y);
        ofRotateZ(rotationSlider.get().z);
        transformInfo.rotateAroundDeg(rotationSlider.get().x,glm::vec3(1,0,0),glm::vec3(0));
        transformInfo.rotateAroundDeg(rotationSlider.get().y, glm::vec3(0, 1, 0), glm::vec3(0));
        transformInfo.rotateAroundDeg(rotationSlider.get().z, glm::vec3(0, 0, 1), glm::vec3(0));
        
        glColor3f(0.5, 0, 0);
        importedMesh.draw();
        glColor3f(0.8, 0, 0);
        importedMesh.drawWireframe();
        ofPopMatrix();
    }
    glDisable(GL_CULL_FACE);
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
    gui.draw();
}
//-----------FOR-LIB-----------//


//-----------THIS-TIME-FUNCS-----------//
void ofApp::resetCamera() {
    cam.setDistance(14);
    //cam.enableOrtho();
    cam.setPosition(glm::vec3(180, -180, 180));
    cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0),glm::vec3(0,1,0));
}

void ofApp::loadMesh(const string& _dirName,ofMesh* _mesh) {
    ofDirectory _dir(_dirName);
    
    _dir.allowExt("ply");//only show {}file ex)png,mp3,css
    _dir.sort();
    _dir.listDir();
    ssGlobalLog << _dir.size() << endl;
    if (_dir.size() > 0) {
        _mesh->load(_dir.getPath(_dir.size()-1));
    }
}

void ofApp::createGUI() {
    gui.add(rotationSlider.set("ROTATION", glm::vec3(0), glm::vec3(-180), glm::vec3(180)));
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

void ofApp::resetMeshMatrix(ofMesh* _mesh) {
    /*
    auto mat = pos.getGlobalTransformMatrix();
    for (auto& v : mesh.getVertices()) {
        v = glm::vec3(mat * glm::vec4(v, 1));
    }
    */
    auto mat2 = transformInfo.getOrientationQuat();
    for (auto& v : _mesh->getNormals()) {
        v = glm::vec3((mat2 * glm::vec4(v, 1)));
    }
    transformInfo.resetTransform();
}
//-----------EVENT-----------//
