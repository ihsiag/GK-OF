#include "walker.h"
#include "ofApp.h"

Walker::Walker(ofPoint _originalPos) {
    acc = ofVec2f(0, 0);
    vel = ofVec2f(0, 0);
    pos = ofVec2f(_originalPos);
    
    targetLocD = 80;
    targetLocR = 30;
    targetLocA = 0;
    change = PI / 2;
    maxspeed = 2.5;
    maxforce = 0.05;
    arriveRadius = 300.0;

    float theta = ofRandom(0, 2 * PI);
    targetLoc = pos + ofVec2f(targetLocR * cos(theta), targetLocR * sin(theta));
}


void Walker::readyToShow() {
    generateFutureTarget();
    borders();
    update();
}
void Walker::update() {
    vel += acc;
    vel.limit(maxspeed);
    pos += vel;
    acc *= 0;
}

void Walker::applyForce(ofVec2f _force) {
    acc += _force;
}

void Walker::seek(ofVec2f _target) {
    ofVec2f desired = _target - pos;
    desired.normalize();
    desired *= maxspeed;
    ofVec2f steer = desired - vel;
    steer.limit(maxforce);
    applyForce(steer);
}

void Walker::arrive(ofVec2f _target) {
    ofVec2f desired = _target - pos;
    float d = desired.length();
    desired.normalize();
    if (d < arriveRadius) {
        float m = ofMap(d, 0, arriveRadius, 0, maxspeed);
        desired *= m;
    }
    else {
        desired *= maxspeed;
    }
    ofVec2f steer = desired - vel;
    steer.limit(maxforce);
    applyForce(steer);
}

void Walker::generateFutureTarget() {

    targetLocA += ofRandom(-change, change);
    targetLoc = vel.getNormalized();
    targetLoc *= targetLocD;
    targetLoc += pos;

    ofVec2f tmp = ofVec2f(1, 0);
    float angle_vel = vel.angleRad(tmp);
    futureTargetLoc = ofVec2f(targetLoc.x + targetLocR * cos(targetLocA + angle_vel), targetLoc.y + targetLocR * sin(targetLocA + angle_vel));
    seek(futureTargetLoc);
}


void Walker::borders() {
    if (pos.x < -targetLocR) { pos.x = ofGetWidth() + targetLocR; }
    if (pos.y < -targetLocR) { pos.y = ofGetHeight() + targetLocR; }
    if (pos.x > ofGetWidth()+targetLocR) { pos.x = -targetLocR; }
    if (pos.y > ofGetHeight()+targetLocR) { pos.y = -targetLocR; }
}




void Walker::show() {
    float theta = vel.angle(ofVec2f(0, 1));
    ofFill();
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
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


ofPoint Walker::returnPos() {
    return ofPoint(pos.x,pos.y);
}