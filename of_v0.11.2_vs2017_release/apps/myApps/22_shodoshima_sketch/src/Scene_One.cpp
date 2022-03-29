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
    gk.defaultUpdate(&cam, &currentFrame, &time,glm::vec4(glm::vec3(0.95),1));
}


void Scene_One::draw(){

    cam.begin();
    glEnable(GL_DEPTH_TEST);
    //-----------MAIN-LAYER-----------//
    if (bDebug) {
        gk.draw3DAxis();
        gk.draw3DPlaneGrid(2, 100, glm::vec3(0, 1, 0), 1, glm::vec4(0, 0, 1, 0.3));
    }
    meshes[0].drawFaces();
    drawGridOnPlane();
    glDisable(GL_DEPTH_TEST);
    cam.end();
    //-----------INFO-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;
    createInfo(ssInstruct, ssProgramInfo, ssDebug);


    //-----------FRONT-LAYER-----------//
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
    
}

void Scene_One::initGKSet() {
    gk.setup(&ssGlobalLog,60);
    gk.setCam(&cam);
    gk.setGUI(gui, 13);
}

void Scene_One::resetCamera() {
    cam.setPosition(glm::vec3(180, 180, 180));
    //cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
    /*cam.enableOrtho();
    cam.setPosition(glm::vec3(0, 0, 500));
    cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
    cam.disableMouseInput();*/
}

void Scene_One::loadMeshes() {
    meshes.erase(meshes.begin(), meshes.end());
    string _dirName = "./models/";
    ofDirectory _dir(_dirName);
    _dir.allowExt("ply");//only show {}file ex)png,mp3,css
    _dir.sort();
    _dir.listDir();
    for (int i = 0; i < _dir.size(); i++) {
        ofMesh _mesh;
        _mesh.load(_dir.getPath(i));
        rescaleMesh(&_mesh, glm::vec3(0),0.01);
        meshes.push_back(_mesh);
    }
    cout << meshes.size() << endl;
}

void Scene_One::rescaleMesh(ofMesh* _mesh,const glm::vec3& _sclC, const float& _sclF) {
    for (int i = 0; i < _mesh->getNumVertices(); i++) {
        _mesh->getVertices()[i] = (_mesh->getVertex(i) - _sclC) * _sclF;
    }
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
void Scene_One::drawGridOnPlane() {
    int _positionVal = 60;
    int _size = 5;
    glLineWidth(3);
    glColor3f(0,1,0);
    gk.drawCross(glm::vec3(0,1,0), - _positionVal, -_positionVal, _size);
    gk.drawCross(glm::vec3(0, 1, 0), -_positionVal, _positionVal, _size);
    gk.drawCross(glm::vec3(0, 1, 0), _positionVal, -_positionVal, _size);
    gk.drawCross(glm::vec3(0, 1, 0), _positionVal, _positionVal, _size);
}

//-----------THISTIME-SCENE-BEIDGE-----------//


//-----------EVENT-----------//
