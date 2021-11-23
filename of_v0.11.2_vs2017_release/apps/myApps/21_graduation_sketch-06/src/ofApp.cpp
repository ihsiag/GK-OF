#include "ofApp.h"


void ofApp::setup(){
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);
    gk.setGUI(gui);
    //glEnable(GL_DEPTH_TEST);
    createGUI();
    resetCamera();
    
    modifyInfo = ofNode();
    modifyInfo.setPosition(0, 0, 0);
    bModified = false;
    importMesh();

    bDebug = false;
    bHideMainMesh = false;

    verticesHolder.reserve(3);
}


void ofApp::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
}


void ofApp::draw(){
    //-----------INIT-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;


    if (!bModified)modifyMesh();
    if (bModified) {
        checkVerticesHolder();
    }
    
    cam.begin();
    //-----------MAIN-LAYER-----------//
    gk.draw3DAxis();
    gk.draw3DCADGrid(10, 50, glm::vec3(0, 1, 0), 1, glm::vec4(glm::vec3(0.3), 1));
    if (mainMesh.hasVertices()) {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        ofPushMatrix();
        ofMultMatrix(modifyInfo.getGlobalTransformMatrix());
        if(!bHideMainMesh)drawMainMesh();
        glDisable(GL_CULL_FACE);
        if(bDebug) debugDot();

        if (bModified) {
            for (auto& myFace : myFaces) {
                myFace.display();
            }
        }
        
        glDisable(GL_DEPTH_TEST);
        ofPopMatrix();
    }
   
    cam.end();
    if (bModified)selectingVertex = vertexPicker(mainMesh,ssDebug);
    //-----------INFO-----------//
    createInfo(ssInstruct, ssProgramInfo, ssDebug);

    //-----------FRONT-LAYER-----------//
    gk.drawGrid();
    gk.drawInfo(ssInstruct, 1);
    gk.drawInfo(ssProgramInfo, 2);
    gk.drawInfo(ssDebug, 5);
    gk.drawInfo(ssGlobalLog, 6);
    if(!bModified)gui.draw();
    drawCamPosition();
}
//-----------FOR-LIB-----------//
void ofApp::checkVerticesHolder() {
    int _size = verticesHolder.size();
    if (_size > 2) {
        Class_MyFace myFace;
        myFace.setup(verticesHolder);
        myFaces.push_back(myFace);
        verticesHolder.erase(verticesHolder.begin(),verticesHolder.end());
    }
}

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
    _ssInstruct << "> ROTATE CAMERA      - RIGHT-BUTTON" << endl;
    _ssInstruct << "> MOVE CAMERA        - SHIFT + RIGHT-BUTTON" << endl;
    _ssInstruct << "> RESET CAMERA       - R" << endl;
    _ssInstruct << "> UPDATE MESH        - U" << endl;
    _ssInstruct << "> HIDE MESH          - H" << endl;
    _ssInstruct << "> SAVE IMG           - S" << endl;
    _ssInstruct << "> SAVE MAIN-MESH     - M" << endl;
    _ssInstruct << "> CLEAR GLOBAL LOG   - L" << endl;


    _ssProgramInfo << "PROGRAM: " << "EPHEMERAL-TMP" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    _ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;
    _ssProgramInfo << "CAMERA LOOK DIR: " << cam.getLookAtDir() << endl;

    
    _ssDebug << "CURRENT-FACE-NUM: " << myFaces.size() << endl;
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

void ofApp::drawMainMesh() {
    glLineWidth(1);
    glPointSize(3);
    glColor4f(0.5, 0.5, 0.5,0.5);
    if (!bModified)glColor3f(0.5, 0, 0);
    mainMesh.draw();
    glColor3f(0.8, 0.8, 0.8);
    if (!bModified) glColor3f(0.8, 0, 0);
    mainMesh.drawWireframe();
    glColor3f(0.8, 0.8, 0.8);
    if (!bModified) glColor3f(0.8, 0, 0);
    mainMesh.drawVertices();
}

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



//-----------THIS-TIME-FUNCS-----------//

void ofApp::importMesh() {
    loadLatestMesh("./selectedMesh/", &mainMesh);
}

void ofApp::modifyMesh() {
    glm::vec3 _theta = rotationSlider.get();
    glm::quat _quat = glm::quat(sin(_theta.x / 2), 0, 0, cos(_theta.x / 2)) * glm::quat(0, sin(_theta.y / 2), 0, cos(_theta.y / 2)) * glm::quat(0, 0, sin(_theta.z / 2), cos(_theta.z / 2));
    modifyInfo.setGlobalOrientation(_quat);
}

ofMesh ofApp::getModifiedMesh(ofMesh* _mesh) {
    auto mat = modifyInfo.getGlobalTransformMatrix();
    for (auto& v : _mesh->getVertices()) {
        v = glm::vec3(mat * glm::vec4(v, 1));
    }
    auto mat2 = modifyInfo.getOrientationQuat();
    for (auto& v : _mesh->getNormals()) {
        v = glm::vec3(mat2 * glm::vec4(v, 1));
    }
    return *_mesh;
}

void ofApp::updateMesh() {
    mainMesh = getModifiedMesh(&mainMesh);
    //gk.saveMesh(getModifiedMesh(&mainMesh), 1);
    //mainMesh.clear();
    //loadLatestMesh("./meshExport/", &mainMesh);
    modifyInfo.resetTransform();
    bModified = true;
}

glm::vec3 ofApp::vertexPicker(const ofMesh& _mesh, stringstream& _ssDebug) {
    float nearestDistance = 0;
    glm::vec3 nearestVertex;
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
                nearestVertex = _vertPos;
                nearestVertex2D = cur;
                nearestIndex = i;
            }
       }
    }

    glColor3f(0, 1, 0);
    ofDrawLine(nearestVertex2D, mouse);

    ofNoFill();
    ofSetColor(ofColor::yellow);
    ofSetLineWidth(2);
    ofDrawCircle(nearestVertex2D, 4);
    ofSetLineWidth(1);

    glm::vec2 offset(10, -10);
    ofDrawBitmapStringHighlight(ofToString(nearestIndex), mouse + offset);
    _ssDebug << "VERTEX-POSITION: " << nearestVertex << endl;

    return nearestVertex;
}

//--------------------------------------------------------------


//-----------EVENT-----------//
