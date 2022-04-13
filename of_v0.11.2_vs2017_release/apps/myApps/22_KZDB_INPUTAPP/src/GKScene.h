#pragma once
#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

class GKScene {
protected:
	ofxGKUtils gk;
public:
	virtual ~GKScene() {}

	virtual void setup() = 0;
	virtual void resetScene() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	

	virtual void keyPressed(int key) = 0;
	virtual void keyReleased(int key) = 0;
	virtual void mouseMoved(int x, int y) = 0;
	virtual void mouseDragged(int x, int y, int button) = 0;
	virtual void mousePressed(ofMouseEventArgs& args) {};
	virtual void mousePressed(int x, int y, int button) = 0;
	virtual void mouseReleased(int x, int y, int button) = 0;
	virtual void mouseEntered(int x, int y) = 0;
	virtual void mouseExited(int x, int y) = 0;
	virtual void mouseScrolled(int x, int y, float scrollX, float scrollY) = 0;
	virtual void windowResized(int w, int h) = 0;
	virtual void dragEvent(ofDragInfo dragInfo) = 0;
	virtual void gotMessage(ofMessage msg) = 0;

private:
};
