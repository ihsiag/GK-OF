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

    //-----------PHISICLIB-----------//
    ofxBulletWorldSoft world;   
    ofxBulletBox* ground;
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


    void setup() {
        mf.setup(&cam);
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

        //-----------EVENTLISTENER-----------//
        ofEventListener listener = stiffness.newListener([&](glm::vec3&) {this->onStiffnessChanged(stiffness); });

        //-----------LOAD-----------//
        font.loadFont("./font/SourceCodePro-Light.ttf", fontSize);
        mesh.load("./3d/test-normal.ply");
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
        ground->create(world.world, glm::vec3(0.), 0., 50., 1.f, 50.f);
        ground->setProperties(.25, .95);
        ground->add();

        light.setPosition(0, -200, 0);
        //light.boom(100);
        light.setScale(glm::vec3(50));

        //-----------GO-----------//
        cam.enableMouseInput();
    }

    void onStiffnessChanged(const glm::vec3& _stiffness) {
        for (int i = 0; i < crashedCans.size(); i++) {
            crashedCans[i]->setStiffness(_stiffness.x, _stiffness.y, _stiffness.z);
        }
        std::cout << "listener listening!!" << endl;
    };

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

        //-----------INFO-----------//
        stringstream ssInstruct;
        ssInstruct << "DEBUG     - H" << endl;
        ssInstruct << "CAMERA    - MOUSE" << endl;
        ssInstruct << "BALL      - SPACEBAR" << endl;
        ssInstruct << "ADD MODEL - A" << endl;
        ssInstruct << "DELETE    - D" << endl;
        ssInstruct << "SAVE IMG  - S" << endl;

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

        stringstream ssAll;
        ssAll << ssInstruct.str().c_str() << endl;
        ssAll << ssProgramInfo.str().c_str() << endl;

        //-----------FRONT-LAYER-----------//
        mf.drawGrid();
        mf.drawInfo(ssInstruct, 0, font,fontSize);
        mf.drawInfo(ssProgramInfo, 1, font, fontSize);
        mf.drawInfo(ssDebug, 2, font, fontSize);
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

    void AddModel() {
        ofQuaternion tquat;
        tquat.makeRotate(180, 1, 0, 0);

        float tscale = ofRandom(0.3, 1);
        //btTransform tt = ofGetBtTransform(ofVec3f(ofRandom(-5, 5) * tscale * 30, -15 * tscale * 30, 0), tquat);
        btTransform tt = ofGetBtTransform(glm::vec3(ofRandom(-500,500),-(0-meshBB[2]),ofRandom(-500,500)), tquat);

        shared_ptr<ofxBulletSoftTriMesh> crashedCan(new ofxBulletSoftTriMesh());
        crashedCan->create(&world, mesh, tt, 2 * tscale);

        crashedCan->getSoftBody()->generateBendingConstraints(3, crashedCan->getSoftBody()->m_materials[0]);

        crashedCan->getSoftBody()->randomizeConstraints();
        crashedCan->getSoftBody()->scale(btVector3(0.025 * tscale, 0.025 * tscale, 0.025 * tscale));

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

    void drawModelPos() {
        for (int i = 0; i < crashedCans.size(); i++) {
            glm::vec3 _pos = crashedCans[i]->getPosition();
            glLineWidth(1);
            glColor4f(1, 0, 0, 0.7);
            glBegin(GL_LINES);
            glVertex3f(_pos.x, 0, -50);
            glVertex3f(_pos.x, 0, 50);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(-50, 0, _pos.z);
            glVertex3f(50, 0, _pos.z);
            glEnd();
        }
    }


    
   


    void keyPressed(int key) {
        switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 's':
            mf.saveImage();
            break;
        case 'h':
            bDrawDebug = !bDrawDebug;
            break;
        case ' ':
            //shootBall();
            createCrasher();
            break;
        case 'a':
            AddModel();
            break;
        case 'd':
            if (crashedCans.size()) {
                crashedCans.erase(crashedCans.begin());
            }
            if (rigidBodies.size()) {
                rigidBodies.erase(rigidBodies.begin());
            }
        }
    }
	
    void keyReleased(int key) {
    };
	void mouseMoved(int x, int y ) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {
        gui.setPosition(mf.myGUIPos());
        gui.setDefaultWidth(mf.myGUIWidth());
        gui.setWidthElements(mf.myGUIWidth());
    }
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};
   
};
