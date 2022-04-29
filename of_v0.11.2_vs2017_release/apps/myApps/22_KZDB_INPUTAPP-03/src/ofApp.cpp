#include "ofApp.h"

std::shared_ptr<ofApp> ofApp::instance;

void ofApp::addGKScene(GKScene* _gkScene) {
	gkScenes.push_back(_gkScene);
}

//--------------------------------------------------------------
void ofApp::setup(){

	currentSceneIndex = 0;
	
	for (GKScene* gs : gkScenes) {
		glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		//ofPushStyle();
		gs->setDataSet(&dataSet);
		gs->initScene();
		//ofPopStyle();
		glPopAttrib();
		glPopClientAttrib();
	}
	
	
}

//--------------------------------------------------------------
void ofApp::update(){
	//check bNext / bBack in each scene's SceneAdminInfo;
	if (gkScenes[currentSceneIndex]->goNext()) { 
		dataSet = gkScenes[currentSceneIndex]->setBackDataSet();
		goNextScene();
	}
	if (gkScenes[currentSceneIndex]->goBack()) {
		dataSet = gkScenes[currentSceneIndex]->setBackDataSet();
		goBackScene();
	};
	//then default update
	gkScenes[currentSceneIndex]->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	gkScenes[currentSceneIndex]->draw();
}
