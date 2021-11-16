#pragma once

#include "ofMain.h"
#include "Class_MyFunctions.h"
#include "ofxBullet.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

public:
    //-----------BASIC-----------//
    Class_MyFunctions mf;
    ofEasyCam cam;
    ofTrueTypeFont font;
    ofMesh mesh;
    float meshBB[6];
    ofLight light;

    stringstream ssGlobalLog;

    //-----------PHISICLIB-----------//
    ofxBulletWorldSoft world;   
    ofxBulletBox* ground;
    glm::vec4 groundInfo;
    vector< shared_ptr<ofxBulletRigidBody> > rigidBodies;
    vector< shared_ptr<ofxBulletSoftTriMesh> > crashedCans;
    vector< shared_ptr<ofxBulletRigidBody>> crashers;

    
    //-----------GLOBALVAL-----------//
    bool bDrawDebug;

    float currentFrame;
    float time;
    int fontSize;

    //-----------SLIDER-----------//
    //ofxPanel gui;
    ofxGuiGroup gui;
    ofParameter<glm::vec3> stiffness;
    ofParameter<int>  slider_piteration;
    ofParameter<float> slider_kDF;
    ofParameter<float> slider_kSSHR_CL;
    ofParameter<float> slider_kSS_SPLT_CL;
    ofParameter<float> slider_kSKHR_CL;
    ofParameter<float> slider_kSK_SPLT_CL;
    
    ofParameter<int> slider_selectModelIndex;


    void setup() {
        mf.setup(&ssGlobalLog);
        mf.setCam(&cam);
        mf.setGUI(gui);
        
        //-----------GLOBALVAL-----------//
        bDrawDebug = false;
        currentFrame = -1;
        fontSize = 10;

        //-----------SLIDER-----------//
        /*  gui.add(slider.setup("sliderName", initial, min, max); */       
        gui.add(stiffness.set("stiffness", glm::vec3(0.8), glm::vec3(0.01), glm::vec3(1.))); // this will create a slider group for your vec3 in the gui.
        gui.add(slider_piteration.set("Positions solver iterations", 2, 0, 4));
        gui.add(slider_kDF.set(" Dynamic friction coefficient [0,1]", 0.5, 0, 1));
        gui.add(slider_kSSHR_CL.set("Soft vs soft hardness[0, 1](cluster only)", 0.5, 0, 1));
        gui.add(slider_kSS_SPLT_CL.set("Soft vs rigid impulse split [0,1] (cluster only)", 0.5, 0., 1));
        gui.add(slider_kSKHR_CL.set("Soft vs kinetic hardness [0,1] (cluster only)", 0.1f, 0, 1.f));
        gui.add(slider_kSK_SPLT_CL.set("Soft vs rigid impulse split [0,1] (cluster only)", 0.5, 0., 1.));
        gui.add(slider_selectModelIndex.set("SELECT MODEL INDEX", 0,0,10));


        //-----------EVENTLISTENER-----------//
        ofEventListener listener = stiffness.newListener([&](glm::vec3&) {this->onStiffnessChanged(stiffness); });

        //-----------LOAD-----------//
        font.loadFont("./font/SourceCodePro-Light.ttf", fontSize);
        mesh.load("./3d/test-normal-reduced.ply");
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        float* meshBBPtr = mf.getBoundingBox(mesh);
        for (int i = 0; i < 6; i++) {
            meshBB[i] = meshBBPtr[i];
        }
        
        //-----------CAMERA-----------//
        cam.disableMouseInput();
        cam.setDistance(14);
        cam.setPosition(ofVec3f(-20.f, -10.f, -20.f));
        cam.lookAt(ofVec3f(0, -5, 0), ofVec3f(0, -1, 0));



        //-----------INITLIB-----------//
        world.setup();
        world.setCamera(&cam);

        //-----------ONCE-----------//
        ground = new ofxBulletBox();
        groundInfo = glm::vec4(50.f, 1.f, 50.f, 1.f);
        ground->create(world.world, glm::vec3(0.,groundInfo.w/2,0.), 0.,groundInfo.x,groundInfo.y,groundInfo.z);
        ground->setProperties(.25, .95);
        ground->add();

        light.setPosition(0, -200, 0);
        //light.boom(100);
        light.setScale(glm::vec3(50));

        //-----------GO-----------//
        cam.enableMouseInput();
    }

    void update();
    
    void draw() {

        //-----------3D-BEGIN-----------//
        ofEnableDepthTest();
        cam.begin();
        if (bDrawDebug) {
            world.drawDebug();
            mf.draw3DAxis();
            drawModelPos();
        }
        ofEnableLighting();
        light.enable();        
        
        ofSetColor(240);
        ofNoFill();
        ground->draw();

        glColor3f(1, 1, 0);
        for (int i = 0; i < rigidBodies.size(); i++) {
            rigidBodies[i]->draw();
        }

        glLineWidth(2);
        for (int i = 0; i < crashedCans.size(); i++) {
            glColor3f(0.5, 0.5, 0.5);
            crashedCans[i]->draw();
            glColor3f(0.8, 0.8, 0.8);
            crashedCans[i]->getMesh().drawWireframe();
        }
        glLineWidth(1);

        light.disable();
        ofDisableLighting();
        cam.end();
        ofDisableDepthTest();
        //-----------3D-END-----------//

        //-----------INFO-----------//--later put into update func.
        stringstream ssInstruct;
        ssInstruct << "INSTRUCTIONS: " << endl;
        ssInstruct << "> DEBUG     - H" << endl;
        ssInstruct << "> CAMERA    - MOUSE" << endl;
        ssInstruct << "> BALL      - SPACEBAR" << endl;
        ssInstruct << "> ADD MODEL - A" << endl;
        ssInstruct << "> DELETE    - D" << endl;
        ssInstruct << "> SAVE IMG  - S" << endl;
        ssInstruct << "> SELECT INDEX " << endl;
        ssInstruct << "> SAVE MESH - M" << endl;

        stringstream ssProgramInfo;
        ssProgramInfo << "PROGRAM: " << "EPHEMERAL-TMP" << endl;
        ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
        ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
        ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
        ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;

        stringstream ssDebug;
        ssDebug << "AMOUT-CAN: " << ofToString(crashedCans.size(), 0) << endl;
        ssDebug << "AMOUT-BALL: " << ofToString(rigidBodies.size(), 0) << endl;
        for (int i = 0; i < crashedCans.size(); i++) {
            ssDebug << "MODEL ID: " << ofToString(i, 3) << " -> POSITION: " << crashedCans[i]->getPosition() << endl;
        }

        //-----------FRONT-LAYER-----------//
        mf.drawGrid();
        mf.drawInfo(ssInstruct, 0, font,fontSize);
        mf.drawInfo(ssProgramInfo, 1, font, fontSize);
        mf.drawInfo(ssDebug, 3, font, fontSize);
        mf.drawInfo(ssGlobalLog, 4, font, fontSize);
        gui.draw();
    }

    void shootBall() {
        shared_ptr< ofxBulletSphere > ss(new ofxBulletSphere());
        ss->create(world.world, cam.getPosition(), 0.75, 1.);
        ss->add();

        ofVec3f frc = -cam.getPosition();
        frc.normalize();
        ss->applyCentralForce(frc * 2000);

        rigidBodies.push_back(ss);
    }

    void createCrasher() {
        shared_ptr< ofxBulletBox > ceiling(new ofxBulletBox());

        ceiling->create(world.world, glm::vec3(0, -30, 0), 2., 50., 1.f, 50.f);
       // ceiling->setProperties(.25, .95);
        ceiling->add();

        glm::vec3 frc = glm::vec3(0, 1, 0);
        ceiling->applyCentralForce(frc * 2000);

        rigidBodies.push_back(ceiling);
    }

    void crashController() {
        glm::vec3 frc = glm::vec3(0, 1, 0);
    }

    void addModel() {
        ofQuaternion tquat;
        tquat.makeRotate(180, 1, 0, 0);

        //btTransform tt = ofGetBtTransform(ofVec3f(ofRandom(-5, 5) * tscale * 30, -15 * tscale * 30, 0), tquat);
        float scaleVal = 0.1;
        //btTransform tt = ofGetBtTransform(glm::vec3(ofRandom(-groundInfo.x/2,groundInfo.x/2),-(0-meshBB[2]),ofRandom(-groundInfo.x/2, groundInfo.x / 2)), tquat);
        btTransform tt = ofGetBtTransform(glm::vec3(50.,-100,50.), tquat);

        shared_ptr<ofxBulletSoftTriMesh> crashedCan(new ofxBulletSoftTriMesh());
        crashedCan->create(&world, mesh, tt, 2);

        crashedCan->getSoftBody()->generateBendingConstraints(3, crashedCan->getSoftBody()->m_materials[0]);
        //crashedCan->getSoftBody()->randomizeConstraints();
        //crashedCan->getSoftBody()->scale(btVector3(0.025 * tscale, 0.025 * tscale, 0.025 * tscale));
        crashedCan->getSoftBody()->scale(btVector3(scaleVal,scaleVal,scaleVal));

        crashedCan->getSoftBody()->m_cfg.collisions = btSoftBody::fCollision::CL_SS + btSoftBody::fCollision::CL_RS;
        crashedCan->getSoftBody()->generateClusters(6);

        crashedCan->add();

        crashedCan->getSoftBody()->m_cfg.piterations = slider_piteration;//2; //Positions solver iterations
        crashedCan->getSoftBody()->m_cfg.kDF = slider_kDF;//1; //Dynamic friction coefficient [0,1]
        crashedCan->getSoftBody()->m_cfg.kSSHR_CL = slider_kSSHR_CL;// 1 // Soft vs soft hardness [0,1] (cluster only)
        crashedCan->getSoftBody()->m_cfg.kSS_SPLT_CL = slider_kSS_SPLT_CL;//0; // Soft vs rigid impulse split [0,1] (cluster only)
        crashedCan->getSoftBody()->m_cfg.kSKHR_CL = slider_kSKHR_CL;//0.1f; // Soft vs soft hardness [0,1] (cluster only)
        crashedCan->getSoftBody()->m_cfg.kSK_SPLT_CL = slider_kSK_SPLT_CL;// 1; // Soft vs rigid impulse split [0,1] (cluster only)
        crashedCan->setStiffness(stiffness.get().x, stiffness.get().y, stiffness.get().z);

        crashedCans.push_back(crashedCan);
    }

    void deleteModel() {
        if (crashedCans.size()) {
            crashedCans.erase(crashedCans.begin());
        }
        if (rigidBodies.size()) {
            rigidBodies.erase(rigidBodies.begin());
        }
    }

    void drawModelPos() {
        for (int i = 0; i < crashedCans.size(); i++) {
            mf.drawFoundCenter(crashedCans[i]->getPosition(),groundInfo.x,glm::vec3(0,1,0));
        }
    }

    void onStiffnessChanged(const glm::vec3& _stiffness) {
        for (int i = 0; i < crashedCans.size(); i++) {
            crashedCans[i]->setStiffness(_stiffness.x, _stiffness.y, _stiffness.z);
        }
        ssGlobalLog << "listener listening!!" << endl;
    };


    void keyPressed(int key) {
        switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 's':
            mf.saveImage();
            break;
        case 'm':
            if(crashedCans.size()>0)mf.saveMesh(crashedCans[slider_selectModelIndex%crashedCans.size()]->getMesh());
            break;
        case 'h':
            bDrawDebug = !bDrawDebug;
            break;
        case 'c':
            //shootBall();
            createCrasher();
            break;
        case 'a':
            addModel();
            break;
        case 'd':
            deleteModel();
            break;
        case ' ':
            ssGlobalLog << "sample text" << endl;
            break;
        }
    }
	
    void keyReleased(int key) {
    };
	void mouseMoved(int x, int y ) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {
        mf.resizeGUI(gui);
    }
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};
   
};
