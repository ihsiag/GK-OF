#include "Scene_Three.h"
#include "Easing.h"


void Scene_Three::setup(){
    //-----------DEFAULT-----------//
    initParam();
    initGKSet();
    resetCamera();
    ofSetVerticalSync(true);

    //-----------LOADING-----------//
    createSpheres();
}

void Scene_Three::resetScene() {
    initParam();
    resetCamera();
}


void Scene_Three::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
    animateSpheres();
}


void Scene_Three::draw(){
    cam.begin();
    glEnable(GL_DEPTH_TEST);
    //-----------MAIN-LAYER-----------//
    if (bDebug) {
        gk.draw3DAxis();
        gk.draw3DPlaneGrid(2, 100, glm::vec3(0, 1, 0), 1, glm::vec4(0, 0, 1, 0.3));
    }
    drawSpheres();
    glColor3f(1, 0, 0);
    ofDrawCircle(0, 0, 50);
    glDisable(GL_DEPTH_TEST);
    cam.end();
    //-----------INFO-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;
    createInfo(ssInstruct, ssProgramInfo, ssDebug);


    //-----------FRONT-LAYER-----------//
    if (bDebug) {
        gk.drawGrid();
        gk.drawInfo(ssInstruct, 1);
        gk.drawInfo(ssProgramInfo, 2);
        gk.drawInfo(ssDebug, 5);
        gk.drawInfo(ssGlobalLog, 6);
    }
}


//-----------FOR-LIB-----------//

void Scene_Three::initParam(){
    currentFrame = 0;
    bDebug = true;
}

void Scene_Three::initGKSet() {
    gk.setup(&ssGlobalLog,60);
    gk.setCam(&cam);
    gk.setGUI(gui, 13);
}

void Scene_Three::resetCamera() {
    cam.setPosition(glm::vec3(180, 180, 180));
    //cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
    /*cam.enableOrtho();
    cam.setPosition(glm::vec3(0, 0, 500));
    cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
    cam.disableMouseInput();*/
}


void Scene_Three::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
    //-----------INFO-----------//--later put into update func.

    _ssInstruct << "INSTRUCTIONS: " << endl;
    _ssInstruct << "> RESET CAMERA       - R" << endl;
    _ssInstruct << "> SAVE IMG           - S" << endl;


    _ssProgramInfo << "PROGRAM: " << "SHODOSHIMA_MOVEMENT-STUDIES" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    _ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;

    _ssDebug << "MOUSE POS" << ofGetMouseX() << ", " << ofGetMouseY() << endl;
}


//-----------THIS-TIME-FUNCS-----------//

void Scene_Three::createSpheres() {
    int _spheresNum = 10;
    int _sphereR = 20;
    for (int i = 0; i < _spheresNum; i++) {
        glm::vec4 _col = glm::vec4(ofRandom(0.6,1), ofRandom(0.6,1), ofRandom(0.6,1), 1);
        spheres.emplace_back(_sphereR,_col,gridUnit);
    }
}

void Scene_Three::animateSpheres() {
    spheres[0].slide();
}

void Scene_Three::drawSpheres() {
    for (auto& ss : spheres) {
        ss.update();
        ss.draw();
    }
}



//-----------THISTIME-SCENE-BEIDGE-----------//


//-----------EVENT-----------//
