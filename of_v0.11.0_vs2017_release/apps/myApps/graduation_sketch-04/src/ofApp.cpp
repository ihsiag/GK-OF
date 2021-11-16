#include "ofApp.h"

bool shouldRemoveRigidBody(const shared_ptr<ofxBulletRigidBody>& ab) {
    return ab->getPosition().y > 15;
}

bool shouldRemoveBunny(const shared_ptr<ofxBulletSoftTriMesh>& ab) {
    return ab->getPosition().y > 15;
}


void ofApp::update() {
    //-----------UPDATE-----------//
    mf.defaultUpdate(&cam,&currentFrame, &time);
    world.update();

    //-----------REMOVE-----------//
    ofRemove(rigidBodies, shouldRemoveRigidBody);
    ofRemove(crashedCans, shouldRemoveBunny);
    
    /*
    stringstream ssAll;
    ssAll << ssInstruct.str().c_str() << endl;
    ssAll << ssProgramInfo.str().c_str() << endl;
    */
};

 
/*
void ofApp::onStiffnessChanged(const float& _stiffness) {
    for (int i = 0; i < crashedCans.size(); i++) {
        //crashedCans[i]->setStiffness(_stiffness.x, _stiffness.y, _stiffness.z);
        crashedCans[i]->setStiffness(_stiffness, _stiffness, _stiffness);
    }
    std::cout << "listener listening!!" << endl;
}*/