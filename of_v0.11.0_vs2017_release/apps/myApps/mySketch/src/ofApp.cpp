#include "ofApp.h"

bool shouldRemoveRigidBody(const shared_ptr<ofxBulletRigidBody>& ab) {
    return ab->getPosition().y > 15;
}

bool shouldRemoveBunny(const shared_ptr<ofxBulletSoftTriMesh>& ab) {
    return ab->getPosition().y > 15;
}

void ofApp::update() {
    world.update();
    ofRemove(rigidBodies, shouldRemoveRigidBody);
    ofRemove(bunnies, shouldRemoveBunny);
};

