#include "ofMain.h"
#include "ofGLProgrammableRenderer.h"

#include "ofApp.h"
#include "Scene_One.h"


//========================================================================
int main() {

	auto mainApp = ofApp::getInstance();
	mainApp->addGKScene(new Scene_One());

	ofGLWindowSettings settings;

	settings.setGLVersion(2, 1);
	settings.setSize(1600, 900);
	settings.windowMode = OF_FULLSCREEN;
	//ofCreateWindow(settings);

	std::shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

	//ofRunApp(new ofApp());

}
