#include "particle.h"
#include "ofApp.h"

Particle::Particle(ofPoint _originalPos) {
    pos = ofVec2f(_originalPos);
    dist = 1;
    friction = 0.001;
    mass = 1;

    incr_locus = 0;
    distW_locus = ofGetWidth()/2 ;
    distH_locus = ofGetHeight() / 2;
    r_locus = 1;
    initialR_ring = 5;


}


void Particle::readyToShow_locus() {
    updatePos_locus();
    updateArray_locus();
    putInside();
}


void Particle::updatePos_locus() {
    theta_locus = 2*PI*ofNoise(incr_locus,pos.x*0.0001, pos.y*0.0001);
    //theta_locus = 2 * PI* ofNoise(incr_locus, xNoise, yNoise);
    pos += ofVec2f(-cos(theta_locus)*5, sin(theta_locus));
}

void Particle::updatePos_ring() {


}

void Particle::updateArray_locus() {
    posArray.push_back(pos);
    if (posArray.size() > maxNum_locus) {
        posArray.erase(posArray.begin());
    }
}

void Particle::updateArray_ring(ofPoint _pos) {
    if (posArray.size() < maxNum_ring) {
        posArray.push_back(_pos);
        float _r = initialR_ring;
        rArray.push_back(_r);
    }
    if (posArray.size() > maxNum_ring) {
        posArray.erase(posArray.begin());
        rArray.erase(rArray.begin());
    }

}
void Particle::addForce(ofVec2f _force) {
    force += _force / mass;

    
}

void Particle::updateForce() {
    force -= vel * friction;
}

void Particle::updatePos_force() {
    vel += force;
    pos += vel;
}

void Particle::readyToShow_force(ofPoint _pos) {
    //updateForce();
    addRepulsionForce(_pos);
    updatePos_force();
    ofSetColor(255);
    ofDrawCircle(pos, 1);
}


void Particle::addAttractionForce(ofPoint _pos) {
    float _r = 20;
    float _scl = 0.1;

    ofVec2f _posOfForce;
    _posOfForce = _pos;
    //posOfForce.set(mouseX,mouseY);
    ofVec2f _diff = _pos - _posOfForce;
    float _length = _diff.length();
    bool _closeEnough = true;
    if (_r > 0) {
        if (_length > _r) {
            _closeEnough = false;
        }
    }
    if (_closeEnough == true) {
        float _pct = 1 - (_length / _r);
        _diff.normalize();
        force -= _diff * _scl * _pct;
    }
}


void Particle::addRepulsionForce(ofPoint _pos) {
    float _r = 20;
    float _scl = 0.1;

    ofVec2f _posOfForce;
    _posOfForce = _pos;
    //posOfForce.set(mouseX,mouseY);
    ofVec2f _diff = pos - _posOfForce;
    float _length = _diff.length();
    bool _closeEnough = true;
    if (_r > 0) {
        if (_length > _r) {
            _closeEnough = false;
        }
    }
    if (_closeEnough == true) {
        float _pct = 1 - (_length / _r);
        _diff.normalize();
        force += _diff * _pct * _scl;
    }

}


void Particle::show_locus() {
    ofSetColor(255);
    
    for (int i = 0; i < posArray.size(); i++) {
        ofPoint _center = posArray[i];
        ofSetColor(255, 250 + (i- posArray.size())*10);
        ofDrawCircle(_center, r_locus);
    } 
}

void Particle::show_ring() {
    ofSetColor(255);
    for (int i = 0; i < posArray.size(); i++) {
        ofPoint _center = posArray[i];
        float _r = rArray[i];
        _r += 1;
        rArray[i] = _r;
        ofDrawCircle(_center, _r);
        
    }

}



void Particle::putInside() {
    if (pos.x + distW_locus < 0) { pos.x = ofGetWidth() + distW_locus; }
    if (pos.y + distH_locus < 0) { pos.y = ofGetHeight() + distH_locus; }
    if (pos.x - distW_locus > ofGetWidth()) { pos.x = -distW_locus; }
    if (pos.y - distH_locus > ofGetHeight()) { pos.y = -distH_locus; }
}

ofPoint Particle::returnPos() {
    return ofPoint(pos.x, pos.y);
}