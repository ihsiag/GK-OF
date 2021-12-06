#include "ofApp.h"


void ofApp::setup(){   
    initParam();
    initSet();
    initSliders();
    resetCamera();
    importMesh();  
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
    if (!bHideLight) {
        ofEnableLighting();
        light.enable();
    }
    if (!bModified)draw3DBeforeModified();
    if (bModified)draw3DAfterModified();
    if (!bHideLight) {
        light.disable();
        ofDisableLighting();
    }
    glDisable(GL_DEPTH_TEST);
    cam.end();
    
    //-----------2D-LAYER-----------//
    if (bModified)selectingVertexPos = getCurrentVertex(mainMesh, ssDebug);

    //-----------INFO-----------//
    createInfo(ssInstruct, ssProgramInfo, ssDebug);

    //-----------FRONT-LAYER-----------//
    gk.drawGrid();
    gk.drawInfo(ssInstruct, 1);
    gk.drawInfo(ssProgramInfo, 0);
    gk.drawInfo(ssDebug, 4);
    gk.drawInfo(ssGlobalLog, 5);
    if(!bModified)gui.draw();
    drawCamPosition();
}

//-----------FOR-LIB-----------//
//addGKPlane();

//-----------THIS-TIME-INITS-----------//
void ofApp::initParam(){
    modifyInfo = ofNode();
    
    modifyInfo.setPosition(0, 0, 0);
    bModified = false;
    bDebug = false;
    bHideMainMesh = false;
    bHideAddedMesh = true;// false;
    bHideGKPlane = true;// false;
    bHideNetwork = false;
    bHideGKPlaneNew = false;
    bHideSelectedPoint = false;
    bHideLight = false;

    verticesPosHolder.reserve(3);

    light.setPosition(80, 80, 80);
    light.setScale(glm::vec3(50));
}

void ofApp::initSet() {
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);
    gk.setGUI(gui);
}

void ofApp::initSliders() {
    gui.add(rotationSlider.set("ROTATION", glm::vec3(0), glm::vec3(-PI), glm::vec3(PI)));
}

void ofApp::resetCamera() {
    cam.setDistance(14);
    //cam.enableOrtho();
    cam.setPosition(glm::vec3(180, 180, 180));
    //cam.setVFlip(true);
    cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
}


//-----------THIS-TIME-UTILS-----------//

void ofApp::drawCamPosition() {
    gk.setGraphGUI(12, glm::vec2(ofGetHeight() * 0.25 - 60), glm::vec2(10 * 50));
    gk.drawEachDataOnGraphGUI(12, glm::vec2(ofGetHeight() * 0.25 - 60), glm::vec2(10 * 50 * 2), cam.getPosition(), glm::vec3(0, 1, 0));
}

void ofApp::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
    //-----------INFO-----------//--later put into update func.
    _ssInstruct << "INSTRUCTIONS: " << endl;
    _ssInstruct << "> DEBUG                 - H" << endl;
    _ssInstruct << "> FULL-SCREEN           - F" << endl;
    _ssInstruct << "> ROTATE CAMERA         - RIGHT-BUTTON" << endl;
    _ssInstruct << "> MOVE CAMERA           - SHIFT + RIGHT-BUTTON" << endl;
    _ssInstruct << "> RESET CAMERA          - R" << endl;
    _ssInstruct << "> UPDATE MESH           - U" << endl;
    _ssInstruct << "> HIDE MAIN-MESH        - 1" << endl;
    _ssInstruct << "> HIDE ADDED-MESH       - 2" << endl;
    _ssInstruct << "> HIDE ADDED-PLANE      - 3" << endl;
    _ssInstruct << "> HIDE NETWORK          - 4" << endl;
    _ssInstruct << "> HIDE GENERATED-SRF    - 5" << endl;
    _ssInstruct << "> HIDE SELECTED-POINT   - 6" << endl;
    _ssInstruct << "> HIDE LIGHT            - 7" << endl;
    _ssInstruct << "> BACK                  - Z" << endl;
    _ssInstruct << "> CLEAR GLOBAL LOG      - L" << endl;
    _ssInstruct << "> CLEAR ALL             - C" << endl;
    _ssInstruct << "> SAVE IMG              - S" << endl;
    _ssInstruct << "> SAVE GENERATED-MESH   - M" << endl;
    _ssInstruct << "> TEST                  - SPACE-BAR" << endl;
    _ssInstruct << "> TEST-2                - B" << endl;
    

    _ssProgramInfo << "PROGRAM: " << "EPHEMERAL-TMP" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    _ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;
    _ssProgramInfo << "CAMERA LOOK DIR: " << cam.getLookAtDir() << endl;
    
    _ssDebug << "DEBUG STATE: " << bDebug << endl;
    _ssDebug << "HIDE MAIN-MESH STATE: " << bHideMainMesh << endl;
    _ssDebug << "HIDE ADDED-MESH STATE: " << bHideAddedMesh << endl;
    _ssDebug << "HIDE ADDED-PLANE STATE: " << bHideGKPlane << endl;
    _ssDebug << "HIDE NETWORK STATE: " << bHideNetwork << endl;
    _ssDebug << "HIDE GENERATED-SRF STATE: " << bHideGKPlaneNew << endl;
    _ssDebug << "HIDE SELECTED-POINT STATE: " << bHideSelectedPoint << endl;
    _ssDebug << "HIDE LIGHT STATE: " << bHideLight << endl;
    _ssDebug << "CURRENT MY-PLANE NUM: " << gkPlanes.size() << endl;
    _ssDebug << "CURRENT MY-PLANE-NEW NUM: " << gkPlanesNew.size() << endl;
    
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

