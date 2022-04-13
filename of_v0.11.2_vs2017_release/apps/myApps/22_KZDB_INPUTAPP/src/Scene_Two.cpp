
#include "Scene_Two.h"
#include "Easing.h"


void Scene_Two::setup(){
    //-----------DEFAULT-----------//
    initParam();
    initGKSet();
    ofSetVerticalSync(true);

    //-----------RESET-----------//
    //resetScene();
}

//-----------FOR-DEFAULT-----------//

void Scene_Two::initParam() {
    currentFrame = 0;
    bDebug = false;
    currentPanelIndex = 0;
}

void Scene_Two::initGKSet() {
    gk.setup(&ssGlobalLog, 40);
    gk.setGUI(gui, 13);
}

void Scene_Two::resetScene() {
    initParam();
    loadImgs();
    inheriteCsv();
    initPanels();
}


void Scene_Two::update(){
    /*if(bDebug)gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0), 1));
    else gk.defaultUpdate(&currentFrame, &time,glm::vec4(glm::vec3(0.95),1));*/
    gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0), 1));
    managePanels();
    panels[currentPanelIndex]->update();
}


void Scene_Two::draw(){
    //-----------MAIN-LAYER-----------//

    //BEGIN - PANELS 
    glColor4f(1, 1, 1, 1);

    runPanel();

    //-----------INFO-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;
    createInfo(ssInstruct, ssProgramInfo, ssDebug);


    //-----------FRONT-LAYER-----------//
    glColor4f(1,1,1,1);
    gk.drawGrid();
    if (bDebug) {
        gk.drawInfo(ssInstruct, 1);
        gk.drawInfo(ssProgramInfo, 2);
        gk.drawInfo(ssDebug, 5);
        gk.drawInfo(ssGlobalLog, 6);
    }
}

//void Scene_Two::initAnimationClasses() {
//    animationClasses.erase(animationClasses.begin(), animationClasses.end());
//    animationClasses.push_back(&ao);
//    ao.setCam(&cam);
//    for (auto& ac : animationClasses) {
//        ac->setup();
//    }
//}
//
//void Scene_Two::resetAnimationClasses() {
//    animationIndex = 0;
//    for (auto& ac : animationClasses) {
//        ac->resetAnimation();
//    }
//}
//
//void Scene_Two::manageAnimationClasses() {
//    if (animationClasses[animationIndex]->getNextAnimationTriggerState())animationIndex++; //&& animationIndex < animationClasses.size() - 1
//    if (animationIndex == animationClasses.size())resetAnimationClasses();
//    for (int i = 0; i < animationIndex + 1; i++) {
//        animationClasses[i]->update();
//    }
//}

//-----------FOR-LIB-----------//
void Scene_Two::loadImgs() {
    string _dirPath = "./" + companyID + "/INPUT/" + materialID + "/projects/" + projectID;
    cout << "IMG-FOLDER : " << _dirPath << endl;
    imgs.erase(imgs.begin(), imgs.end());
    imgNames.erase(imgNames.begin(), imgNames.end());
    gk.loadImgsInDir(&imgs, &imgNames,_dirPath);
    cout << "IMG-NUM : " << imgs.size() << endl;
    cout << "IMG-FILE-NAMES : " << endl;
    for (auto& in : imgNames)cout << in << endl;
}

void Scene_Two::inheriteCsv() {

}




void Scene_Two::initPanels() {
    imgButtonsPanel = Class_ImgButtonsPanel(&selectedImg, &selectedImgID, &imgs, &imgNames, companyID, materialID, projectID);
    //selectedImg.loadImage("./companyA/materialA/projects/projectA/projectA_1.jpg");
    editPanel = Class_EditPanel(&selectedImg,&selectedImgID,companyID, materialID, projectID);
    
    panels.erase(panels.begin(), panels.end());
    panels.push_back(&imgButtonsPanel);
    panels.push_back(&editPanel);
    
    for(auto& pnl:panels)pnl->setup();
}

void Scene_Two::managePanels() {
    if (panels[currentPanelIndex]->goNext()) {
        panels[currentPanelIndex]->reset();
        currentPanelIndex = (currentPanelIndex + 1) % panels.size();
    }
    if (panels[currentPanelIndex]->goBack()) {
        panels[currentPanelIndex]->reset();
        if (currentPanelIndex >= 1)currentPanelIndex = currentPanelIndex - 1;
        else currentPanelIndex = panels.size()-1;
    }   
}

void Scene_Two::runPanel() {
    panels[currentPanelIndex]->draw();
}


void Scene_Two::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
    //-----------INFO-----------//--later put into update func.

    _ssInstruct << "INSTRUCTIONS: " << endl;
    _ssInstruct << "> FULLSCREEN   - F" << endl;
    _ssInstruct << "> DEBUG        - H" << endl;
    _ssInstruct << "> SAVE IMG     - S" << endl;


    _ssProgramInfo << "PROGRAM: " << "KZDB_INPUTAPP-PROTOTYPE" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    

    _ssDebug << "MOUSE-POS: " << ofGetMouseX() << ", " << ofGetMouseY() << endl;
    _ssDebug << "IMGPANELS-PANEL MOUSE-POS: " << imgButtonsPanel.mousePosOnPanel<< endl;

}


//-----------THIS-TIME-FUNCS-----------//


//-----------THISTIME-SCENE-BEIDGE-----------//


//-----------EVENT-----------//