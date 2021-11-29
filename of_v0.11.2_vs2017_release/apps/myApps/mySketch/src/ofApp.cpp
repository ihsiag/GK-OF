#include "ofApp.h"


void ofApp::setup(){
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);
    gk.setGUI(gui);
    resetCamera();
}


void ofApp::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time, glm::vec4(0.75,0.75,0.75,1.0));
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
    gk.draw3DPlaneGrid(10,10,glm::vec3(0,1,0),0.5,glm::vec4(0.3,0.3,0.6,0.8));
    run();
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
    cam.setPosition(glm::vec3(100, 100, 100));
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
    /*
    _ssDebug << "DEBUG-STATE: " << bDebug << endl;
    _ssDebug << "CURRENT MY-PLANE NUM: " << gkPlanes.size() << endl;
    _ssDebug << "HIDE MAIN-MESH: " << bHideMainMesh << endl;
    _ssDebug << "HIDE ADDED-MESH: " << bHideAddedMesh << endl;
    _ssDebug << "HIDE FLAT-SRF: " << bHideGKPlane << endl;
    */
}

//-----------THIS-TIME-FUNCS-----------//
void ofApp::run() {
    gkPlaneForNormal.drawGKPlane();
    gkPlaneTestOriginal.drawGKPlane();
    gkPlaneTestModified.drawGKPlane();
    if (gkPlaneTestModified.vertices.size()) {
        for (int i = 0; i < 3; i++) {
            glm::vec3 _p1 = gkPlaneForNormal.vertices[i];
            glm::vec3 _p2 = gkPlaneTestOriginal.vertices[i];
            glm::vec3 _p3 = gkPlaneTestModified.vertices[i];
            glPointSize(20);
            glBegin(GL_POINTS);
            if (i == 0)glColor3f(1, 0, 0);
            if (i == 1)glColor3f(0, 1, 0);
            if (i == 2)glColor3f(0, 0, 1);
            glVertex3f(_p1.x, _p1.y, _p1.z);
            glVertex3f(_p2.x, _p2.y, _p2.z);
            glVertex3f(_p3.x, _p3.y, _p3.z);
            glEnd();
        }
    }
}

void ofApp::makeRandomMesh() {
    float _size = 80;
    ofMesh _mesh;
    for (int i = 0; i < 3; i++) {
        _mesh.addVertex(glm::vec3(ofRandom(-_size, _size), ofRandom(-_size, _size), ofRandom(-_size, _size)));
    }
    gkPlaneForNormal.setup(_mesh,0);

    vector<glm::vec3> _vertices;
    /*
    for (int i = 0; i < 3; i++) {
        _vertices.push_back(glm::vec3(ofRandom(-_size, _size), ofRandom(-_size, _size), 0));
    }
    */
    _vertices.push_back(glm::vec3(25,-34, 0));
    _vertices.push_back(glm::vec3(9,65, 0));
    _vertices.push_back(glm::vec3(-45,5, 0));

    gkPlaneTestOriginal.setup(_vertices, 0);
}

void ofApp::test() {
    gkPlaneTestModified.setup(gk.getModifiedVertices(gkPlaneTestOriginal.vertices, gkPlaneForNormal.modifyInfo),0);
}




//-----------DEBUG-FUNC-----------//

//-----------EVENT-----------//
