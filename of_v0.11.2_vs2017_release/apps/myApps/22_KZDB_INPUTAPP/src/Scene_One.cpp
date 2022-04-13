
#include "Scene_One.h"
#include "Easing.h"


void Scene_One::setup(){
    //-----------DEFAULT-----------//
    initParam();
    initGKSet();
    ofSetVerticalSync(true);

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
    loadMatImg();
    loadFont();
    loadProjectList();
    initPanels();
}


void Scene_One::update(){
    /*if(bDebug)gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0), 1));
    else gk.defaultUpdate(&currentFrame, &time,glm::vec4(glm::vec3(0.95),1));*/
    gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0), 1));
    managePanels();
}


void Scene_One::draw(){
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
void Scene_One::loadFont() {
    string _filePath = "./font/NotoSansJP-Regular.otf";
    fontMSize = 12;
    fontLSize = 16;
    fontMHeight = 18;
    fontLHeight = 24;
    ofTrueTypeFont::setGlobalDpi(72);//72
    ofTrueTypeFontSettings settings(_filePath, fontMSize);
    settings.antialiased = true;
    settings.contours = false;
    settings.simplifyAmt = 0.0;
    settings.addRanges(ofAlphabet::Japanese);
    settings.addRange(ofUnicode::Latin);
    settings.addRange(ofUnicode::Latin1Supplement);
    //    settings.addRange(ofUnicode::NumberForms);
    //    settings.addRange(ofUnicode::MathOperators);

    fontM.load(settings);

    settings.fontSize = fontLSize;
    fontL.load(settings);
}

void Scene_One::loadMatImg() {
    string _filePath = "./" + companyID + "/INPUT/" + materialID +"/" + materialID + ".jpg";
    cout << "IMG-FILE : " << _filePath << endl;
    matImg.loadImage(_filePath);
}

void Scene_One::loadProjectList() {
    string _filePath = companyID + "./INPUT/projectList.csv";
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

void Scene_One::initPanels(){
    
    matImgPanel = Class_MatImgPanel(&matImg,&companyID,&materialID,&fontL,&fontLSize,&fontLHeight);
    projectListPanel = Class_ProjectListPanel(&projectIDs,&fontM,&fontMSize,&fontMHeight);
    
    panels.erase(panels.begin(), panels.end());
    panels.push_back(&matImgPanel);
    panels.push_back(&projectListPanel);

    for (auto& pnl : panels)pnl->setup();

}

void Scene_One::resetPanels() {}

void Scene_One::managePanels() {}

void Scene_One::runPanel() {
    for (auto& pnl : panels)pnl->draw();
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
