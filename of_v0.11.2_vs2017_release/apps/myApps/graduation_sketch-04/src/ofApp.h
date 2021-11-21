#pragma once

#include "ofMain.h"
#include "Class_MyFunctions.h"
#include "ofxBullet.h"
#include "ofxGui.h"
#include "ofEvent.h"


class ofApp : public ofBaseApp{

public:
    //-----------BASIC-----------//
    Class_MyFunctions mf;
    ofEasyCam cam;
    ofTrueTypeFont font;
    ofMesh mesh;
    float meshScaleFactor;
    float meshBB[6];
    ofLight light;

    stringstream ssGlobalLog;

    //-----------FBO-----------//
    ofFbo fbo;

    //-----------PHISICLIB-----------//
    ofxBulletWorldSoft world;

    ofxBulletBox* ground;
    glm::vec3 groundInfo;
    
    vector< shared_ptr<ofxBulletSoftTriMesh> > models;
    vector< shared_ptr<ofxBulletRigidBody> > rigidBodies;
    vector< shared_ptr<ofxBulletRigidBody>> crashers;
    vector< shared_ptr<ofxBulletRigidBody>> kinematicBodies;

    int							mousePickIndex;
    ofVec3f						mousePickPos;

    
    //-----------GLOBALVAL-----------//
    bool bDrawDebug;


    unsigned long int currentFrame;
    float time;
    int fontSize;

    glm::vec2 mouseOnWorldPlane;

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
    ofParameter<btScalar> slider_timestep;
    
    ofParameter<int> slider_selectModelIndex;


    void setup();
    void update();    
    void draw();

    //-----------FOR-BULLET-----------//

    void addKinematicBody();
    void addBox();
    void addCylinder(const glm::vec2& _pos);
    void addModel(const glm::vec2& _pos);
    void deleteModel();
    void drawModelPos();
    void drawBodies();

    //-----------THISTIME-FUNCS-----------//
    void resetCamera();

    void createGUI();
    void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);
    void drawMyGraph();

    //-----------EVENT-FUNCS-----------//
    void mousePickEvent(ofxBulletMousePickEvent& e);
  

    //-----------EVENT-----------//
    void keyPressed(int key) {

        switch (key) {
        case 'r':
            resetCamera();
            break;
        case 'f':
            ofToggleFullscreen();
            break;
        case 's':
            mf.saveImage();
            break;
        case 'm':            
            if (models.size() > 0)mf.saveMesh(models[slider_selectModelIndex % models.size()]->getMesh(),1/meshScaleFactor);
            break;
        case 'h':
            bDrawDebug = !bDrawDebug;
            if (bDrawDebug){
                ssGlobalLog << "DEBUG MODE ON" << endl;
            }
            else {
                ssGlobalLog << "DEBUG MODE OFF" << endl;
            }
            break;
        case 'b':
            addBox();
            break;
        case 'c':
            addCylinder(mouseOnWorldPlane);
            break;
        case 'a':
            addModel(mouseOnWorldPlane);
            break;
        case 'd':
            deleteModel();
            break;
        case ' ':
            break;
        case 'l':
            // �o�b�t�@���N���A���܂��B
            ssGlobalLog.str("");
            // ��Ԃ��N���A���܂��B
            ssGlobalLog.clear(std::stringstream::goodbit);
            ssGlobalLog << "CLEARED LOG" << endl;
            break;
        }
    }
	
    void keyReleased(int key) {
    };
	void mouseMoved(int x, int y ) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {
    };
	void mouseReleased(int x, int y, int button) {
        mousePickIndex = -1;
    };
	void windowResized(int w, int h) {
        mf.resizeGUI(gui);
    }
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};
   
};