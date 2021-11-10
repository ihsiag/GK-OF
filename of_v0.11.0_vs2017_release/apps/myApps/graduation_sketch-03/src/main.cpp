#include "ofMain.h"
#include "ofGLProgrammableRenderer.h"
#include "ofApp.h"


//========================================================================
int main( ){
	
	ofGLWindowSettings settings;
	settings.setGLVersion(2, 1);
	settings.setSize(1920, 1080);
	//settings.windowMode = OF_FULLSCREEN;
	ofCreateWindow(settings);
	
	ofRunApp(new ofApp());

}
