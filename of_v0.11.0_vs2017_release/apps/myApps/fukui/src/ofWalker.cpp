#include "ofWalker.h"
#include "ofApp.h"

ofWalker::ofWalker(float  _x, float _y) {
	location.set(_x, _y);
	velocity.set(0, 0);
	acceleration(0, 0);
	r = 3.0;
	maxspeed = 4;
	maxforce = 0.1;
}



void ofWalker::update(){	
	velocity += acceleration;
	velocity.limit(maxspeed);
	location += velocity;
	acceleration *= 0;
}

void ofWalker::applyForce(ofVec2f _force) {
	acceleration += _force;
}

void ofWalker::seek(ofVec2f _target) {
	ofVec2f desired = _target - location;
	desired.normalize();
	desired *= maxspeed;
	ofVec2f steer = desired - velocity;
	steer.limit(maxforce);
	applyForce(steer);
}

void ofWalker::output() {
	float theta = velocity.angle(ofVec2f(0, 1));
	ofFill();
	ofPushMatrix();
	ofTranslate(location.x, location.y);
	ofRotate(-theta);

	ofSetColor(0, 0, 0, 175);
	ofBeginShape();
	ofVertex(0, r * 2);
	ofVertex(-r, -r * 2);
	ofVertex(r, -r * 2);
	ofEndShape();

	ofPopMatrix();
}