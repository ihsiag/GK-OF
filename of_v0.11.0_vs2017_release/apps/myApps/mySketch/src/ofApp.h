#pragma once

#include "ofMain.h"
#include "ofxBullet.h"

class ofApp : public ofBaseApp{

public:
    
    

    ofxBulletWorldSoft			world;

    ofEasyCam camera;
    ofxBulletBox* ground;

    vector< shared_ptr<ofxBulletRigidBody> > rigidBodies;
    vector< shared_ptr<ofxBulletSoftTriMesh> > bunnies;

    ofMesh mesh;

    ofLight light;



    void setup() {
        ofSetFrameRate(60);

        camera.disableMouseInput();
        camera.setDistance(14);

        camera.setPosition(ofVec3f(0, -4.f, -10.f));
        camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));

        world.setup();
        world.setCamera(&camera);


        ground = new ofxBulletBox();
        ground->create(world.world, ofVec3f(0., 5.5, 0.), 0., 50., 1.f, 50.f);
        ground->setProperties(.25, .95);
        ground->add();

        // used from the OF examples/3d/pointPickerExample
        mesh.load("test.ply");

        //mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        camera.enableMouseInput();

        light.setPosition(0, -5, 0);
    };
    
    void update();
    
    void draw() {
        ofEnableDepthTest();
        ofBackground(ofColor(34, 107, 126));

        camera.begin();

        world.drawDebug();

        ofEnableLighting();
        light.enable();
        ofSetColor(34, 107, 126);
        ground->draw();

        ofSetHexColor(0xC4EF02);
        for (int i = 0; i < rigidBodies.size(); i++) {
            rigidBodies[i]->draw();
        }

        ofSetLineWidth(2);
        for (int i = 0; i < bunnies.size(); i++) {
            ofSetHexColor(0xDD3B49);
            bunnies[i]->draw();
            ofSetHexColor(0x3DABB7);
            bunnies[i]->getMesh().drawWireframe();
        }
        ofSetLineWidth(1);



        light.disable();
        ofDisableLighting();

        camera.end();

        ofDisableDepthTest();

        ofSetColor(220, 220, 220);
        ofDrawBitmapString("Shoot ball(spacebar): " + ofToString(rigidBodies.size(), 0) + "\nAdd Bunny(b): " + ofToString(bunnies.size(), 0), 20, 20);
    }

    void keyPressed(int key) {
        if (key == ' ') {
            shared_ptr< ofxBulletSphere > ss(new ofxBulletSphere());
            ss->create(world.world, camera.getPosition(), 0.75, 1.);
            ss->add();

            ofVec3f frc = -camera.getPosition();
            frc.normalize();
            ss->applyCentralForce(frc * 2000);

            rigidBodies.push_back(ss);
        }

        if (key == 'b') {
            ofQuaternion tquat;
            tquat.makeRotate(180, 1, 0, 0);

            float tscale = ofRandom(0.3, 1);
            btTransform tt = ofGetBtTransform(ofVec3f(ofRandom(-5, 5) * tscale * 30, -15 * tscale * 30, 0), tquat);

            shared_ptr<ofxBulletSoftTriMesh> bunny(new ofxBulletSoftTriMesh());
            bunny->create(&world, mesh, tt, 2 * tscale);

            bunny->getSoftBody()->generateBendingConstraints(3, bunny->getSoftBody()->m_materials[0]);

            bunny->getSoftBody()->randomizeConstraints();
            bunny->getSoftBody()->scale(btVector3(0.025 * tscale, 0.025 * tscale, 0.025 * tscale));

            bunny->getSoftBody()->m_cfg.collisions = btSoftBody::fCollision::CL_SS + btSoftBody::fCollision::CL_RS;
            bunny->getSoftBody()->generateClusters(6);

            bunny->add();

            bunny->getSoftBody()->m_cfg.piterations = 2;
            bunny->getSoftBody()->m_cfg.kDF = 1;
            bunny->getSoftBody()->m_cfg.kSSHR_CL = 1;
            bunny->getSoftBody()->m_cfg.kSS_SPLT_CL = 0;
            bunny->getSoftBody()->m_cfg.kSKHR_CL = 0.1f;
            bunny->getSoftBody()->m_cfg.kSK_SPLT_CL = 1;

            //        bunny->setStiffness(0.5, 0.5, 0.5);

            bunnies.push_back(bunny);
        }

        if (key == 127 || key == OF_KEY_DEL) {
            if (bunnies.size()) {
                bunnies.erase(bunnies.begin());
            }
        }
    }
	
    void keyReleased(int key) {};
	void mouseMoved(int x, int y ) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};
   
};
