
#include "Scene_Two.h"
#include "Easing.h"


void Scene_Two::setup(){
    //-----------DEFAULT-----------//
    initParam();
    initGKSet();
    ofSetVerticalSync(true);

    //-----------RESET-----------//
    loadFont();
    resetScene();
}

//-----------FOR-DEFAULT-----------//

void Scene_Two::initParam() {
    currentFrame = 0;
    bDebug = false;
}

void Scene_Two::initGKSet() {
    gk.setup(&ssGlobalLog, 40);
    gk.setGUI(gui, 13);
}

void Scene_Two::resetScene() {
    initParam();
    loadMatImg();
    loadProjectList();
    initPanels();
}


void Scene_Two::update(){
    /*if(bDebug)gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0), 1));
    else gk.defaultUpdate(&currentFrame, &time,glm::vec4(glm::vec3(0.95),1));*/
    gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0), 1));
    managePanels();
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


//-----------FOR-LIB-----------//
void Scene_Two::setDataSet(DataSet* _dataSet) {
    dataSet = _dataSet;
}

void Scene_Two::loadFont() {
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

void Scene_Two::loadMatImg() {
    string _filePath = "./" + (* dataSet).companyID + "/INPUT/materials/" + (*dataSet).materialID + ".jpg";
    cout << "IMG-FILE : " << _filePath << endl;
    matImg.loadImage(_filePath);
}

void Scene_Two::loadProjectList() {
    string _filePath = (*dataSet).companyID + "./INPUT/projectList.csv";
    projectIDs.erase(projectIDs.begin(), projectIDs.end());
    if (csv.load(_filePath)) {
        cout << "CSV-FILE" << _filePath << endl;
        cout << "PROJECT-IDs : " << endl;
        for (auto& row : csv) {
            cout << row.getString(0) << endl;
            projectIDs.push_back(row.getString(0));
        }
    }
}

void Scene_Two::initPanels(){
    
    matImgPanel = Class_MatImgPanel(&matImg,&(*dataSet).companyID,&(*dataSet).materialID,&fontL);
    projectListPanel = Class_ProjectButtonsPanel(&dataSet,&projectIDs,&fontL);
    
    panels.erase(panels.begin(), panels.end());
    panels.push_back(&matImgPanel);
    panels.push_back(&projectListPanel);

    for (auto& pnl : panels)pnl->setup();

}

void Scene_Two::resetPanels() {}

void Scene_Two::managePanels() {
    //for (auto& pnl : panels)pnl->update();
}

void Scene_Two::runPanel() {
    for (auto& pnl : panels)pnl->draw();
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
}


//-----------THIS-TIME-FUNCS-----------//


//-----------THISTIME-SCENE-BEIDGE-----------//


//-----------EVENT-----------//
