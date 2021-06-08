#include "ofMain.h"
#include "ofGLProgrammableRenderer.h"
#include "ofApp.h"


//========================================================================
int main( ){
	
	ofGLWindowSettings settings;
	settings.setGLVersion(2, 1);
	//settings.setSize(1024, 768);
	settings.setSize(1920, 1080);
	ofCreateWindow(settings);
	

	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	
	
	ofRunApp(new ofApp());

}
