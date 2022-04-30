
#include "Scene_Three.h"


void Scene_Three::initScene() {
    //-----------DEFAULT-----------//
    initParam();
    ofSetVerticalSync(true);
    ofSetFrameRate(40);

    //-----------RESET-----------//
    resetScene();
}

//-----------FOR-DEFAULT-----------//

void Scene_Three::initParam() {
    currentFrame = 0;
    adminInfo = SceneAdminInfo();
    adminInfo.dataSet = *dataSet;
}

void Scene_Three::resetScene() {
    initParam();
    loadImgToStamp();
    setZones();
}


void Scene_Three::update() {
    gk.defaultUpdate(&currentFrame, &time, glm::vec4(glm::vec3(0.98), 1));
    if (adminInfo.bGo)goNext();
}


void Scene_Three::draw() {
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
void Scene_Three::setDataSet(DataSet* _dataSet) {
    dataSet = _dataSet;
}

void Scene_Three::loadImgToStamp() {
    string _dirPath = "./projectList/"+dataSet->prjId +"/"+dataSet->imgId;
    cout << _dirPath << endl;
    imgToStamp.loadImage(_dirPath);
    cout << imgToStamp.getHeight() << endl;
}

void Scene_Three::setZones() {
    int _margin = 10;
    glm::vec2 _indexZonePos = glm::vec2(0);
    glm::vec2 _indexZoneSize = glm::vec2(ofGetWidth(), 40);
    glm::vec2 _headTitleZonePos = glm::vec2(0, _indexZonePos.y + _indexZoneSize.y + _margin);
    glm::vec2 _headTitleZoneSize = glm::vec2(_indexZoneSize.x, _indexZoneSize.y);
    glm::vec2 _contentZonePos = glm::vec2(0, _headTitleZonePos.y + _headTitleZoneSize.y + _margin);
    glm::vec2 _contentZoneSize = glm::vec2(_indexZoneSize.x, ofGetHeight() - (_indexZoneSize.y + _margin + _headTitleZoneSize.y + _margin));
    indexZone = Class_IndexZone_forSceneThree(_indexZonePos, _indexZoneSize, &adminInfo);
    headTitleZone = Class_HeadTitleZone_forSceneThree(_headTitleZonePos, _headTitleZoneSize, &adminInfo);
    contentZone = Class_ContentZone_forSceneThree(_contentZonePos, _contentZoneSize, &adminInfo, &imgToStamp);
    zones.erase(zones.begin(), zones.end());
    zones.push_back(&indexZone);
    zones.push_back(&headTitleZone);
    zones.push_back(&contentZone);
    for (auto& zone : zones)zone->setup();
}

//-----------FOR-SCENE-UPDATE-----------//
void Scene_Three::runZones() {
    for (auto& zone : zones)zone->run();
}

//-----------FOR-SCENE-RESIZED-----------//

//-----------FOR-SCENE-EVENT-----------//

