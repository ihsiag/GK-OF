#include "ofApp.h"


void ofApp::setup(){
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);
    gk.setGUI(gui);
    createGUI();
    resetCamera();
    importMesh();

    modifyInfo = ofNode();
    modifyInfo.setPosition(0, 0, 0);
    bModified = false;
    bDebug = false;
    bHideMainMesh = false;
    bHideAddedMesh = true;// false;
    bHideMyPlane = true;// false;

    verticesPosHolder.reserve(3);
}

void ofApp::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void ofApp::draw(){
    //-----------INIT-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;

    //-----------PROCESS-----------//
    if (!bModified)modifyMesh();
    if (bModified)checkVerticesHolder();
    
    //-----------3D-LAYER-----------//
    cam.begin();  
    glEnable(GL_DEPTH_TEST);
    gk.draw3DAxis();
    gk.draw3DCADGrid(10, 50, glm::vec3(0, 1, 0), 1, glm::vec4(glm::vec3(0.3), 1)); 
    if (!bModified)draw3DBeforeModified();
    if (bModified)draw3DAfterModified();
    glDisable(GL_DEPTH_TEST);
    cam.end();
    
    //-----------2D-LAYER-----------//
    if (bModified)selectingVertexPos = getCurrentVertex(mainMesh, ssDebug);
    //-----------INFO-----------//
    createInfo(ssInstruct, ssProgramInfo, ssDebug);

    //-----------FRONT-LAYER-----------//
    gk.drawGrid();
    gk.drawInfo(ssInstruct, 1);
    gk.drawInfo(ssProgramInfo, 2);
    gk.drawInfo(ssDebug, 5);
    gk.drawInfo(ssGlobalLog, 6);
    gui.draw();
    drawCamPosition();
}

//-----------FOR-LIB-----------//
//addFace();

//-----------THIS-TIME-UTILS-----------//
void ofApp::resetCamera() {
    cam.setDistance(14);
    //cam.enableOrtho();
    cam.setPosition(glm::vec3(180, 180, 180));
    //cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0),glm::vec3(0,1,0));
}

void ofApp::drawCamPosition() {
    gk.setGraphGUI(14, glm::vec2(ofGetHeight() * 0.25), glm::vec2(10 * 50));
    gk.drawEachDataOnGraphGUI(14, glm::vec2(ofGetHeight() * 0.25), glm::vec2(10 * 50 *2),cam.getPosition(),glm::vec3(0,1,0));
}

void ofApp::createGUI() {
    gui.add(rotationSlider.set("ROTATION", glm::vec3(0), glm::vec3(-PI), glm::vec3(PI)));
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
    _ssDebug << "CURRENT MY-PLANE NUM: " << myPlanes.size() << endl;
    _ssDebug << "HIDE MAIN-MESH: " << bHideMainMesh << endl;
    _ssDebug << "HIDE ADDED-MESH: " << bHideAddedMesh << endl;
    _ssDebug << "HIDE FLAT-SRF: " << bHideMyPlane << endl;
}

void ofApp::loadLatestMesh(const string& _dirName, ofMesh* _mesh) {
    ofDirectory _dir(_dirName);

    _dir.allowExt("ply");//only show {}file ex)png,mp3,css
    _dir.sort();
    _dir.listDir();
    ssGlobalLog << _dir.size() << endl;
    if (_dir.size() > 0) {
        _mesh->load(_dir.getPath(_dir.size() - 1));
    }
}


//-----------THIS-TIME-FUNCS-----------//
void ofApp::importMesh() {
    loadLatestMesh("./selectedMesh/", &mainMesh);
}

void ofApp::modifyMesh() {
    glm::vec3 _theta = rotationSlider.get();
    glm::quat _quat = glm::quat(sin(_theta.x / 2), 0, 0, cos(_theta.x / 2)) * glm::quat(0, sin(_theta.y / 2), 0, cos(_theta.y / 2)) * glm::quat(0, 0, sin(_theta.z / 2), cos(_theta.z / 2));
    modifyInfo.setGlobalOrientation(_quat);
}

void ofApp::updateMesh() {
    mainMesh = gk.getModifiedMesh(&mainMesh,modifyInfo);
    //gk.saveMesh(getModifiedMesh(&mainMesh), 1);
    //mainMesh.clear();
    //loadLatestMesh("./meshExport/", &mainMesh);
    modifyInfo.resetTransform();
    bModified = true;
}

