
#include "Scene_Two.h"


void Scene_Two::initScene() {
    //-----------DEFAULT-----------//
    initParam();
    ofSetVerticalSync(true);
    ofSetFrameRate(40);

    //-----------RESET-----------//
    resetScene();
}

//-----------FOR-DEFAULT-----------//

void Scene_Two::initParam() {
    currentFrame = 0;
    adminInfo = SceneAdminInfo();
    adminInfo.dataSet = *dataSet;
}

void Scene_Two::resetScene() {
    initParam();
    loadImgsInPrj();
    setZones();
}


void Scene_Two::update() {
    gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0.98), 1));
    if (adminInfo.bGo)goNext();
}


void Scene_Two::draw() {
    //-----------MAIN-LAYER-----------//

    //BEGIN - Zones 
    glColor4f(1, 1, 1, 1);
    runZones();

    //-----------FRONT-LAYER-----------//
    glColor4f(1, 1, 1, 1);
    if (*bDebug)showCurrentDataSet();
    //gk.drawGrid();
}


//-----------FOR-LIB-----------//

//-----------FOR-SCENE-SET-----------//
void Scene_Two::setDataSet(DataSet* _dataSet) {
    dataSet = _dataSet;
}

void Scene_Two::loadImgsInPrj() {
    cout << "<BEGIN LOAD IMAGES IN SELECTED PROJECT>" << endl;
    string _dirPath = "./projectList/"+ dataSet->prjId;
    cout <<"- - ImgsInPrj-Path : "<< _dirPath << endl;
    imgsInPrj.erase(imgsInPrj.begin(), imgsInPrj.end());
    imgInPrjNames.erase(imgInPrjNames.begin(), imgInPrjNames.end());
    gk.loadImgsInDir(&imgsInPrj, &imgInPrjNames, _dirPath);
    cout << "- - Img-Num: " << imgsInPrj.size() << endl;
    for (auto& name : imgInPrjNames)cout << name << endl;
    cout << "<END LOAD IMAGES IN SELECTED PROJECT>" << endl;
    cout << "= = = = = = = = = = =" << endl;
}

void Scene_Two::setZones() {
    int _margin = 10;
    glm::vec2 _indexZonePos = glm::vec2(globalMargin);
    glm::vec2 _indexZoneSize = glm::vec2(ofGetWidth() - globalMargin * 2, 49 / 2);
    glm::vec2 _headTitleZonePos = glm::vec2(_indexZonePos.x, _indexZonePos.y + _indexZoneSize.y + _margin);
    glm::vec2 _headTitleZoneSize = glm::vec2(_indexZoneSize.x, 87 / 2);
    glm::vec2 _contentZonePos = glm::vec2(_indexZonePos.x, _headTitleZonePos.y + _headTitleZoneSize.y + _margin);
    glm::vec2 _contentZoneSize = glm::vec2(_indexZoneSize.x, ofGetHeight() - (_indexZonePos.y + _indexZoneSize.y + _margin + _headTitleZoneSize.y + _margin)-globalMargin);
    indexZone = Class_IndexZone_forSceneTwo(globalMargin,_indexZonePos, _indexZoneSize, uiElementsForIndexZone,&adminInfo);
    headTitleZone = Class_HeadTitleZone_forSceneTwo(globalMargin,_headTitleZonePos, _headTitleZoneSize,uiElementsForHeadTitleZone, &adminInfo);
    contentZone = Class_ContentZone_forSceneTwo(globalMargin,_contentZonePos, _contentZoneSize, uiElementsForContentZone,&adminInfo,
        &imgsInPrj,
        &imgInPrjNames
    );
    zones.erase(zones.begin(), zones.end());
    zones.push_back(&indexZone);
    zones.push_back(&headTitleZone);
    zones.push_back(&contentZone);
    for (auto& zone : zones)zone->setup();
}

//-----------FOR-SCENE-UPDATE-----------//
void Scene_Two::runZones() {
    for (auto& zone : zones)zone->run();
}

//-----------FOR-SCENE-RESIZED-----------//

//-----------FOR-SCENE-EVENT-----------//

