
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
	//-----------INIT-----------//
	stringstream ssInstruct;
	stringstream ssProgramInfo;
	stringstream ssDebug;

	//-----------PROCESS-----------//
	

	//-----------3D-LAYER-----------//


	cam.begin();
	glEnable(GL_DEPTH_TEST);
	if (bPlayAnimation)animate();
	drawMainMesh();
	
	glDisable(GL_DEPTH_TEST);
	cam.end();

	//-----------2D-LAYER-----------//

	//-----------INFO-----------//
    createInfo(ssInstruct, ssProgramInfo, ssDebug);

	//-----------FRONT-LAYER-----------//
    gk.drawInfo(ssInstruct, 1);
    gk.drawInfo(ssProgramInfo, 0);
    gk.drawInfo(ssDebug, 4);
    gk.drawInfo(ssGlobalLog, 5);
}


void Scene_Animation::initParam() {
	bPlayAnimation = false;
	animationFrame = 0;
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

void Scene_Animation::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
    //-----------INFO-----------//--later put into update func.
    _ssInstruct << "INSTRUCTIONS: " << endl;
    _ssInstruct << "START / STOP             - S" << endl;



    _ssProgramInfo << "PROGRAM: " << "SIMULATED EXPERIENCE OR DREAM" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    _ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;
    _ssProgramInfo << "CAMERA LOOK DIR: " << cam.getLookAtDir() << endl;
}

void Scene_Animation::drawMainMesh() {
	glColor4f(0, 1, 0, 0.4);
	meshToAnimate.drawWireframe();
	glColor4f(0, 0, 1, 0.4);
	meshToAnimate.drawFaces();
}


void Scene_Animation::toggleAnimation() {
	bPlayAnimation = !bPlayAnimation;
	animationFrame = 0;
}

void Scene_Animation::animate() {

	int index = animationFrame/2;
	if (index > gkPlanesCreatedFromMeshToAnimate.size()*3)index = gkPlanesCreatedFromMeshToAnimate.size()*3;
	glPointSize(10);
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	for (int i = 0; i < index; i++) {	
		glm::vec3 _p = gkPlanesCreatedFromMeshToAnimate[i / 3].originalMesh.getVertex(i % 3);
		glVertex3f(_p.x,_p.y,_p.z);
	}
	glEnd();
	index = animationFrame / 2;
	if (index > gkPlanesCreatedManuallyToAnimate.size())index = gkPlanesCreatedManuallyToAnimate.size();
	for (int i = 0; i < index; i++) {
		gkPlanesCreatedManuallyToAnimate[i].drawGKPlane();
	}
	animationFrame++;
}

void Scene_Animation::rotateCamera() {

}

void Scene_Animation::animateGKPCFM() {

}