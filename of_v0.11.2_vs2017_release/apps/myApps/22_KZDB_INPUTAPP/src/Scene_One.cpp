
#include "Scene_One.h"
#include "Easing.h"


void Scene_One::setup(){
    //-----------DEFAULT-----------//
    initParam();
    initGKSet();
    ofSetVerticalSync(true);
    loadFont();

    //-----------RESET-----------//
    resetScene();
}

//-----------FOR-DEFAULT-----------//

void Scene_One::initParam() {
    currentFrame = 0;
    bDebug = false;
}

void Scene_One::initGKSet() {
    gk.setup(&ssGlobalLog, 40);
    gk.setGUI(gui, 13);
}

void Scene_One::resetScene() {
    initParam();
    
    loadImgs();
    inheriteCsv();
    initPanels();
}


void Scene_One::update(){
    /*if(bDebug)gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0), 1));
    else gk.defaultUpdate(&currentFrame, &time,glm::vec4(glm::vec3(0.95),1));*/
    gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0), 1));
    matButtonsPanel.update();
}


void Scene_One::draw(){
    //-----------MAIN-LAYER-----------//

    //BEGIN - PANELS 
    glColor4f(1, 1, 1, 1);

    runPanel ();

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
void Scene_One::setDataSet(DataSet* _dataSet) {
    dataSet = _dataSet;
    //
    dataSet->companyID = "company-A";
}

void Scene_One::loadFont() {
    string _filePath = "./font/NotoSansJP-Regular.otf";
    ofTrueTypeFont::setGlobalDpi(72);//72
    ofTrueTypeFontSettings settings(_filePath,14);
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


void Scene_One::loadImgs() {
    string _dirPath = "./" + dataSet->companyID + "/INPUT/materials";
    cout << "IMG-FOLDER : " << _dirPath << endl;
    matImgs.erase(matImgs.begin(), matImgs.end());
    matImgNames.erase(matImgNames.begin(), matImgNames.end());
    gk.loadImgsInDir(&matImgs, &matImgNames, _dirPath);
    cout << "IMG-NUM : " << matImgs.size() << endl;
    cout << "IMG-FILE-NAMES : " << endl;
    for (auto& in : matImgNames) {
        in = gk.extractFilePathWithoutExt(in);
        cout << in << endl;
    }
}

void Scene_One::inheriteCsv() {

}

void Scene_One::initPanels() {
    loadFont();
    matButtonsPanel = Class_MatButtonsPanel(&fontL, &matImgs, &matImgNames, &dataSet);
    matButtonsPanel.setup();
}

void Scene_One::managePanels() {

}

void Scene_One::runPanel() {
    matButtonsPanel.draw();
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
    

    _ssDebug << "MOUSE-POS: " << ofGetMouseX() << ", " << ofGetMouseY() << endl;
}


//-----------THIS-TIME-FUNCS-----------//


//-----------THISTIME-SCENE-BEIDGE-----------//


//-----------EVENT-----------//
