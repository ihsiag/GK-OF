
#include "Scene_Animation.h"


void Scene_Animation::setup() {
	initParam();
	initSet();
	initSliders();
	resetCamera();
	
    gk.setup(&ssGlobalLog);
	gk.setCam(&cam);
	setLight();
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
	initAnimationClasses();
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
	ofEnableLighting();
	for(auto&l:lights)l.enable();
	//gk.draw3DPlaneGrid(10,50,glm::vec3(0,1,0),1,glm::vec4(0.6));
	gk.draw3DBox(glm::vec3(0), 100, 100, 160, 1, glm::vec4(1, 1, 1, 0.5));
	if (bPlayAnimation)animate();
	render();
	for (auto& l : lights)l.disable();
	ofDisableLighting();
	glDisable(GL_DEPTH_TEST);
	cam.end();

	//-----------2D-LAYER-----------//
	gk.drawGrid();
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
	animationIndex = 0;
	bHideMesh = false;
}

void Scene_Animation::initSet() {
	gk.setup(&ssGlobalLog);
	gk.setCam(&cam);
}

void Scene_Animation::initSliders() {
}

void Scene_Animation::resetCamera() {
	//cam.setDistance(14);
	//cam.enableOrtho();
	cam.setPosition(glm::vec3(180, 180, 180));
	//cam.setVFlip(true);
	cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
}

void Scene_Animation::createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug) {
    //-----------INFO-----------//--later put into update func.
    _ssInstruct << "INSTRUCTIONS: " << endl;
    _ssInstruct << "START / STOP             - S" << endl;
	_ssInstruct << "RESET             - R" << endl;




    _ssProgramInfo << "PROGRAM: " << "SIMULATED EXPERIENCE OR DREAM" << endl;
    _ssProgramInfo << "DEVELOPER: " << "GAISHI KUDO" << endl;
    _ssProgramInfo << "TIME: " << ofToString(time, 0) << endl;
    _ssProgramInfo << "FRAMERATE: " << ofToString(ofGetFrameRate(), 0) << endl;
    _ssProgramInfo << "CAMERA: " << cam.getPosition() << endl;
    _ssProgramInfo << "CAMERA LOOK DIR: " << cam.getLookAtDir() << endl;
}



void Scene_Animation::drawMainMesh() {
	glColor4f(0, 0, 1, 0.4);
	meshToAnimate.drawFaces();
	glLineWidth(1);
	glColor4f(0, 1, 0, 0.4);
	meshToAnimate.drawWireframe();
	
}

void Scene_Animation::toggleAnimation() {
	bPlayAnimation = !bPlayAnimation;
}

void Scene_Animation::initAnimationClasses() {
	animationClasses.push_back(&amv);
	animationClasses.push_back(&ame);
	animationClasses.push_back(&amf);
	animationClasses.push_back(&apf);
	animationClasses.push_back(&afc);

	amv.setGPL(&gkPlanesCreatedFromMeshToAnimate);
	ame.setGPL(&gkPlanesCreatedFromMeshToAnimate);
	amf.setGPL(&gkPlanesCreatedFromMeshToAnimate);
	apf.setGPL(&gkPlanesCreatedFromMeshToAnimate);
	afc.setGPL(&gkPlanesCreatedFromMeshToAnimate);
	afc.setCam(&cam);
	afc.setHideMesh(&bHideMesh);
	
	for (auto& ac : animationClasses) {
		ac->setup();
	}
}

void Scene_Animation::resetAnimationClasses() {
	animationIndex = 0;
	for (auto& ac : animationClasses) {
		ac->resetAnimation();
	}
}

void Scene_Animation::animate() {
	if (animationClasses[animationIndex]->getNextAnimationTriggerState())animationIndex++; //&& animationIndex < animationClasses.size() - 1
	if (animationIndex == animationClasses.size())resetAnimationClasses();
	for (int i = 0; i < animationIndex+1; i++) {
		animationClasses[i]->update();
	}
	rotateCamera();
	animationFrame++;
}
void Scene_Animation::render() {
	if (animationIndex > 3) {
		for (int i = 3; i < animationIndex+1; i++) {
			animationClasses[i]->draw();
		}
	}
	else {
		for (auto& ac : animationClasses) { ac->draw(); }
	}
	
	if(!bHideMesh)drawMainMesh();
}

void Scene_Animation::rotateCamera() {
	float rotateR = sqrt(pow(140,2)*2);
	float rotationSpeed = animationFrame * 0.002;
	cam.setPosition(glm::vec3(rotateR * cos(PI/4+rotationSpeed), 100, rotateR * sin(PI/4+rotationSpeed)));
	cam.lookAt(ofVec3f(0, 0, 0), glm::vec3(0, 1, 0));
}

void Scene_Animation::setLight() {
	lights.emplace_back(ofLight());
	lights.emplace_back(ofLight());
	float rotateR = sqrt(pow(140, 2) * 2);
	lights[0].setPosition(rotateR * cos(PI / 4), cam.getPosition().y, rotateR * sin(PI / 4));
	lights[1].setPosition(rotateR * cos(PI / 2), cam.getPosition().y, rotateR * sin(PI / 4));	
}