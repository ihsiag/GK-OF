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
}

void Scene_Two::resetScene() {
    initParam();
    resetCamera();
  
    prepairSpheres();
    managePush();
}


void Scene_Two::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
    if (currentFrame% (displayTime+animationTime) == 0)counter++;
    if (currentFrame % (displayTime+animationTime) == 0)managePush();
}


void Scene_Two::draw(){
    cam.begin();
    glEnable(GL_DEPTH_TEST);
    //-----------MAIN-LAYER-----------//
    if (bDebug) {
        gk.draw3DAxis();
        gk.draw3DPlaneGrid(2, 100, glm::vec3(0, 1, 0), 1, glm::vec4(0, 0, 1, 0.3));
    }
    animateSpheres();
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
    _ssInstruct << "> RESET SCENE        - R" << endl;
    _ssInstruct << "> SAVE IMG           - S" << endl;
    _ssInstruct << "> SET CAMERA         - C" << endl;


    _ssProgramInfo << "PROGRAM: " << "SHODOSHIMA_MOVEMENT-STUDIES" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    _ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;
    
    _ssDebug << "COUNTER: " << counter << endl;
    _ssDebug << "STAGING-TIME: " << sphereStaging[0].displayT << " / " << sphereStaging[0].animationT << endl;
    _ssDebug << "LEAVING-TIME: " << sphereLeaving[0].displayT << " / " << sphereLeaving[0].animationT << endl;
    _ssDebug << "STORED-TIME: " << sphereStored[0].displayT << " / " << sphereStored[0].animationT << endl;
        _ssDebug << "MOUSE POS" << ofGetMouseX() << ", " << ofGetMouseY() << endl;
}


//-----------THIS-TIME-FUNCS-----------//

void Scene_Two::createSpheres() {
    spheres.erase(spheres.begin(), spheres.end());
    int _spheresNum = 10;
    int _sphereR = 20;
    for (int i = 0; i < _spheresNum; i++) {
        glm::vec4 _col = glm::vec4(ofRandom(0.6,1), ofRandom(0.6,1), ofRandom(0.6,1), 1);
        spheres.emplace_back(&cam,i,_sphereR,_col,gridUnit,float(displayTime),float(animationTime));
    }
}

void Scene_Two::prepairSpheres() {
    sphereStaging.erase(sphereStaging.begin(), sphereStaging.end());
    sphereLeaving.erase(sphereLeaving.begin(), sphereLeaving.end());
    sphereStored.erase(sphereStored.begin(), sphereStored.end());
    for (auto& s : spheres) {
        sphereStored.emplace_back(&s);
    }
    sphereLeaving.emplace_back(sphereStored[0].sphere);
    sphereStored.erase(sphereStored.begin());
    sphereStaging.emplace_back(sphereStored[0].sphere);
    sphereStored.erase(sphereStored.begin());
}

void Scene_Two::pushToStored() {
    sphereStored.emplace_back(sphereLeaving[0].sphere);
    sphereLeaving.erase(sphereLeaving.begin());
}

void Scene_Two::pushToLeaving() {
    sphereLeaving.emplace_back(sphereStaging[0].sphere);
    sphereStaging.erase(sphereStaging.begin());
}

void Scene_Two::pushToStaging() {
    sphereStaging.emplace_back(sphereStored[0].sphere);
    sphereStored.erase(sphereStored.begin());
}

void Scene_Two::managePush() {
    pushToStored();
    pushToLeaving();
    pushToStaging();
}

void Scene_Two::animateSpheres() {
    for (auto& ss : sphereStaging) {
        ss.run();
   }
    for (auto& sl : sphereLeaving) {
        sl.run();
    }
    for (auto& ss : sphereStored) {
        ss.run();
    }
    glColor3f(1, 0, 0);
    ofDrawCircle(0, 0, 50);
}

void Scene_Two::setCameraPos() {
    cam.setPosition(glm::vec3(0, 80, 100));
    cam.lookAt(glm::vec3(0), glm::vec3(0, 1, 0));
}



//-----------THISTIME-SCENE-BEIDGE-----------//


//-----------EVENT-----------//
