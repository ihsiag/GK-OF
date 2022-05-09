
#include "Scene_One.h"


void Scene_One::initScene() {
    //-----------DEFAULT-----------//
    initParam();
    ofSetVerticalSync(true);
    ofSetFrameRate(40);

    loadPrjThumbImgs();
    loadPrjNames();
    loadFont();

    //-----------RESET-----------//
    resetScene();
}

//-----------FOR-DEFAULT-----------//

void Scene_One::initParam() {
    currentFrame = 0;
    adminInfo = SceneAdminInfo();
}

void Scene_One::resetScene() {
    initParam();
    setZones();
}


void Scene_One::update(){
    gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0.98), 1));
}


void Scene_One::draw(){
    //-----------MAIN-LAYER-----------//

    //BEGIN - Zones 
    glColor4f(1, 1, 1, 1);
    runZones();

    //-----------FRONT-LAYER-----------//
    glColor4f(1,1,1,1);
    if (*bDebug)showCurrentDataSet();
    //gk.drawGrid();
}


//-----------FOR-LIB-----------//

//-----------FOR-SCENE-SET-----------//
void Scene_One::setDataSet(DataSet* _dataSet) {
    dataSet = _dataSet;
}

void Scene_One::loadPrjThumbImgs() {
    cout << "<BEGIN LOAD PROJECT THUMBNAILS>" << endl;
    string _dirPath = "./projectList";
    ofDirectory _dir(_dirPath);
    prjThumbImgs.erase(prjThumbImgs.begin(), prjThumbImgs.end());
    prjIds.erase(prjIds.begin(), prjIds.end());
    _dir.sort();
    _dir.listDir();
    for (int i = 0; i < _dir.size();i++) {
        string _name;
        _name = _dir.getName(i);
        prjIds.push_back(_name);
        ofDirectory _dirdir(_dir.getPath(i));
        _dirdir.allowExt("png");
        _dirdir.allowExt("jpg");
        _dirdir.allowExt("jpeg");
        _dirdir.allowExt("JPEG");
        _dirdir.sort();
        _dirdir.listDir();
        ofImage _img;
        _img.loadImage(_dirdir.getPath(0));
        prjThumbImgs.push_back(_img);
    } 
    cout << "- - Img-Num: " << prjThumbImgs.size() << endl;
    for (auto& name: prjIds)cout << "- - PROJECT-ID: "<<name << endl;
    cout << "<END LOAD PROJECT THUMBNAILS>" << endl;
    cout << "= = = = = = = = = = =" << endl;
}

void Scene_One::loadPrjNames() {
    cout << "<BEGIN LOAD PROJECT NAMES>" << endl;
    if(csv.load("projectNameList.csv")){
        cout << "[ projectNameList.csv ] EXISTS" << endl;
        for (auto& row : csv) {
            prjNames.push_back(row.getString(1));
        }
    }
    else {
        cout << "[ projectNameList.csv ] DOESN'T EXISTS" << endl;
    }
    cout << "<END LOAD PROJECT NAMES>" << endl;
    cout << "= = = = = = = = = = =" << endl;
}

void Scene_One::loadFont() {
    cout << "<BEGIN LOAD FONT>" << endl;
    string _filePath = "./font/Noto-Sans_JP/NotoSansJP-Light.otf";
    ofTrueTypeFont::setGlobalDpi(72);//72

    ofTrueTypeFontSettings settings(_filePath, 22);
    settings.antialiased = true;
    settings.contours = true;
    settings.simplifyAmt = 0.5;
    settings.addRanges(ofAlphabet::Japanese);
    settings.addRange(ofUnicode::Latin);
    settings.addRange(ofUnicode::Latin1Supplement);
    //    settings.addRange(ofUnicode::NumberForms);
    //    settings.addRange(ofUnicode::MathOperators);

    font.load(settings);

    cout << "<END LOAD FONT>" << endl;
    cout << "= = = = = = = = = = =" << endl;
}

void Scene_One::setZones() {
    int _margin = 10;
    glm::vec2 _indexZonePos = glm::vec2(globalMargin);
    glm::vec2 _indexZoneSize = glm::vec2(ofGetWidth()-globalMargin*2, 49/2);
    glm::vec2 _headTitleZonePos = glm::vec2(_indexZonePos.x, _indexZonePos.y + _indexZoneSize.y + _margin);
    glm::vec2 _headTitleZoneSize = glm::vec2(_indexZoneSize.x, 87/2);
    glm::vec2 _contentZonePos = glm::vec2(_indexZonePos.x, _headTitleZonePos.y + _headTitleZoneSize.y+_margin);
    glm::vec2 _contentZoneSize = glm::vec2(_indexZoneSize.x, ofGetHeight() - (_indexZonePos.y + _indexZoneSize.y + _margin + _headTitleZoneSize.y + _margin)-globalMargin);
    indexZone = Class_IndexZone_forSceneOne(globalMargin,_indexZonePos,_indexZoneSize,uiElementsForIndexZone,&adminInfo);
    headTitleZone = Class_HeadTitleZone_forSceneOne(globalMargin,_headTitleZonePos,_headTitleZoneSize,uiElementsForHeadTitleZone,&adminInfo);
    contentZone = Class_ContentZone_forSceneOne(globalMargin,_contentZonePos,_contentZoneSize,uiElementsForContentZone,&adminInfo,&prjThumbImgs,&prjIds,&prjNames,&font);
    zones.erase(zones.begin(), zones.end());
    zones.push_back(&indexZone);
    zones.push_back(&headTitleZone);
    zones.push_back(&contentZone);
    for (auto& zone : zones)zone->setup();
}

//-----------FOR-SCENE-UPDATE-----------//
void Scene_One::runZones() {
    for (auto& zone : zones)zone->run();
}

//-----------FOR-SCENE-RESIZED-----------//

//-----------FOR-SCENE-EVENT-----------//

