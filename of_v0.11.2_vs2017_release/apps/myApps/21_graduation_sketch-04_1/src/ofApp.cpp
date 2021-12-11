#include "ofApp.h"

bool shouldRemoveRigidBody(const shared_ptr<ofxBulletRigidBody>& ab) {
    return ab->getPosition().y > 15;
}

bool shouldRemoveModel(const shared_ptr<ofxBulletSoftTriMesh>& ab) {
    return ab->getPosition().y > 15;
}

bool shouldRemoveCrasher(const shared_ptr<ofxBulletRigidBody>& ab) {
    return ab->getPosition().y > 15;
}

bool shouldRemoveKinematicBody(const shared_ptr<ofxBulletRigidBody>& ab) {
    return ab->getPosition().y > 15;
}


void ofApp::setup() {
    initParam();
    initSet();
    resetCamera();
    cam.disableMouseInput();
    initSliders();

    loadFont();
    loadMesh();

    setWorld();
    makeControllerUI();
    makeArms();
    
    initListener();
    cam.enableMouseInput();  
}


void ofApp::update() {
    //-----------UPDATE-----------//
    gk.defaultUpdate(&cam,&currentFrame, &time);
    world.world->stepSimulation(1);
    world.update();
    updateControllerUI();
    updateArms();

    //-----------REMOVE-----------//
    ofRemove(rigidBodies, shouldRemoveRigidBody);
    ofRemove(models, shouldRemoveModel);
    ofRemove(crashers, shouldRemoveCrasher);
    ofRemove(kinematicBodies, shouldRemoveKinematicBody);
    
};


void ofApp::draw() {
    //-----------INIT-----------//
    stringstream ssInstruct;
    stringstream ssProgramInfo;
    stringstream ssDebug;

    //-----------PROCESS-----------//

    //-----------3D-LAYER-----------//
    cam.begin();
    glEnable(GL_DEPTH_TEST);
    
    //-----------no-light-----------//
    if (bDrawDebug) { //debug
        world.drawDebug();
        gk.draw3DAxis();
        gk.draw3DPlaneGrid(1, 50, glm::vec3(0, 1, 0), 0.8, glm::vec4(0.1, 0.2, 0.5, 1));
        drawModelPos();
        gk.drawFoundCenterTo3D(glm::vec3(mouseOnWorldPlane.x, 10, mouseOnWorldPlane.y), glm::vec2(groundInfo.x, groundInfo.z), glm::vec3(0, 1, 0));
    }
    //-----------yes-light-----------//
    ofEnableLighting();
    light.enable();
    ofSetColor(240);
    ofNoFill();
    ground->draw();
    drawBodies(); //rigid, ,kinematic, crashers, models
    drawArms();
    drawControllerUI();

    light.disable();
    ofDisableLighting();
    glDisable(GL_DEPTH_TEST);
    cam.end();

    //-----------2D-LAYER-----------//

    //-----------INFO-----------//
    createInfo(ssInstruct, ssProgramInfo, ssDebug);

    //-----------FRONT-LAYER-----------//
    drawMyGraph();
    gk.drawGrid();
    gk.drawInfo(ssInstruct, 1);
    gk.drawInfo(ssProgramInfo, 2);
    gk.drawInfo(ssDebug, 5);
    gk.drawInfo(ssGlobalLog, 6);
    guiOne.draw();
    guiTwo.draw();
   
}


//-----------THIS-TIME-INITS-----------//
void ofApp::initParam() {
    bDrawDebug = false;
    currentFrame = 0;
    fontSize = 3;
    mousePickIndex = -1;

    light.setPosition(0, -200, 0);
    light.setScale(glm::vec3(50));
}

void ofApp::initSet() {
    gk.setup(&ssGlobalLog);
    gk.setCam(&cam);

    gk.setGUI(guiOne, 12);
    gk.setGUI(guiTwo, 13);
}

void ofApp::resetCamera() {
    cam.setDistance(14);
    cam.setPosition(ofVec3f(0, -35.f, 35.f));
    cam.lookAt(ofVec3f(0, -5, 0), ofVec3f(0, 1, 0));
    cam.setVFlip(true);
}

