#ifndef _WALKER
#define _WALKER

#include "ofMain.h"

class Walker {

public:

    void readyToShow();
    void update();
    void applyForce(ofVec2f force);
    void seek(ofVec2f _target);
    void arrive(ofVec2f _target);
    void show();
    void generateFutureTarget();
    void borders();
    ofPoint returnPos();
    Walker() {} // dont know why but this line seems necessary
    Walker(ofPoint _originalPos);

private:

    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
    ofVec2f targetLoc;
    ofVec2f futureTargetLoc;

    float targetLocD; //distance from a walker to the center of target
    float targetLocR; //radius(area) : a possible pos of the future target
    float targetLocA; //domain of angle
    float change; // brings slight changes to targetLocA
    float maxforce;
    float maxspeed;
    float arriveRadius;

};

#endif 
