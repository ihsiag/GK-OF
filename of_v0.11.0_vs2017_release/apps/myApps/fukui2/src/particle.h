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

    void readyToShow_ring();
    void updatePos_ring();
    void updateArray_ring(ofPoint _pos);
    void show_ring();

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
    
    static const int maxNum_locus = 1;
    static const int maxNum_ring = 150;
    vector <ofPoint> posArray;
    vector <float> rArray;

};

#endif 