void ofApp::initSliders() {
    /*  guiOne.add(slider.setup("sliderName", initial, min, max); */
    guiOne.add(stiffness.set("stiffness", glm::vec3(0.8), glm::vec3(0.01), glm::vec3(1.))); // this will create a slider group for your vec3 in the guiOne.
    guiOne.add(slider_piteration.set("Positions solver iterations", 2, 0, 4));
    guiOne.add(slider_kDF.set("Dynamic friction coefficient [0,1]", 0.5, 0, 1));
    guiOne.add(slider_kSSHR_CL.set("Soft vs soft hardness[0, 1](cluster only)", 0.5, 0, 1));
    guiOne.add(slider_kSS_SPLT_CL.set("Soft vs rigid impulse split [0,1] (cluster only)", 0.5, 0., 1));
    guiOne.add(slider_kSKHR_CL.set("Soft vs kinetic hardness [0,1] (cluster only)", 0.1f, 0, 1.f));
    guiOne.add(slider_kSK_SPLT_CL.set("Soft vs rigid impulse split [0,1] (cluster only)", 0.5, 0., 1.));
    guiOne.add(slider_selectModelIndex.set("SELECT MODEL INDEX", 0, 0, 10));
    
    guiTwo.add(slider_controller_angle.set("controller_angle", 0, -180, 180));
    guiTwo.add(slider_controller_pressure.set("controller_pressure", -4, -20, 0));
    guiTwo.add(slider_armsDowner_r.set("controller_hand_baseR", 15, 25, 0));
    guiTwo.add(slider_armsUpper_r.set("conttoller_hand_rotaterR", 15, 25, 0));
    guiTwo.add(slider_power.set("power", 0, -200, 500));

}

void ofApp::initListener() {
    ofAddListener(world.MOUSE_PICK_EVENT, this, &ofApp::mousePickEvent);
}

//-----------THISTIME-UTILS-----------//
void ofApp::loadFont() {
    font.loadFont("./font/SourceCodePro-Light.ttf", fontSize);
}

void ofApp::loadMesh() {
    mesh.load("./3d/test-normal-reduced.ply");
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    meshScaleFactor = 0.05;
    for (int i = 0; i < mesh.getNumVertices(); i++) {
        mesh.getVertices()[i] = mesh.getVertices()[i] * meshScaleFactor;
    }
    float* meshBBPtr = gk.getBoundingBox(mesh);
    for (int i = 0; i < 6; i++) {
        meshBB[i] = meshBBPtr[i];
    }
}

void ofApp::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
    //-----------INFO-----------//--later put into update func.

    _ssInstruct << "INSTRUCTIONS: " << endl;
    _ssInstruct << "> DEBUG              - H" << endl;
    _ssInstruct << "> ROTATE CAMERA      - RIGHT-BUTTON" << endl;
    _ssInstruct << "> MOVE CAMERA        - SHIFT + RIGHT-BUTTON" << endl;
    _ssInstruct << "> RESET CAMERA       - R" << endl;
    _ssInstruct << "> ADD CYLINDER       - C" << endl;
    _ssInstruct << "> ADD BOX            - B" << endl;
    _ssInstruct << "> ADD MODEL          - A" << endl;
    _ssInstruct << "> PICK OBJECT        - LEFT-BUTTON" << endl;
    _ssInstruct << "> DELETE             - D" << endl;
    _ssInstruct << "> SAVE IMG           - S" << endl;
    _ssInstruct << "> SAVE SELECTED MESH - M" << endl;
    _ssInstruct << "> CLEAR GLOBAL LOG   - L" << endl;


    _ssProgramInfo << "PROGRAM: " << "EPHEMERAL-TMP" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    _ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;


    _ssDebug << "AMOUT-CAN: " << ofToString(models.size(), 0) << endl;
    _ssDebug << "AMOUT-CRASHER: " << ofToString(rigidBodies.size(), 0) << endl;
    for (int i = 0; i < models.size(); i++) {
        _ssDebug << "MODEL ID: " << ofToString(i, 3) << " -> POSITION: " << models[i]->getPosition() << endl;
    }
    _ssDebug << "MOUSE WORLD POS: " << mouseOnWorldPlane << endl;
    _ssDebug << "MOUSE PICK POS: " << mousePickPos << endl;
}

