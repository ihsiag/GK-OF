#include "ofMain.h"
#include "ofGLProgrammableRenderer.h"

#include "ofApp.h"
#include "Scene_One.h"
#include "Scene_Two.h"


//========================================================================
int main() {

	auto mainApp = ofApp::getInstance();
	mainApp->addGKScene(new Scene_One());
	mainApp->addGKScene(new Scene_Two());

	ofGLWindowSettings settings;

	settings.setGLVersion(2, 1);
	settings.setSize(1600, 900);
	//settings.windowMode = OF_FULLSCREEN;
	settings.windowMode = OF_WINDOW;
	settings.setPosition(glm::vec2(1920 + 80, 80));
	//ofCreateWindow(settings);

	std::shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

	//ofRunApp(new ofApp());

}
