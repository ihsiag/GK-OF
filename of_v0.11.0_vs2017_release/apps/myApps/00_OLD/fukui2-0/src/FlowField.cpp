#include "ofApp.h"
#include "FlowField.h"

FlowField::FlowField(int _r) {
	zoff = 1.0;
	//resolution = _r;
	resolution = 1;
	cols = ofGetWidth()/ resolution;
	rows = ofGetHeight() / resolution;
	//init();
}


void FlowField::init(){
	int _noiseSeed = int(ofRandom(0, 100));
	float _xoff = 0;
	for (int i = 0; i < cols; i++) {
		float _yoff = 0;
		for (int j = 0; j < rows; j++) {
			float _theta = ofNoise(_noiseSeed, _xoff, _yoff) * 2 * PI;
			
			
		}
	}

}