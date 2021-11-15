#include "ofApp.h"

bool shouldRemoveRigidBody(const shared_ptr<ofxBulletRigidBody>& ab) {
    return ab->getPosition().y > 15;
}

bool shouldRemoveBunny(const shared_ptr<ofxBulletSoftTriMesh>& ab) {
    return ab->getPosition().y > 15;
}


void ofApp::update() {
    mf.defaultUpdate(&currentFrame, &time);
    world.update();
    ofRemove(rigidBodies, shouldRemoveRigidBody);
    ofRemove(crashedCans, shouldRemoveBunny);
    /*
    for (int i = 0; i < crashedCans.size(); i++) {
        crashedCans[i]->setStiffness(stiffness.get().x, stiffness.get().y, stiffness.get().z);
        crashedCans[i]->setStiffness(stiffness.get().x, stiffness.get().y, stiffness.get().z);
        crashedCans[i]->updateMesh(crashedCans[i]->getMesh());
    }*/
};

 
/*
void ofApp::onStiffnessChanged(const float& _stiffness) {
    for (int i = 0; i < crashedCans.size(); i++) {
        //crashedCans[i]->setStiffness(_stiffness.x, _stiffness.y, _stiffness.z);
        crashedCans[i]->setStiffness(_stiffness, _stiffness, _stiffness);
    }
    std::cout << "listener listening!!" << endl;
}*/