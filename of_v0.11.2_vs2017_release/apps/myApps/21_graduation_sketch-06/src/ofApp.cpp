#include "ofApp.h"


void ofApp::setup(){
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);
    gk.setGUI(gui);
    createGUI();
    resetCamera();
    importMesh();

    modifyInfo = ofNode();
    modifyInfo.setPosition(0, 0, 0);
    bModified = false;
    bDebug = false;
    bHideMainMesh = false;
    bHideAddedMesh = true;// false;
    bHideGKPlane = true;// false;
    bHideGKPlaneScaled = false;

    verticesPosHolder.reserve(3);
}

void ofApp::update(){
    gk.defaultUpdate(&cam, &currentFrame, &time);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void ofApp::draw(){
    //-----------INIT-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;

    //-----------PROCESS-----------//
    if (!bModified)modifyMesh();
    if (bModified)checkVerticesHolder();
    
    //-----------3D-LAYER-----------//
    cam.begin();  
    glEnable(GL_DEPTH_TEST);
    gk.draw3DAxis();
    gk.draw3DPlaneGrid(10, 50, glm::vec3(0, 1, 0), 1, glm::vec4(glm::vec3(0.3), 1)); 
    if (!bModified)draw3DBeforeModified();
    if (bModified)draw3DAfterModified();
    glDisable(GL_DEPTH_TEST);
    cam.end();
    
    //-----------2D-LAYER-----------//
    if (bModified)selectingVertexPos = getCurrentVertex(mainMesh, ssDebug);
    //-----------INFO-----------//
    createInfo(ssInstruct, ssProgramInfo, ssDebug);

    //-----------FRONT-LAYER-----------//
    gk.drawGrid();
    gk.drawInfo(ssInstruct, 1);
    gk.drawInfo(ssProgramInfo, 2);
    gk.drawInfo(ssDebug, 5);
    gk.drawInfo(ssGlobalLog, 6);
    if(!bModified)gui.draw();
    drawCamPosition();
}

//-----------FOR-LIB-----------//
//addGKPlane();

//-----------THIS-TIME-UTILS-----------//
void ofApp::resetCamera() {
    cam.setDistance(14);
    //cam.enableOrtho();
    cam.setPosition(glm::vec3(180, 180, 180));
    //cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0),glm::vec3(0,1,0));
}

void ofApp::drawCamPosition() {
    gk.setGraphGUI(14, glm::vec2(ofGetHeight() * 0.25), glm::vec2(10 * 50));
    gk.drawEachDataOnGraphGUI(14, glm::vec2(ofGetHeight() * 0.25), glm::vec2(10 * 50 *2),cam.getPosition(),glm::vec3(0,1,0));
}

void ofApp::createGUI() {
    gui.add(rotationSlider.set("ROTATION", glm::vec3(0), glm::vec3(-PI), glm::vec3(PI)));
}

void ofApp::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
    //-----------INFO-----------//--later put into update func.
    _ssInstruct << "INSTRUCTIONS: " << endl;
    _ssInstruct << "> DEBUG               - H" << endl;
    _ssInstruct << "> FULL-SCREEN         - F" << endl;
    _ssInstruct << "> ROTATE CAMERA       - RIGHT-BUTTON" << endl;
    _ssInstruct << "> MOVE CAMERA         - SHIFT + RIGHT-BUTTON" << endl;
    _ssInstruct << "> RESET CAMERA        - R" << endl;
    _ssInstruct << "> UPDATE MESH         - U" << endl;
    _ssInstruct << "> HIDE MAIN-MESH      - 1" << endl;
    _ssInstruct << "> HIDE ADDED-MESH     - 2" << endl;
    _ssInstruct << "> HIDE FLAT-SRF       - 3" << endl;
    _ssInstruct << "> BACK                - Z" << endl;
    _ssInstruct << "> SAVE IMG            - S" << endl;
    _ssInstruct << "> SAVE GENERATED-MESH - M" << endl;
    _ssInstruct << "> CLEAR GLOBAL LOG    - L" << endl;

    _ssProgramInfo << "PROGRAM: " << "EPHEMERAL-TMP" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    _ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;
    _ssProgramInfo << "CAMERA LOOK DIR: " << cam.getLookAtDir() << endl;
    
    _ssDebug << "DEBUG-STATE: " << bDebug << endl;
    _ssDebug << "CURRENT MY-PLANE NUM: " << gkPlanes.size() << endl;
    _ssDebug << "HIDE MAIN-MESH: " << bHideMainMesh << endl;
    _ssDebug << "HIDE ADDED-MESH: " << bHideAddedMesh << endl;
    _ssDebug << "HIDE FLAT-SRF: " << bHideGKPlane << endl;
}

