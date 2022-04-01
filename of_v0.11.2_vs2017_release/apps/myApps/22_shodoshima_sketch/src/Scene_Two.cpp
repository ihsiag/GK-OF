#include "Scene_Two.h"
#include "Easing.h"


void Scene_Two::setup(){
    //-----------DEFAULT-----------//
    initParam();
    initGKSet();
    resetCamera();
    ofSetVerticalSync(true);

    //-----------LOADING-----------//
    createSpheres();
    initSpheresPos();
}

void Scene_Two::resetScene() {
    initParam();
    resetCamera();
}


void Scene_Two::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
    if (currentFrame % 120 == 0)counter++;
    if (currentFrame % 120 == 0)manageSpheres();
}


void Scene_Two::draw(){

    cam.begin();
    glEnable(GL_DEPTH_TEST);
    //-----------MAIN-LAYER-----------//
    if (bDebug) {
        gk.draw3DAxis();
        gk.draw3DPlaneGrid(2, 100, glm::vec3(0, 1, 0), 1, glm::vec4(0, 0, 1, 0.3));
    }
    for (auto& s : spheres) {
        s.update();
        s.draw();
    }
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

void Scene_Two::initParam(){
    currentFrame = 0;
    bDebug = true;
}

void Scene_Two::initGKSet() {
    gk.setup(&ssGlobalLog,60);
    gk.setCam(&cam);
    gk.setGUI(gui, 13);
}

void Scene_Two::resetCamera() {
    cam.setPosition(glm::vec3(180, 180, 180));
    //cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
    /*cam.enableOrtho();
    cam.setPosition(glm::vec3(0, 0, 500));
    cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
    cam.disableMouseInput();*/
}


void Scene_Two::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
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

void Scene_Two::createSpheres() {
    int _spheresNum = 10;
    int _sphereR = 20;
    for (int i = 0; i < _spheresNum; i++) {
        glm::vec4 _col = glm::vec4(ofRandom(0.6,1), ofRandom(0.6,1), ofRandom(0.6,1), 1);
        spheres.emplace_back(_sphereR,_col,gridUnit);
    }
}

void Scene_Two::initSpheresPos() {
    for (auto& s : spheres) {
        spheresStored.push_back(&s);
    }
    sphereGone.push_back(spheresStored[0]);
    spheresStored.erase(spheresStored.begin());
    sphereStaged.push_back(spheresStored[0]);
    spheresStored.erase(spheresStored.begin());
}

void Scene_Two::manageSpheres() {
    letSphereStaged();
    letSphereGone();
    letSphereStored();
    sphereStaged[0]->bStaged = true;
    sphereGone[0]->bGone = true;
    for (auto& ss : spheresStored) {
        ss->bStored = true;
    }
}

void Scene_Two::letSphereStaged() {
    sphereStaged.push_back(spheresStored[0]);
    spheresStored.erase(spheresStored.begin());
    //sphereStaged[0]->setGlobalPosition(glm::vec3(0));
}

void Scene_Two::letSphereGone() {
    sphereGone.push_back(sphereStaged[0]);
    sphereStaged.erase(sphereStaged.begin());
    //sphereGone[0]->setGlobalPosition(glm::vec3(gridUnit, 0, 0));
}

void Scene_Two::letSphereStored() {
    spheresStored.push_back(sphereGone[0]);
    sphereGone.erase(sphereGone.begin());
    for (auto& ss : spheresStored) {
        //ss->setGlobalPosition(glm::vec3(-gridUnit, 0, 0));
    }
}


//-----------THISTIME-SCENE-BEIDGE-----------//


//-----------EVENT-----------//