ofMesh ofApp::getMeshFromGKPlanes(vector<GKPlane>* _gkPlanes) {
    ofMesh _meshContainer;
    for (auto gp : *_gkPlanes) {
        _meshContainer.append(gp.convertToMesh());
    }
    return _meshContainer;
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
    mainMesh = gk.getModifiedMesh(mainMesh,modifyInfo);
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
        //if(glm::dot(_camPos-_vertPos,_vertNormal)>0){
            glm::vec3 cur = cam.worldToScreen(_vertPos);
            float distance = glm::distance(cur, mouse);
            if (i == 0 || distance < nearestDistance) {
                nearestDistance = distance;
                nearestVertex3D = _vertPos;
                nearestVertex2D = cur;
                nearestIndex = i;
            }
        //}
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
    _gkPlane.setup(_mesh, gkPlanes.size()+1);
    gkPlanes.push_back(_gkPlane);
    verticesPosHolder.erase(verticesPosHolder.begin(), verticesPosHolder.end());
    ssGlobalLog << "ADDED GKPLANE" << endl;
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
    drawNetwork();
    drawGKPlanes();
    if(!bHideGKPlaneNew)drawGKPlanesNew();
    if (bDebug) {
        drawgkIntersectLines();
        //debugDot();
    }
    if (!bHideMainMesh)drawMainMesh();
}

void ofApp::drawMainMesh() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glLineWidth(1);
    glPointSize(3);
    glColor4f(0.4, 0.5, 0.6, 0.5);
    if (!bModified)glColor3f(0.5, 0, 0);
    mainMesh.draw();
    glColor3f(0.7, 0.7, 0.8);
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

void ofApp::drawGKPlanes() {
    for (auto& gkPlane : gkPlanes) {
        if (!bHideAddedMesh)gkPlane.drawInputMesh();
        if (!bHideGKPlane)gkPlane.drawGKPlane();
        if (bDebug) {
            gkPlane.drawGKPlaneNormal();
            gkPlane.drawGKPlaneCentroid();
        }
        if(!bHideSelectedPoint)gkPlane.drawInputMeshVertices();
    }
}

