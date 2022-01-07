#include "ofMain.h"
#include "ofApp.h"

#include "Scene_Sample1.h"
#include "Scene_Sample2.h"



//========================================================================
int main( ){
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	//// this kicks off the running of my app
	//// can be OF_WINDOW or OF_FULLSCREEN
	//// pass in width and height too:
	//ofRunApp(new ofApp());

    auto mainApp = ofApp::getInstance();
    mainApp->addGKScene(new Scene_Sample1());
    mainApp->addGKScene(new Scene_Sample2());

    ofGLFWWindowSettings settings;
    settings.multiMonitorFullScreen = true;
    //settings.setSize(1920, 1080);
    //settings.setPosition(glm::vec2(100, 100));
    //settings.decorated = false;
    std::shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();

}
