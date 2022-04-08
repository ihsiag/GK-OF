#include "Scene_One.h"
#include "Easing.h"


void Scene_One::setup(){
    //-----------DEFAULT-----------//
    initParam();
    initGKSet();
    resetCamera();
    ofSetVerticalSync(true);

    //-----------LOADING-----------//
    loadImgs();
    setImgPanels();
    initEditPanel();
}

void Scene_One::resetScene() {
    initParam();
    resetCamera();
}


void Scene_One::update(){
    if(bDebug)gk.defaultUpdate(&cam, &currentFrame, &time, glm::vec4(glm::vec3(0), 1));
    else gk.defaultUpdate(&cam, &currentFrame, &time,glm::vec4(glm::vec3(0.95),1));
}


void Scene_One::draw(){

    cam.begin();
    //-----------MAIN-LAYER-----------//
    if (bDebug) {
        gk.draw3DAxis();
        //gk.draw3DPlaneGrid(2, 100, glm::vec3(0, 1, 0), 1, glm::vec4(0, 0, 1, 0.3));
    }
    //BEGIN - ANIMATIONCLASSES
    glColor4f(1, 1, 1, 1);
    drawImgPanels();
    drawEditPanel();
    //END - ANIMATIONCLASSES
    cam.end();
    //-----------INFO-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;
    createInfo(ssInstruct, ssProgramInfo, ssDebug);


    //-----------FRONT-LAYER-----------//
    glColor4f(1,1,1,1);
    if (bDebug) {
        gk.drawGrid();
        gk.drawInfo(ssInstruct, 1);
        gk.drawInfo(ssProgramInfo, 2);
        gk.drawInfo(ssDebug, 5);
        gk.drawInfo(ssGlobalLog, 6);
    }
}


//-----------FOR-LIB-----------//

void Scene_One::initParam(){
    currentFrame = 0;
    bDebug = true;
    
    bPlayAnimation = false;
    animationFrame = 0;
    animationIndex = 0;
    //initAnimationClasses();
}

void Scene_One::initGKSet() {
    gk.setup(&ssGlobalLog,60);
    gk.setCam(&cam);
    gk.setGUI(gui, 13);
}

//void Scene_One::initAnimationClasses() {
//    animationClasses.erase(animationClasses.begin(), animationClasses.end());
//    animationClasses.push_back(&ao);
//    ao.setCam(&cam);
//    for (auto& ac : animationClasses) {
//        ac->setup();
//    }
//}
//
//void Scene_One::resetAnimationClasses() {
//    animationIndex = 0;
//    for (auto& ac : animationClasses) {
//        ac->resetAnimation();
//    }
//}
//
//void Scene_One::manageAnimationClasses() {
//    if (animationClasses[animationIndex]->getNextAnimationTriggerState())animationIndex++; //&& animationIndex < animationClasses.size() - 1
//    if (animationIndex == animationClasses.size())resetAnimationClasses();
//    for (int i = 0; i < animationIndex + 1; i++) {
//        animationClasses[i]->update();
//    }
//}

void Scene_One::toggleAnimate() {
    bPlayAnimation = !bPlayAnimation;
}



void Scene_One::resetCamera() {
    //cam.setPosition(glm::vec3(180, 180, 180));
    ////cam.setVFlip(true);
    //cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
    cam.enableOrtho();
    cam.setPosition(glm::vec3(0, 0, 100));
    cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
    cam.disableMouseInput();
}

void Scene_One::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
    //-----------INFO-----------//--later put into update func.

    _ssInstruct << "INSTRUCTIONS: " << endl;
    _ssInstruct << "> FULLSCREEN   - F" << endl;
    _ssInstruct << "> DEBUG        - H" << endl;
    _ssInstruct << "> SAVE IMG     - S" << endl;


    _ssProgramInfo << "PROGRAM: " << "KZDB_INPUTAPP-PROTOTYPE" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    

    _ssDebug << "ANIMATION-STATE: " << bPlayAnimation << endl;
    _ssDebug << "MOUSE-POS: " << ofGetMouseX() << ", " << ofGetMouseY() << endl;
    _ssDebug << "CAMERA: " << cam.getPosition() << endl;

}


//-----------THIS-TIME-FUNCS-----------//
void Scene_One::loadImgs() {
    string companyID = "companyA";
    string materialID = "materialA";
    string projectID = "projectA";
    string _dirPath = "./" + companyID + "/" + materialID + "/projects/" + projectID;
    cout << _dirPath << endl;
    imgs.erase(imgs.begin(), imgs.end());
    gk.loadImgsInDir(&imgs,_dirPath);
    cout << imgs.size() << endl;
}

void Scene_One::resizeImgs(){}

void Scene_One::setImgPanels() {
    imgPanels.erase(imgPanels.begin(), imgPanels.end());
    for (auto& img : imgs) {
        Class_ImgPanel _imgPanel(&img, &selectedImg, & cam, glm::vec2(0), glm::vec2(0));
        imgPanels.push_back(_imgPanel);
    }
    resizeImgPanels();
}

void Scene_One::resizeImgPanels() {
    int columns = 4;
    glm::vec2 _sizeToDisplay = glm::vec2(ofGetWidth() /columns, ofGetHeight() /columns);
    for (int i = 0; i<imgPanels.size(); i++) {
        glm::vec2 _pos = glm::vec2(i % columns, i / columns) * _sizeToDisplay;
        imgPanels[i].onWindowResized(_pos,_sizeToDisplay);
    }
}

void Scene_One::drawImgPanels() {
    for (auto& ip : imgPanels) {
        ip.draw();
    }
}

void Scene_One::initEditPanel() {
    selectedImg = &imgs[0];
    editPanel = Class_EditPanel(&selectedImg, &cam);
}


void Scene_One::resizeEditPanel() {
    glm::vec2 _pos = glm::vec2(0);
    glm::vec2 _size = glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2);
    editPanel.onWindowResized(_pos,_size);
}

void Scene_One::drawEditPanel() {
    if(editPanel.bSetImg)editPanel.draw();
}



//-----------THISTIME-SCENE-BEIDGE-----------//


//-----------EVENT-----------//
