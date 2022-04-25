#include "ofMain.h"
#include "ofGLProgrammableRenderer.h"

#include "ofApp.h"
#include "Scene_One.h"
#include "Scene_Two.h"
#include "Scene_Three.h"


//========================================================================
int main() {

	auto mainApp = ofApp::getInstance();
	mainApp->addGKScene(new Scene_One());
	mainApp->addGKScene(new Scene_Two());
	mainApp->addGKScene(new Scene_Three());

	////== BEGIN - RYO SHIRAKI ==//

	//ofGLWindowSettings settings;
	//
	//settings.setGLVersion(2, 1);
	//settings.setSize(1300, 800);
	////settings.windowMode = OF_FULLSCREEN;
	//settings.windowMode = OF_WINDOW;
	//settings.setPosition(glm::vec2(1920 + 80, 80));
	////ofCreateWindow(settings);

	//std::shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	//ofRunApp(mainWindow, mainApp);
	//ofRunMainLoop();

	////== END - RYO SHIRAKI ==//


	
	//== BEGIN - SATORU HIGA ==//

	//== END - SATORU HIGA ==//

	//== BEGIN - MY MIX ==//
	ofAppGLFWWindow window;
	window.setNumSamples(8);
	window.setWindowPosition(1920 + 80, 80);

	ofSetupOpenGL(&window, 1300, 800, OF_WINDOW);

	ofRunApp(mainApp);

	//== END - MY MIX ==//

}
