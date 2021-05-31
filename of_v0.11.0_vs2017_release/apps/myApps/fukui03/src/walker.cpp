#include "Walker.h"
#include "ofApp.h"

Walker::Walker(float _x, float _y) {
    acceleration = ofVec2f(0, 0);
    velocity = ofVec2f(0, 0);
    location = ofVec2f(_x, _y);
    
    targetLocD = 80;
    targetLocR = 30;
    targetLocA = 0;
    change = 1.0;
    maxspeed = 2.5;
    maxforce = 0.05;
    arriveRadius = 300.0;

    float theta = ofRandom(0, 2 * PI);
    targetLoc = ofVec2f(_x + targetLocR * cos(theta), _y + targetLocR * sin(theta));
}


void Walker::run() {
    generateFutureTarget();
    borders();
    update();
}
void Walker::update() {
    velocity += acceleration;
    velocity.limit(maxspeed);
    location += velocity;
    acceleration *= 0;
}

void Walker::applyForce(ofVec2f _force) {
    acceleration += _force;
}

void Walker::seek(ofVec2f _target) {
    ofVec2f desired = _target - location;
    desired.normalize();
    desired *= maxspeed;
    ofVec2f steer = desired - velocity;
    steer.limit(maxforce);
    applyForce(steer);
}

void Walker::arrive(ofVec2f _target) {
    ofVec2f desired = _target - location;
    float d = desired.length();
    desired.normalize();
    if (d < arriveRadius) {
        float m = ofMap(d, 0, arriveRadius, 0, maxspeed);
        desired *= m;
    }
    else {
        desired *= maxspeed;
    }
    ofVec2f steer = desired - velocity;
    steer.limit(maxforce);
    applyForce(steer);
}

void Walker::generateFutureTarget() {

    targetLocA += ofRandom(-change, change);
    targetLoc = velocity.getNormalized();
    targetLoc *= targetLocD;
    targetLoc += location;

    ofVec2f tmp = ofVec2f(1, 0);
    float angle_vel = velocity.angleRad(tmp);
    futureTargetLoc = ofVec2f(targetLoc.x + targetLocR * cos(targetLocA + angle_vel), targetLoc.y + targetLocR * sin(targetLocA + angle_vel));
    seek(futureTargetLoc);
}


void Walker::borders() {
    if (location.x < -targetLocR) { location.x = ofGetWidth() + targetLocR; }
    if (location.y < -targetLocR) { location.y = ofGetHeight() + targetLocR; }
    if (location.x > ofGetWidth()+targetLocR) { location.x = -targetLocR; }
    if (location.y > ofGetHeight()+targetLocR) { location.y = -targetLocR; }
}




void Walker::display() {
    float theta = velocity.angle(ofVec2f(0, 1));
    ofFill();
    ofPushMatrix();
    ofTranslate(location.x, location.y);
    ofRotate(-theta);

    int triSize = 12;
    ofSetColor(20, 180, 100);
    ofBeginShape();
    ofVertex(0, triSize * 2);
    ofVertex(-triSize, -triSize * 2);
    ofVertex(triSize, -triSize * 2);
    ofEndShape();

    ofPopMatrix();
}


ofPoint Walker::returnLoc() {
    return ofPoint(location.x,location.y);
}