void ofApp::loadLatestMesh(const string& _dirName, ofMesh* _mesh) {
    ofDirectory _dir(_dirName);

    _dir.allowExt("ply");//only show {}file ex)png,mp3,css
    _dir.sort();
    _dir.listDir();
    if (_dir.size() > 0) {
        _mesh->load(_dir.getPath(_dir.size() - 1));
    }
    ssGlobalLog << "IMPORTED MESH" << endl;
}


//-----------THIS-TIME-FUNCS-----------//
void ofApp::importMesh() {
    loadLatestMesh("./selectedMesh/", &mainMesh);
}

void ofApp::modifyMesh() {
    glm::vec3 _theta = rotationSlider.get();
    glm::quat _quat = glm::quat(sin(_theta.x / 2), 0, 0, cos(_theta.x / 2)) * glm::quat(0, sin(_theta.y / 2), 0, cos(_theta.y / 2)) * glm::quat(0, 0, sin(_theta.z / 2), cos(_theta.z / 2));
    modifyInfo.setGlobalOrientation(_quat);
}

void ofApp::updateMesh() {
    mainMesh = gk.getModifiedMesh(&mainMesh,modifyInfo);
    //gk.saveMesh(getModifiedMesh(&mainMesh), 1);
    //mainMesh.clear();
    //loadLatestMesh("./meshExport/", &mainMesh);
    modifyInfo.resetTransform();
    bModified = true;
}

glm::vec3 ofApp::getCurrentVertex(const ofMesh& _mesh, stringstream& _ssDebug) {
    float nearestDistance = 0;
    glm::vec3 nearestVertex3D;
    glm::vec2 nearestVertex2D;
    int nearestIndex = 0;
    glm::vec3 mouse(ofGetMouseX(), ofGetMouseY(),0);
    for (int i = 0; i < _mesh.getNumVertices(); i++) {
        glm::vec3 _camPos = cam.getPosition();
        glm::vec3 _vertPos = _mesh.getVertex(i);
        glm::vec3 _vertNormal = _mesh.getNormal(i);
        if(glm::dot(_camPos-_vertPos,_vertNormal)>0){
            glm::vec3 cur = cam.worldToScreen(_vertPos);
            float distance = glm::distance(cur, mouse);
            if (i == 0 || distance < nearestDistance) {
                nearestDistance = distance;
                nearestVertex3D = _vertPos;
                nearestVertex2D = cur;
                nearestIndex = i;
            }
       }
    }

    /*
    glLineWidth(1);
    glColor3f(0, 1, 0);
    ofDrawLine(nearestVertex2D, mouse);
    */

    ofNoFill();
    ofSetColor(ofColor::yellow);
    ofSetLineWidth(2);
    ofDrawCircle(nearestVertex2D, 4);
    ofSetLineWidth(1);

    glm::vec2 offset(10, -10);
    ofDrawBitmapStringHighlight(ofToString(nearestIndex), mouse + offset);
    _ssDebug << "VERTEX-POSITION: " << nearestVertex3D << endl;
    return nearestVertex3D;
}

void ofApp::checkVerticesHolder() {
    if (verticesPosHolder.size() > 2) {
        addGKPlane();
    }
}

void ofApp::addGKPlane() {
    GKPlane _gkPlane;
    ofMesh _mesh;
    _mesh.addVertices(verticesPosHolder);
    _gkPlane.setup(_mesh, 0);
    gkPlanes.push_back(_gkPlane);
    verticesPosHolder.erase(verticesPosHolder.begin(), verticesPosHolder.end());
}