glm::vec3 ofApp::getCurrentVertex(const ofMesh& _mesh, stringstream& _ssDebug) {
    float nearestDistance = 0;
    glm::vec3 nearestVertex3D;
    glm::vec2 nearestVertex2D;
    int nearestIndex = 0;
    glm::vec3 mouse(ofGetMouseX(), ofGetMouseY(),0);
    for (int i = 0; i < _mesh.getNumVertices(); i++) {
        glm::vec3 _camPos = cam.getPosition();
        glm::vec3 _vertPos = _mesh.getVertex(i);
        glm::vec3 _vertNormal = _mesh.getNormal(i);
        if(glm::dot(_camPos-_vertPos,_vertNormal)>0){
            glm::vec3 cur = cam.worldToScreen(_vertPos);
            float distance = glm::distance(cur, mouse);
            if (i == 0 || distance < nearestDistance) {
                nearestDistance = distance;
                nearestVertex3D = _vertPos;
                nearestVertex2D = cur;
                nearestIndex = i;
            }
       }
    }

    glLineWidth(1);
    glColor3f(0, 1, 0);
    ofDrawLine(nearestVertex2D, mouse);

    ofNoFill();
    ofSetColor(ofColor::yellow);
    ofSetLineWidth(2);
    ofDrawCircle(nearestVertex2D, 4);
    ofSetLineWidth(1);

    glm::vec2 offset(10, -10);
    ofDrawBitmapStringHighlight(ofToString(nearestIndex), mouse + offset);
    _ssDebug << "VERTEX-POSITION: " << nearestVertex3D << endl;
    return nearestVertex3D;
}

void ofApp::checkVerticesHolder() {
    if (verticesPosHolder.size() > 2) {
        addMyPlane();
    }
}

void ofApp::addMyPlane() {
    Class_MyPlane _myPlane;
    ofMesh _mesh;
    _mesh.addVertices(verticesPosHolder);
    _myPlane.setup(_mesh, myPlanes.size(), &ssGlobalLog);
    myPlanes.push_back(_myPlane);
    verticesPosHolder.erase(verticesPosHolder.begin(), verticesPosHolder.end());
}

void ofApp::draw3DBeforeModified() {
    ofPushMatrix();
    ofMultMatrix(modifyInfo.getGlobalTransformMatrix());
    if (mainMesh.hasVertices()) {
        drawMainMesh();
    }
    if (bDebug) debugDot();
    ofPopMatrix();
}

void ofApp::draw3DAfterModified() {
    for (auto& myPlane : myPlanes) {
        if (!bHideAddedMesh)myPlane.drawInputMesh();
        if (!bHideMyPlane)myPlane.drawMyPlane();
        myPlane.drawInputMeshVertices();
    }
    if (!bHideMainMesh)drawMainMesh();
}

void ofApp::drawMainMesh() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glLineWidth(1);
    glPointSize(3);
    glColor4f(0.5, 0.5, 0.5, 0.5);
    if (!bModified)glColor3f(0.5, 0, 0);
    mainMesh.draw();
    glColor3f(0.8, 0.8, 0.8);
    if (!bModified) glColor3f(0.8, 0, 0);
    mainMesh.drawWireframe();
    /*
    glColor3f(0.8, 0.8, 0.8);
    if (!bModified) glColor3f(0.8, 0, 0);
    mainMesh.drawVertices();
    */
    glPointSize(10);
    glColor3f(0, 1, 0);
    glBegin(GL_POINTS);
    for (auto& _v : verticesPosHolder) {
        glVertex3f(_v.x, _v.y, _v.z);
    }
    glEnd();
    glDisable(GL_CULL_FACE);
}

//-----------DEBUG-----------//
void ofApp::debugDot() {
    for (int i = 0; i < mainMesh.getNumVertices(); i++) {
        glm::vec3 _camPos = cam.getPosition();
        glm::vec3 _vertPos = mainMesh.getVertex(i);
        glm::vec3 _vertNormal = mainMesh.getNormal(i);
        glLineWidth(0.5);
        glColor4f(1, 0, 1, 0.4);
        ofDrawLine(_camPos, _vertPos);
        if (glm::dot(_camPos - _vertPos, _vertNormal) < 0) {
            glColor4f(1, 0, 0, 0.8);
        }
        else {
            glColor4f(0, 0, 1, 0.8);
        }
        ofDrawLine(_vertPos, _vertPos + _vertNormal * 10);
        glPointSize(7);
        ofFill();
        glBegin(GL_POINTS);
        glVertex3f(_vertPos.x, _vertPos.y, _vertPos.z);
        glEnd();
    }
}
//--------------------------------------------------------------


//-----------EVENT-----------//
