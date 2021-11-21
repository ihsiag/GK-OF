#ifndef _WALKER
#define _WALKER

#include "ofMain.h"

class Walker {

public:

    void run();
    void update();
    void applyForce(ofVec2f force);
    void seek(ofVec2f _target);
    void arrive(ofVec2f _target);
    void display();
    void generateFutureTarget();
    void borders();
    ofPoint returnLoc();
    Walker() {} // dont know why but this line seems necessary
    Walker(float x, float y);

private:

    ofVec2f location;
    ofVec2f velocity;
    ofVec2f acceleration;
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
