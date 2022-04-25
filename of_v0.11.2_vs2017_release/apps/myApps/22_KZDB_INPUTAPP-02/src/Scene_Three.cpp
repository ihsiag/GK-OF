
#include "Scene_Three.h"
#include "Easing.h"


void Scene_Three::setup(){
    //-----------DEFAULT-----------//
    initParam();
    initGKSet();
    ofSetVerticalSync(true);

    //-----------RESET-----------//
    //resetScene();
    loadFont();
}

//-----------FOR-DEFAULT-----------//

void Scene_Three::initParam() {
    currentFrame = 0;
    bDebug = false;
    currentPanelIndex = 0;
}

void Scene_Three::initGKSet() {
    gk.setup(&ssGlobalLog, 40);
    gk.setGUI(gui, 13);
}

void Scene_Three::resetScene() {
    initParam();
    loadImgs();
    inheriteCsv();
    initPanels();
}


void Scene_Three::update(){
    /*if(bDebug)gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0), 1));
    else gk.defaultUpdate(&currentFrame, &time,glm::vec4(glm::vec3(0.95),1));*/
    gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0), 1));
    managePanels();
    panels[currentPanelIndex]->update();
}


void Scene_Three::draw(){
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


//-----------FOR-LIB-----------//
void Scene_Three::setDataSet(DataSet* _dataSet) {
    dataSet = _dataSet;
}

void Scene_Three::loadFont() {
    string _filePath = "./font/NotoSansJP-Regular.otf";
    ofTrueTypeFont::setGlobalDpi(72);//72
    ofTrueTypeFontSettings settings(_filePath, 14);
    settings.antialiased = true;
    settings.contours = true;
    settings.simplifyAmt = 0.5;
    settings.addRanges(ofAlphabet::Japanese);
    settings.addRange(ofUnicode::Latin);
    settings.addRange(ofUnicode::Latin1Supplement);
    //    settings.addRange(ofUnicode::NumberForms);
    //    settings.addRange(ofUnicode::MathOperators);

    fontM.load(settings);

    settings.fontSize = 20;
    fontL.load(settings);
}

void Scene_Three::loadImgs() {
    string _dirPath = "./" + dataSet->companyID + "/INPUT/projects/"+ dataSet->projectID;
    cout << "IMG-FOLDER : " << _dirPath << endl;
    imgs.erase(imgs.begin(), imgs.end());
    imgNames.erase(imgNames.begin(), imgNames.end());
    gk.loadImgsInDir(&imgs, &imgNames,_dirPath);
    cout << "IMG-NUM : " << imgs.size() << endl;
    cout << "IMG-FILE-NAMES : " << endl;
    for (auto& in : imgNames)cout << in << endl;
}

void Scene_Three::inheriteCsv() {

}




void Scene_Three::initPanels() {
    
    imgButtonsPanel = Class_ImgButtonsPanel(&fontL,&selectedImg, &selectedImgID, &imgs, &imgNames, dataSet->companyID, dataSet->materialID, dataSet->projectID);
    //selectedImg.loadImage("./companyA/materialA/projects/projectA/projectA_1.jpg");
    editPanel = Class_EditPanel(&selectedImg,&selectedImgID,dataSet->companyID, dataSet->materialID, dataSet->projectID);
    
    panels.erase(panels.begin(), panels.end());
    panels.push_back(&imgButtonsPanel);
    panels.push_back(&editPanel);
    
    for(auto& pnl:panels)pnl->setup();
}

void Scene_Three::managePanels() {
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

void Scene_Three::runPanel() {
    panels[currentPanelIndex]->draw();
}


void Scene_Three::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
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

}


//-----------THIS-TIME-FUNCS-----------//


//-----------THISTIME-SCENE-BEIDGE-----------//


//-----------EVENT-----------//
