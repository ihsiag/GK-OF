#include "ofMain.h"
#include "ofGLProgrammableRenderer.h"

#include "Manager.h"
#include "Scene_Room.h"
#include "Scene_Viewer.h"
#include "Scene_Modeler.h"

//========================================================================
int main() {

	auto mainApp = myManager::getInstance();
	mainApp->addRenderer(new Scene_Room());
	mainApp->addRenderer(new Scene_Viewer());
	mainApp->addRenderer(new Scene_Modeler());
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