void ofApp::draw3DBeforeModified() {
    ofPushMatrix();
    ofMultMatrix(modifyInfo.getGlobalTransformMatrix());
    if (mainMesh.hasVertices()) {
        drawMainMesh();
    }
    if (bDebug) debugDot();
    ofPopMatrix();
}

void ofApp::draw3DAfterModified() {
    for (auto& gkPlane : gkPlanes) {
        if (!bHideAddedMesh)gkPlane.drawInputMesh();
        if (!bHideGKPlane)gkPlane.drawGKPlane();
        if (bDebug) {
            gkPlane.drawGKPlaneNormal();
            gkPlane.drawGKPlaneCentroid();
        }
        gkPlane.drawInputMeshVertices();       
    }
    if(bDebug)drawIntersections();
    if (!bHideMainMesh)drawMainMesh();
}

void ofApp::drawMainMesh() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glLineWidth(1);
    glPointSize(3);
    glColor4f(0.5, 0.5, 0.5, 0.5);
    if (!bModified)glColor3f(0.5, 0, 0);
    mainMesh.draw();
    glColor3f(0.8, 0.8, 0.8);
    if (!bModified) glColor3f(0.8, 0, 0);
    mainMesh.drawWireframe();
    /*
    glColor3f(0.8, 0.8, 0.8);
    if (!bModified) glColor3f(0.8, 0, 0);
    mainMesh.drawVertices();
    */
    glPointSize(10);
    glColor3f(0, 1, 0);
    glBegin(GL_POINTS);
    for (auto& _v : verticesPosHolder) {
        glVertex3f(_v.x, _v.y, _v.z);
    }
    glEnd();
    glDisable(GL_CULL_FACE);
}



void ofApp::findPlaneIntersections() {
    intersectLines.erase(intersectLines.begin(), intersectLines.end());
    //-> check this line!! you need to meke kumiawase with saiki func
    vector<glm::vec2> _indexSetList = gk.getIndexList_nC2(gkPlanes.size());
    ssGlobalLog << "COMBINATION SET NUM: [" << _indexSetList.size() <<"] FOUND" << endl;
    ssGlobalLog << "COMBINATION SET NUM IDEAL: [" << gk.totalNumCombination(gkPlanes.size(),2) << "] FOUND" << endl;
    for (auto& indexSet : _indexSetList) {
        ssGlobalLog << "SHOW : " << indexSet << endl;
        GKPlane& _gkPlanePassive = gkPlanes[indexSet.x];
        GKPlane& _gkPlaneActive = gkPlanes[indexSet.y];
        vector<glm::vec3> _intersectPoints = getPlaneIntersection(_gkPlanePassive, _gkPlaneActive);
        if (_intersectPoints.size() == 2) {
            intersectLines.push_back(GKLineSimple(_intersectPoints[0], _intersectPoints[1]));
        }
    }
    ssGlobalLog << "INTERSECT LINES: [" << intersectLines.size() << "] FOUND" << endl;
}
vector<glm::vec3> ofApp::getPlaneIntersection(const GKPlane& _gkPlanePassive, const GKPlane& _gkPlaneActive) {
    int _lengthMax = 100;
    vector<glm::vec3>  _intersectPoints;
    vector<GKLineSimple> _edges =  _gkPlaneActive.edges;
    for (auto& _edge : _edges) { 
        glm::vec3 _intersectPoint;
        //scalePlaneEdge(&_edge, _gkPlaneActive.centroid, _lengthMax);
        float _innerA = glm::dot(_gkPlanePassive.normal, _edge.a - _gkPlanePassive.centroid);
        float _innerB = glm::dot(_gkPlanePassive.normal, _edge.b - _gkPlanePassive.centroid);
        if (abs(_innerA) < 0.000001) { _innerA = 0.0; }
        if (abs(_innerB) < 0.000001) { _innerB = 0.0; }
        if ((_innerA > 0 && _innerB < 0) || (_innerA < 0 && _innerB > 0)) {
               // _bIntersect = true;
            _intersectPoint = (_edge.b - _edge.a) * abs(_innerA) / (abs(_innerA) + abs(_innerB)) + _edge.a;
            _intersectPoints.push_back(_intersectPoint);
        }       
    }
    return _intersectPoints;
}
void ofApp::scalePlaneEdge(GKLineSimple* _edge, const glm::vec3& _scaleCenter, const float& _scaleFactor) {
    _edge->a = glm::normalize(_edge->a - _scaleCenter) * _scaleFactor + _scaleCenter;
    _edge->b = glm::normalize(_edge->b - _scaleCenter) * _scaleFactor + _scaleCenter;
}

