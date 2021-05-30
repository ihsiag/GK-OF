#include "ofMain.h"
#include "ofApp.h"
#include "Constants.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(4, 1);
    settings.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
