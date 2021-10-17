#pragma once

#ifndef _PARTICLE
#define _PARTICLE

#include "ofMain.h"

class Particle {

public:

    void readyToShow_locus();
    void updatePos_locus();
    void updateArray_locus();
    void show_locus();

    void updatePos_ring();
    void updateArray_ring(ofPoint _pos);
    void show_ring();


    void addAttractionForce(ofPoint _pos);
    void addRepulsionForce(ofPoint _pos);
    void addForce(ofVec2f _force);
    void updateForce();
    void updatePos_force();
    void readyToShow_force(ofPoint _pos);


    void putInside();
    ofPoint returnPos();

    Particle() {} // dont know why but this line seems necessary
    Particle(ofPoint _originalPos);
    float incr_locus;
private:

    ofVec2f pos;
    float dist;
    float theta_locus, distW_locus,distH_locus, r_locus;
    float initialR_ring;
    float xNoise, yNoise;

    float friction,mass;
    ofVec2f vel, force;
    
    static const int maxNum_locus = 2;
    static const int maxNum_ring = 150;
    vector <ofPoint> posArray;
    vector <float> rArray;

};

#endif 