void ofApp::splitPlanes() {   
    /*
    for ( auto& thePlane: _PlanesWithLines){
        for (auto& gkLine : _gkLinesOnthePlane) {
            newPlanes.push_back(splitPlanes(thePlane, gkLine));
        }
    }
    */
}
GKPlane ofApp::splitPlaneWithIntersectLine(const GKPlane& _gkPlane, const GKLineSimple& _gkLine) {
    vector<GKPoint> _gkPointsPolar;
    for (auto vertex : _gkPlane.vertices) {
        //here you need to getOnPlaneVertices()
        _gkPointsPolar.push_back(GKPoint(gk.getPolarFromRectangular(vertex),0));
    }
    glm::vec3 _tmp = _gkLine.a;
    _gkPointsPolar.push_back(GKPoint(gk.getPolarFromRectangular(_tmp), 1));
    _tmp = _gkLine.b;
    _gkPointsPolar.push_back(GKPoint(gk.getPolarFromRectangular(_tmp), 1));
    gk.sortPolars(&_gkPointsPolar);
    
    vector<glm::vec3> _verticesForA, _verticesForB;
    bool bFaceBBegin = false;
    for (auto& gkPoint : _gkPointsPolar) {
        if (bFaceBBegin == false && gkPoint.state == 1)bFaceBBegin = true;
        if (bFaceBBegin == true && gkPoint.state == 1)bFaceBBegin = false;
        if (bFaceBBegin)_verticesForB.push_back(gk.getRectangularFromPolar(gkPoint.pos));
        else _verticesForA.push_back(gk.getRectangularFromPolar(gkPoint.pos));
    }
    GKPlane _splittedFaceA, _splittedFaceB;
    
    _splittedFaceA.setup(_verticesForA, 1);
    _splittedFaceB.setup(_verticesForB, 1);
    if (_splittedFaceA.hasInside(_gkPlane.centroid))return _splittedFaceA;
    else return _splittedFaceB;  
}

void ofApp::drawIntersections() {
    for (auto& intersectLine : intersectLines) {
        glLineWidth(3);
        glColor3f(0.4, 0.4, 0.9);
        intersectLine.drawLine();
    }
    if (!bHideGKPlaneScaled) {
        for (auto& gkPlane : gkPlanes) {
            for (auto edge : gkPlane.edges) {
                glLineWidth(1);
                glColor3f(0.9, 0.4, 0.4);
                scalePlaneEdge(&edge, gkPlane.centroid, 100);
                edge.drawLine();
            }
        }
    }
}



//-----------DEBUG-----------//
void ofApp::debugDot() {
    for (int i = 0; i < mainMesh.getNumVertices(); i++) {
        glm::vec3 _camPos = cam.getPosition();
        glm::vec3 _vertPos = mainMesh.getVertex(i);
        glm::vec3 _vertNormal = mainMesh.getNormal(i);
        glLineWidth(0.5);
        glColor4f(1, 0, 1, 0.4);
        ofDrawLine(_camPos, _vertPos);
        if (glm::dot(_camPos - _vertPos, _vertNormal) < 0) {
            glColor4f(1, 0, 0, 0.8);
        }
        else {
            glColor4f(0, 0, 1, 0.8);
        }
        ofDrawLine(_vertPos, _vertPos + _vertNormal * 10);
        glPointSize(7);
        ofFill();
        glBegin(GL_POINTS);
        glVertex3f(_vertPos.x, _vertPos.y, _vertPos.z);
        glEnd();
    }
}
//--------------------------------------------------------------


//-----------EVENT-----------//
