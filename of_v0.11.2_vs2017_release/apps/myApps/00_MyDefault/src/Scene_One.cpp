#include "Scene_One.h"
#include "Easing.h"


void Scene_One::setup(){
    //-----------DEFAULT-----------//
    initParam();
    initGKSet();
    resetCamera();
    ofSetVerticalSync(true);

    //-----------LOADING-----------//
    loadMeshes();
}

void Scene_One::resetScene() {
    initParam();
    resetCamera();
}


void Scene_One::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
}


void Scene_One::draw(){
    cam.begin();
    //-----------MAIN-LAYER-----------//

    cam.end();
    //-----------INFO-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;
    createInfo(ssInstruct, ssProgramInfo, ssDebug);


    //-----------FRONT-LAYER-----------//
    gk.drawGrid();
    gk.drawInfo(ssInstruct, 1);
    gk.drawInfo(ssProgramInfo, 2);
    gk.drawInfo(ssDebug, 5);
    gk.drawInfo(ssGlobalLog, 6);
}


//-----------FOR-LIB-----------//

void Scene_One::initParam(){
    currentFrame = 0;
}

void Scene_One::initGKSet() {
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);
    gk.setGUI(gui, 13);
}

void Scene_One::resetCamera() {
    cam.enableOrtho();
    cam.setPosition(glm::vec3(0, 0, 500));
    cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
    cam.disableMouseInput();
}


void Scene_One::loadMeshes() {
    //string _dirName = "./meshExportedFromRoomToViewer/";
    //ofDirectory _dir(_dirName);
    //_dir.allowExt("ply");//only show {}file ex)png,mp3,css
    //_dir.sort();
    //_dir.listDir();
    //for (int i = 0; i < _dir.size(); i++) {
    //    ofMesh _mesh;
    //    _mesh.load(_dir.getPath(i));
    //    meshes.push_back(_mesh);
    //    meshNames.push_back(_dir.getPath(i));
    //}
    //cout << meshes.size() << endl;
}

void Scene_One::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
    //-----------INFO-----------//--later put into update func.

    _ssInstruct << "INSTRUCTIONS: " << endl;
    _ssInstruct << "> RESET CAMERA       - R" << endl;
    _ssInstruct << "> SAVE IMG           - S" << endl;


    _ssProgramInfo << "PROGRAM: " << "SHODOSHIMA_VISUAL-STUDIES" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    _ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;


    _ssDebug << "MOUSE POS" << ofGetMouseX() << ", " << ofGetMouseY() << endl;

}


//-----------THIS-TIME-FUNCS-----------//

//-----------THISTIME-SCENE-BEIDGE-----------//


//-----------EVENT-----------//