void ofApp::setGKSplits() {
    gkPlanesNew.erase(gkPlanesNew.begin(), gkPlanesNew.end());
    sort(gkPlanes.begin(), gkPlanes.end());
    ssGlobalLog << "PLANES NUM: " << gkPlanes.size() << endl;
    gkDelaTriangles.erase(gkDelaTriangles.begin(), gkDelaTriangles.end());
    gkDelaTriangles = gkDela.getDelaunayTriangles(gkPlanes);
    ssGlobalLog << "GK-DELA-TRIANGLES NUM: " << gkDelaTriangles.size() << endl;

    gkSplits.erase(gkSplits.begin(), gkSplits.end());
    for (auto& gpl : gkPlanes) {
        gkSplits.emplace_back(gpl);
    }
    for (auto& gdt : gkDelaTriangles) {
        gkSplits[gdt.vertices[0].state - 1].addCutterPlane(gkPlanes[gdt.vertices[1].state - 1]);
        gkSplits[gdt.vertices[0].state - 1].addCutterPlane(gkPlanes[gdt.vertices[2].state - 1]);
        gkSplits[gdt.vertices[1].state - 1].addCutterPlane(gkPlanes[gdt.vertices[0].state - 1]);
        gkSplits[gdt.vertices[1].state - 1].addCutterPlane(gkPlanes[gdt.vertices[2].state - 1]);
        gkSplits[gdt.vertices[2].state - 1].addCutterPlane(gkPlanes[gdt.vertices[1].state - 1]);
        gkSplits[gdt.vertices[2].state - 1].addCutterPlane(gkPlanes[gdt.vertices[0].state - 1]);
    }
}

void ofApp::runGKSplits() {
    gkIntersectLines.erase(gkIntersectLines.begin(), gkIntersectLines.end());
    for (auto& gks : gkSplits) {
        gks.splitExcute(&gkPlanesNew,&gkIntersectLines);
    }
}

void ofApp::splitIntersectPlanes(GKPlane* _planeB, GKPlane* _planeA) {
        vector<glm::vec3> _intersectPointsA = gkSplitUtil.getPlaneIntersection(*_planeB, *_planeA);
        if (_intersectPointsA.size() == 2) {
            vector<glm::vec3> _intersectPointsB = gkSplitUtil.getPlaneIntersection(*_planeA, *_planeB);
            if (_intersectPointsB.size() == 2) {
                
                GKLineSimple _intersectLineA = GKLineSimple(_intersectPointsA[0], _intersectPointsA[1]);
                gkIntersectLines.push_back(_intersectLineA); //gkIntersectLines
                GKPlane _gkPlaneNewA = gkSplitUtil.splitPlaneWithIntersectLine(*_planeA, _intersectLineA);
                
                GKLineSimple _intersectLineB = GKLineSimple(_intersectPointsB[0], _intersectPointsB[1]);
                gkIntersectLines.push_back(_intersectLineB); //gkIntersectLines
                GKPlane _gkPlaneNewB = gkSplitUtil.splitPlaneWithIntersectLine(*_planeB, _intersectLineB);
                
                //mainPlane = _gkPlaneNew;
                *_planeA = _gkPlaneNewA; //maybe you should store data tmpPlane and after every check then you should put your data into realPlane
                *_planeB = _gkPlaneNewB;
            }

        }
}

void ofApp::runSplitIntersectPlanes() {
    for (auto& combi : gk.getIndexList_nC2(gkPlanesNew.size())) {
        splitIntersectPlanes(&gkPlanesNew[combi.x],&gkPlanesNew[combi.y]);
    }
}

void ofApp::drawNetwork() {
    if (!bHideNetwork) {
        if (gkDelaTriangles.size()) {
            int counter = 0;
            for (auto& gdt : gkDelaTriangles) {
                glLineWidth(0.5);
                ofFill();
                glColor4f(0.2, 0.2, 0.9, 1);
                glBegin(GL_LINE_LOOP);
                for (auto& v : gdt.vertices) {
                    glVertex3f(v.pos.x,v.pos.y,v.pos.z);
                }
                glEnd();
                cam.end();
                ofDrawBitmapString(ofToString(counter), cam.worldToScreen(gdt.getCentroid().pos));
                cam.begin();
                counter++;
            }
            /*
            for (auto& gks : gkSplits) {
                cam.end();
                ofDrawBitmapStringHighlight(ofToString(gks.mainPlane.state), cam.worldToScreen(gks.mainPlane.centroid));
                cam.begin();
            }
            */
        }
    }
}

void ofApp::drawgkIntersectLines() {
    for (auto& intersectLine : gkIntersectLines) {
        glLineWidth(3);
        glColor3f(0.4, 0.4, 0.9);
        intersectLine.drawLine();
        glPointSize(4);
        intersectLine.drawVertices();
    }
}

void ofApp::drawGKPlanesNew() {
    for (auto& gkPlaneNew : gkPlanesNew) {
        gkPlaneNew.drawGKPlane(glm::vec4(0.6,0.0,0.2,0.9),glm::vec4(0.6,0.8,0.2,1),2);
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
