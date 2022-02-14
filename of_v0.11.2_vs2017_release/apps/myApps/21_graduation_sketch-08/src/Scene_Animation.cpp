
#include "Scene_Animation.h"


void Scene_Animation::setup() {
	initParam();
	initSet();
	initSliders();
	resetCamera();
	
    gk.setup(&ssGlobalLog);
	gk.setCam(&cam);
}

void Scene_Animation::resetScene() {
	initParam();
    resetCamera();

    gkPlanesCreatedFromMeshToAnimate.erase(gkPlanesCreatedFromMeshToAnimate.begin(), gkPlanesCreatedFromMeshToAnimate.end());
    gkPlanesCreatedManuallyToAnimate.erase(gkPlanesCreatedManuallyToAnimate.begin(), gkPlanesCreatedManuallyToAnimate.end());
    
    ssGlobalLog.str("");
    ssGlobalLog.clear(std::stringstream::goodbit);
    ssGlobalLog << "CLEARED LOG" << endl;
    ssGlobalLog << "CLEARED-ARRAYS" << endl;

    gk.importGK3D(gk.findLatestFilePath("./gk3dExported/", "gk3d"), meshToAnimate, gkPlanesCreatedFromMeshToAnimate, gkPlanesCreatedManuallyToAnimate);

}

void Scene_Animation::update() {
	gk.defaultUpdate(&cam, &currentFrame, &time);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Scene_Animation::draw() {
	cam.begin();
	
	glColor3f(0, 1, 0);
	meshToAnimate.drawWireframe();
	glColor4f(0, 0, 1, 0.5);
	meshToAnimate.drawFaces();

	for (auto& gkcfm : gkPlanesCreatedFromMeshToAnimate) {
		gkcfm.drawInputMesh();
	}
	for (auto& gkcm : gkPlanesCreatedManuallyToAnimate) {
		gkcm.drawGKPlane();
	}
	cam.end();
	
}


void Scene_Animation::initParam() {

}

void Scene_Animation::initSet() {
}

void Scene_Animation::initSliders() {
}

void Scene_Animation::resetCamera() {
	cam.setDistance(14);
	//cam.enableOrtho();
	cam.setPosition(glm::vec3(180, 180, 180));
	//cam.setVFlip(true);
	cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
}