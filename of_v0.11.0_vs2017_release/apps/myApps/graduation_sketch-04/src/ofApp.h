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
    ofLight light;

    //-----------PHISICLIB-----------//
    ofxBulletWorldSoft world;   
    ofxBulletBox* ground;
    vector< shared_ptr<ofxBulletRigidBody> > rigidBodies;
    vector< shared_ptr<ofxBulletSoftTriMesh> > crashedCans;

    
    //-----------GLOBALVAL-----------//
    bool bDrawDebug;

    float currentFrame;
    float time;
    int fontSize;

    //-----------SLIDER-----------//
    ofxPanel gui;
    ofParameter<glm::vec3> stiffness;


    void setup() {
        mf.setup(&cam);

        //-----------GLOBALVAL-----------//
        bDrawDebug = false;
        currentFrame = -1;
        fontSize = 10;

        //-----------SLIDER-----------//
        /*  gui.add(slider.setup("sliderName", initial, min, max); */
        gui.setup();
        gui.add(stiffness.set("stiffness", glm::vec3(0.8), glm::vec3(0.01), glm::vec3(1.))); // this will create a slider group for your vec3 in the gui.

        //-----------EVENTLISTENER-----------//
        ofEventListener listener = stiffness.newListener([&](glm::vec3&) {this->onStiffnessChanged(stiffness); });
        

        //-----------LOAD-----------//
        font.loadFont("./font/SourceCodePro-Light.ttf", fontSize);
        mesh.load("./3d/test.ply");
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);

        //-----------CAMERA-----------//
        cam.disableMouseInput();
        cam.setDistance(14);
        cam.setPosition(ofVec3f(0, -4.f, -10.f));
        cam.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));



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

        //-----------PROCESS-----------//
        stringstream ssMain;
        ssMain << "Time: " << time << endl;
        ssMain << "Framerate: " << ofToString(ofGetFrameRate(), 0) << endl;
        ssMain << "Debug (h): " << ofToString(bDrawDebug, 0) << endl;
        //ssMain << "draw textures (e): " << ofToString(bDrawFbos, 0) << endl;
        ssMain << "Shoot ball(spacebar): " << ofToString(rigidBodies.size(), 0) << endl;
        ssMain << "Add crashedCan(a): " << ofToString(crashedCans.size(), 0) << endl;
        ssMain << "Delete (d)" << endl;
        ssMain << "Save Image (s)" << endl;
        


        //-----------FRONT-LAYER-----------//
        mf.drawGrid();
        mf.drawInfo(ssMain, font,fontSize);
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

    void AddModel() {
        ofQuaternion tquat;
        tquat.makeRotate(180, 1, 0, 0);

        float tscale = ofRandom(0.3, 1);
        //btTransform tt = ofGetBtTransform(ofVec3f(ofRandom(-5, 5) * tscale * 30, -15 * tscale * 30, 0), tquat);
        btTransform tt = ofGetBtTransform(glm::vec3(0,50,200), tquat);

        shared_ptr<ofxBulletSoftTriMesh> crashedCan(new ofxBulletSoftTriMesh());
        crashedCan->create(&world, mesh, tt, 2 * tscale);

        crashedCan->getSoftBody()->generateBendingConstraints(3, crashedCan->getSoftBody()->m_materials[0]);

        crashedCan->getSoftBody()->randomizeConstraints();
        crashedCan->getSoftBody()->scale(btVector3(0.025 * tscale, 0.025 * tscale, 0.025 * tscale));

        crashedCan->getSoftBody()->m_cfg.collisions = btSoftBody::fCollision::CL_SS + btSoftBody::fCollision::CL_RS;
        crashedCan->getSoftBody()->generateClusters(6);

        crashedCan->add();

        crashedCan->getSoftBody()->m_cfg.piterations = 2;
        crashedCan->getSoftBody()->m_cfg.kDF = 1;
        crashedCan->getSoftBody()->m_cfg.kSSHR_CL = 1;
        crashedCan->getSoftBody()->m_cfg.kSS_SPLT_CL = 0;
        crashedCan->getSoftBody()->m_cfg.kSKHR_CL = 0.1f;
        crashedCan->getSoftBody()->m_cfg.kSK_SPLT_CL = 1;
        crashedCan->setStiffness(stiffness.get().x, stiffness.get().y, stiffness.get().z);

        crashedCans.push_back(crashedCan);
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
            shootBall();
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
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};
   
};