void ofApp::drawMyGraph() {
    gk.setGraphGUI(14, glm::vec2(ofGetHeight() * 0.25), glm::vec2(groundInfo.x, groundInfo.z));
    gk.drawMouseOnGraphGUI(14, glm::vec2(ofGetHeight() * 0.25), glm::vec2(groundInfo.x, groundInfo.z), &mouseOnWorldPlane);
    for (int i = 0; i < models.size(); i++) {
        gk.drawEachDataOnGraphGUI(14, glm::vec2(ofGetHeight() * 0.25), glm::vec2(groundInfo.x, groundInfo.z), models[i]->getPosition(), glm::vec3(0, 1, 0));
    }
}

//-----------THISTIME-FUNCS-----------//
void ofApp::setWorld(){
    //-----------INITLIB-----------//
    world.setup();
    world.setCamera(&cam);
    world.enableGrabbing();

    //-----------ONCE-----------//
    ground = new ofxBulletBox();
    groundInfo = glm::vec3(50.f, 1.f, 50.f);
    ground->create(world.world, glm::vec3(0., groundInfo.y / 2, 0.), 0., groundInfo.x, groundInfo.y, groundInfo.z);
    ground->setProperties(.25, .95);
    ground->add();
}

void ofApp::addKinematicBody() {
    for (int i = 0; i < 5; i++) {
        shared_ptr< ofxBulletBox > kinematicBody(new ofxBulletBox());
        glm::vec3 kinematicBodyInfo = glm::vec3(2., 2., 2.);
        kinematicBody->create(world.world, glm::vec3(ofRandom(-groundInfo.x / 2, groundInfo.x / 2), -groundInfo.y / 2, ofRandom(-groundInfo.z / 2, groundInfo.z / 2)), 1, kinematicBodyInfo.x, kinematicBodyInfo.y, kinematicBodyInfo.z);
        // ceiling->setProperties(.25, .95);
        //kinematicBody->setCollisionFlags(kinematicBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
        kinematicBody->getCollisionObject()->setCollisionFlags(kinematicBody->getCollisionObject()->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
        kinematicBody->setActivationState(DISABLE_DEACTIVATION);
        kinematicBody->add();
        kinematicBodies.push_back(kinematicBody);
    }
    ssGlobalLog << "ADDED KINEMATIC BODIES." << endl;
}

void ofApp::addBox() {
    shared_ptr< ofxBulletBox > ceiling(new ofxBulletBox());

    ceiling->create(world.world, glm::vec3(0, -30, 0), 2., 50., 1.f, 50.f);
    // ceiling->setProperties(.25, .95);
    ceiling->add();
    glm::vec3 frc = glm::vec3(0, 1, 0);
    ceiling->applyCentralForce(frc * 2000);
    rigidBodies.push_back(ceiling);

    ssGlobalLog << "ADDED BOX." << endl;
}

void ofApp::addCylinder(const glm::vec2& _pos) {
    shared_ptr< ofxBulletCylinder > cylinder(new ofxBulletCylinder());
    ofQuaternion tquat;
    //tquat.makeRotate(ofRandom(180), ofRandom(1), ofRandom(1), ofRandom(1));
    tquat.makeRotate(0, 1, 0, 0);
    btTransform tt = ofGetBtTransform(glm::vec3(_pos.x, ofRandom(-10, -30), _pos.y), tquat);
    cylinder->create(world.world, tt, 4., 1., 5.);
    cylinder->add();
    crashers.push_back(cylinder);

    ssGlobalLog << "ADDED CYLINDER" << endl;
}

void ofApp::addModel(const glm::vec2& _pos) {
    ofQuaternion tquat;
    tquat.makeRotate(180, 1, 0, 0);

    //btTransform tt = ofGetBtTransform(ofVec3f(ofRandom(-5, 5) * tscale * 30, -15 * tscale * 30, 0), tquat);
    float scaleVal = 0.1;
    //btTransform tt = ofGetBtTransform(glm::vec3(ofRandom(-groundInfo.x/2,groundInfo.x/2),-(0-meshBB[2]),ofRandom(-groundInfo.x/2, groundInfo.x / 2)), tquat);
    btTransform tt = ofGetBtTransform(glm::vec3(_pos.x, -(0 - meshBB[2]), _pos.y), tquat);

    shared_ptr<ofxBulletSoftTriMesh> model(new ofxBulletSoftTriMesh());
    model->create(&world, mesh, tt, 2);

    model->getSoftBody()->generateBendingConstraints(3, model->getSoftBody()->m_materials[0]);
    //model->getSoftBody()->randomizeConstraints();
    //model->getSoftBody()->scale(btVector3(0.025 * tscale, 0.025 * tscale, 0.025 * tscale));
    //model->getSoftBody()->scale(btVector3(scaleVal,scaleVal,scaleVal));

    model->getSoftBody()->m_cfg.collisions = btSoftBody::fCollision::CL_SS + btSoftBody::fCollision::CL_RS;
    model->getSoftBody()->generateClusters(6);
    
    model->add();

    model->getSoftBody()->m_cfg.piterations = slider_piteration;//2; //Positions solver iterations
    model->getSoftBody()->m_cfg.kDF = slider_kDF;//1; //Dynamic friction coefficient [0,1]
    model->getSoftBody()->m_cfg.kSSHR_CL = slider_kSSHR_CL;// 1 // Soft vs soft hardness [0,1] (cluster only)
    model->getSoftBody()->m_cfg.kSS_SPLT_CL = slider_kSS_SPLT_CL;//0; // Soft vs rigid impulse split [0,1] (cluster only)
    model->getSoftBody()->m_cfg.kSKHR_CL = slider_kSKHR_CL;//0.1f; // Soft vs soft hardness [0,1] (cluster only)
    model->getSoftBody()->m_cfg.kSK_SPLT_CL = slider_kSK_SPLT_CL;// 1; // Soft vs rigid impulse split [0,1] (cluster only)
    model->setStiffness(stiffness.get().x, stiffness.get().y, stiffness.get().z);

    models.push_back(model);

    ssGlobalLog << "ADDED MODEL" << endl;
}

void ofApp::deleteModel() {
    if (models.size()) {
        models.erase(models.begin());
    }
    if (rigidBodies.size()) {
        rigidBodies.erase(rigidBodies.begin());
    }
    if (crashers.size()) {
        crashers.erase(crashers.begin());
    }
}

void ofApp::drawModelPos() {
    for (int i = 0; i < models.size(); i++) {
        gk.drawFoundCenterTo3D(models[i]->getPosition(), glm::vec2(groundInfo.x, groundInfo.z), glm::vec3(0, 1, 0));
    }
}

void ofApp::drawBodies() {
    glColor3f(1, 1, 0);
    for (int i = 0; i < rigidBodies.size(); i++) {
        rigidBodies[i]->draw();
    }

    for (int i = 0; i < crashers.size(); i++) {
        ofFill();
        glColor3f(0.5, 0.5, 0.5);
        crashers[i]->draw();
        ofNoFill();
        glColor3f(0.8, 0.8, 0.8);
        crashers[i]->draw();
    }

    glLineWidth(2);
    for (int i = 0; i < models.size(); i++) {
        glColor3f(0.5, 0.5, 0.5);
        if (i == slider_selectModelIndex % models.size()) {
            if (bDrawDebug)glColor3f(1, 1, 0);
        }
        models[i]->draw();
        glColor3f(0.8, 0.8, 0.8);
        models[i]->getMesh().drawWireframe();
        ofDisableLighting();
        glColor3f(1., 1., 1.);
        if (bDrawDebug)ofDrawBitmapString("MODEL ID: " + ofToString(i), models[i]->getPosition());
        ofEnableLighting();
    }
    glLineWidth(1);

    ofFill();
    for (int i = 0; i < kinematicBodies.size(); i++) {
        glColor3f(0.8, 0.8, 0.8);
        if (mousePickIndex == i) {
            ofSetColor(255, 0, 0);
        }
        kinematicBodies[i]->draw();
    }
}

void ofApp::makeControllerUI() {
    gkcAU.set(glm::vec3(0, -10, 0), 8, 0.5, glm::vec3(0, 1, 0), &font);
    gkcAD.set(glm::vec3(0, 0, 0), 8, 0.5, glm::vec3(0, 1, 0), &font);
}

void ofApp::updateControllerUI() {
    //gkcAD.update(slider_controller_angle);
    gkcAU.update(slider_controller_angle,slider_controller_pressure);
}

void ofApp::drawControllerUI() {
    gkcAU.drawController();
    gkcAD.drawController();
}

void ofApp::makeArms() {
    int _armsNum = 10;
    float _axisR = 10;
    glm::vec3 _armInfo = glm::vec3(2, 2, 2);

    //------ARMS-DOWNER
    glm::vec3 _axisSliderInfo = glm::vec3(_axisR, -_armInfo.y * 0.75, 0);
    for (int i = 0; i < _armsNum; i++) {
        //A1
        btGhostObject* ghost = new btGhostObject();
        
        btRigidBody* pRbA1;
        ofxBulletBox* _bbA;
        btTransform frameInA;
        frameInA = btTransform::getIdentity();
        btVector3 worldPosA(_axisSliderInfo.x * cos(-2 * PI / _armsNum * i), _axisSliderInfo.y, _axisSliderInfo.x * sin(-2 * PI / _armsNum * i));
        btTransform transA;
        transA.setIdentity();
        transA.setOrigin(worldPosA);
        btQuaternion _tquat;
        _tquat.setRotation(btVector3(0, 1, 0), 2 * PI / _armsNum * i);
        transA.setRotation(_tquat);
        float massA = 0;
        _bbA = new ofxBulletBox();
        _bbA->create(world.world, transA, massA, 1, 1, 1);
        _bbA->add();
        pRbA1 = _bbA->getRigidBody();
        pRbA1->setActivationState(DISABLE_DEACTIVATION);

       
        //B1
        btRigidBody* pRbB1;
        ofxBulletBox* _bbB;
        btTransform frameInB;
        frameInB = btTransform::getIdentity();
        btVector3 worldPosB(_axisSliderInfo.x * cos(-2 * PI / _armsNum * i), _axisSliderInfo.y, _axisSliderInfo.x * sin(-2 * PI / _armsNum * i));
        btTransform transB;
        transB.setIdentity();
        transB.setOrigin(worldPosB);
        transB.setRotation(_tquat);
        float massB = 1;
        _bbB = new ofxBulletBox();
        _bbB->create(world.world, transB, massB, 1, 1, 1);
        _bbB->add();
        pRbB1 = _bbB->getRigidBody();
        pRbB1->setActivationState(DISABLE_DEACTIVATION);
        armsDowner.push_back(_bbB);

        btSliderConstraint* _axisSlider = new btSliderConstraint(*pRbA1, *pRbB1, frameInA, frameInB, true);
        //btSliderConstraint* _axisSlider = new btSliderConstraint( *pRbB1,  frameInB, true);
        _axisSlider->setLowerLinLimit(-25.0F);
        _axisSlider->setUpperLinLimit(-1.0F);
        _axisSlider->setLowerAngLimit(0);
        _axisSlider->setUpperAngLimit(0);

        world.world->addConstraint(_axisSlider, true);
        _axisSlider->setDbgDrawSize(btScalar(10.f));
    }

    //-----ARMS-UPPER
    _axisSliderInfo = glm::vec3(_axisR, slider_controller_pressure, 0);
    for (int i = 0; i < _armsNum; i++) {
        //A1
        btGhostObject* ghost = new btGhostObject;

        btRigidBody* pRbA1;
        ofxBulletBox* _bbA;
        btTransform frameInA;
        frameInA = btTransform::getIdentity();
        btVector3 worldPosA(_axisSliderInfo.x * cos(-2 * PI / _armsNum * i), _axisSliderInfo.y, _axisSliderInfo.x * sin(-2 * PI / _armsNum * i));
        btTransform transA;
        transA.setIdentity();
        transA.setOrigin(worldPosA);
        btQuaternion _tquat;
        _tquat.setRotation(btVector3(0, 1, 0), 2 * PI / _armsNum * i);
        transA.setRotation(_tquat);
        float massA = 0;
        _bbA = new ofxBulletBox();
        _bbA->create(world.world, transA, massA, 1, 1, 1);
        _bbA->add();
        pRbA1 = _bbA->getRigidBody();
        pRbA1->setActivationState(DISABLE_DEACTIVATION);


        //B1
        btRigidBody* pRbB1;
        ofxBulletBox* _bbB;
        btTransform frameInB;
        frameInB = btTransform::getIdentity();
        btVector3 worldPosB(_axisSliderInfo.x * cos(-2 * PI / _armsNum * i), _axisSliderInfo.y, _axisSliderInfo.x * sin(-2 * PI / _armsNum * i));
        btTransform transB;
        transB.setIdentity();
        transB.setOrigin(worldPosB);
        transB.setRotation(_tquat);
        float massB = 1;
        _bbB = new ofxBulletBox();
        _bbB->create(world.world, transB, massB, 1, 1, 1);
        _bbB->add();
        pRbB1 = _bbB->getRigidBody();
        pRbB1->setActivationState(DISABLE_DEACTIVATION);
        armsUpper.push_back(_bbB);
        
        btSliderConstraint* _axisSlider = new btSliderConstraint(*pRbA1, *pRbB1, frameInA, frameInB, true);
        //btSliderConstraint* _axisSlider = new btSliderConstraint(*pRbB1, frameInB, true);
        _axisSlider->setLowerLinLimit(-25.0F);
        _axisSlider->setUpperLinLimit(-1.0F);
        _axisSlider->setLowerAngLimit(0);
        _axisSlider->setUpperAngLimit(0);

        world.world->addConstraint(_axisSlider, true);
        _axisSlider->setDbgDrawSize(btScalar(10.f));
    }
}

void ofApp::updateArms() {
    for (auto& chd : armsDowner) {
        glm::vec3 _dir =  glm::normalize(chd->getPosition())*-1;
        btVector3 _f = btVector3(_dir.x, 0, _dir.z);
        chd->applyCentralForce(_f * slider_power);        
    }
    for (auto& chu : armsUpper) {
        glm::vec3 _dir = glm::normalize(chu->getPosition()) * -1;
        btVector3 _f = btVector3(_dir.x, _dir.y, _dir.z);
        chu->applyCentralForce(_f * slider_power);
    }
}

void ofApp::drawArms() {
    glColor3f(0.7, 0, 0);
    for (auto& chd : armsDowner) {
        chd->draw();
    }
    for (auto& chu : armsUpper) {
        chu->draw();
    }
}

void ofApp::connectArmsToModel() {
    if (models.size() > 0) {
        for (auto& ad : armsDowner) {
            models[0]->getSoftBody()->appendAnchor(tmp, ad);
        }
        for (auto& au : armsUpper) {
            models[0]->getSoftBody()->appendAnchor(models[0]->getSoftBody, au);
        }
    }
}


//-----------EVENT-FUNCS-----------//
void ofApp::mousePickEvent(ofxBulletMousePickEvent& e) {
    mousePickIndex = -1;
    //for (int i = 0; i < kinematicBodies.size(); i++) {
    //    if (*kinematicBodies[i] == e) {
    //        mousePickIndex = i;
    //        mousePickPos = e.pickPosWorld;
    //        break;
    //    }
    //}
    for (int i = 0; i < armsUpper.size(); i++) {
        if (*armsUpper[i] == e) {
            mousePickIndex = i;
            mousePickPos = e.pickPosWorld;
            break;
        }
    }
}