#pragma once
#ifndef SCENE_ANIMATION_H  
#define SCENE_ANIMATION_H 

#include "GKScene.h"
#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"
#include "ofEasyCam.h"

class AnimationClass {
public:
	virtual void setup() = 0;
	virtual void resetAnimation() =0;
	virtual void update()=0;
	virtual void draw()=0;
	virtual bool getThisAnimationEndState()=0;
	virtual bool getNextAnimationTriggerState() = 0;
};

class AnimationClassMeshVertex : public AnimationClass {
public:
	int animationFrame;
	int planesNumToShow;
	int dotsNumToShow;
	bool bDrawAll;
	bool bNextAnimationTrigger;
	vector<GKPlane>* gpl;

	AnimationClassMeshVertex(){}
	

	void setup() {
		initParam();
	}

	void setGPL(vector<GKPlane>* _gpl) {
		gpl = _gpl;
	}

	void initParam() {
		animationFrame = 0;
		planesNumToShow = 0;
		dotsNumToShow = 0;
		bDrawAll = false;
		bNextAnimationTrigger = false;
	}

	void update() {
		animationFrame++;
		dotsNumToShow++;
		if (dotsNumToShow > 2) {
			dotsNumToShow = 0;
			planesNumToShow++;
		}
		if (planesNumToShow > gpl->size() / 2)bNextAnimationTrigger = true;
		if (planesNumToShow > gpl->size()) {
			planesNumToShow = gpl->size();
			dotsNumToShow = 3;
			bDrawAll = true;
		}
	}

	void draw() {
		glPointSize(10);
		glColor3f(1, 0, 0);
		glBegin(GL_POINTS);
		for (int i = 0; i < planesNumToShow; i++) {
			if (i < planesNumToShow - 1) {
				for (int j = 0; j < 3; j++) {
					glm::vec3 _p = gpl->at(i).originalMesh.getVertex(j);
					glVertex3f(_p.x, _p.y, _p.z);
				}
			}
			else {
				for (int j = 0; j < dotsNumToShow; j++) {
					glm::vec3 _p = gpl->at(i).originalMesh.getVertex(j);
					glVertex3f(_p.x, _p.y, _p.z);
				}
			}
		}
		glEnd();
	}

	bool getThisAnimationEndState() {
		return bDrawAll;
	}

	bool getNextAnimationTriggerState() {
		return bNextAnimationTrigger;
	}

	void resetAnimation() {
		initParam();
	}
};

class AnimationClassMeshEdge : public AnimationClass {
public:
	int animationFrame;
	int planesNumToShow;
	int dotsNumToShow;
	bool bDrawAll;
	bool bNextAnimationTrigger;
	vector<GKPlane>* gpl;
	
	AnimationClassMeshEdge(){}

	void setup() {
		initParam();
	}

	void setGPL(vector<GKPlane>* _gpl) {
		gpl = _gpl;
	}

	void initParam() {
		animationFrame = 0;
		planesNumToShow = 0;
		dotsNumToShow = 0;
		bDrawAll = false;
		bNextAnimationTrigger = false;
	}

	void update() {
		animationFrame++;
		if(animationFrame%2 == 0)dotsNumToShow++;
		if (dotsNumToShow > 4) {
			dotsNumToShow = 0;
			planesNumToShow++;
		}
		if (planesNumToShow > gpl->size() / 2) bNextAnimationTrigger = true;
		if (planesNumToShow > gpl->size()) {
			planesNumToShow = gpl->size();
			dotsNumToShow = 4;
			bDrawAll = true;
		}
	}

	void draw() {
		glLineWidth(2);
		glColor3f(1, 0, 0);
		for (int i = 0; i < planesNumToShow; i++) {
			glBegin(GL_LINE_STRIP);
			if (i < planesNumToShow - 1) {
				for (int j = 0; j < 4; j++) {
					glm::vec3 _p = gpl->at(i).originalMesh.getVertex(j%3);
					glVertex3f(_p.x, _p.y, _p.z);
				}
			}
			else {
				for (int j = 0; j < dotsNumToShow; j++) {
					glm::vec3 _p = gpl->at(i).originalMesh.getVertex(j%3);
					glVertex3f(_p.x, _p.y, _p.z);
				}
			}
			glEnd();
		}
	}

	bool getNextAnimationTriggerState() {
		return bNextAnimationTrigger;
	}

	bool getThisAnimationEndState() {
		return bDrawAll;
	}

	void resetAnimation() {
		initParam();
	}

};

class AnimationClassMeshFace : public AnimationClass {
public:
	int animationFrame;
	int planesNumToShow;
	bool bDrawAll;
	bool bNextAnimationTrigger;
	vector<GKPlane>* gpl;

	AnimationClassMeshFace() {}

	void setup() {
		initParam();
	}

	void setGPL(vector<GKPlane>* _gpl) {
		gpl = _gpl;
	}

	void initParam() {
		animationFrame = 0;
		planesNumToShow = 0;
		bDrawAll = false;
		bNextAnimationTrigger = false;
	}

	void update() {
		animationFrame++;
		planesNumToShow++;
		if (planesNumToShow > gpl->size())bNextAnimationTrigger = true;
		if (planesNumToShow > gpl->size()) {
			planesNumToShow = gpl->size();
			bDrawAll = true;
		}
	}

	void draw() {
		glLineWidth(2);
		glColor3f(1, 0, 0);
		for (int i = 0; i < planesNumToShow; i++) {
			gpl->at(i).drawInputMesh();
		}	
	}

	bool getNextAnimationTriggerState() {
		return bNextAnimationTrigger;
	}

	bool getThisAnimationEndState() {
		return bDrawAll;
	}

	void resetAnimation() {
		initParam();
	}

};

class AnimationClassPlaneFace : public AnimationClass {
public:
	int animationFrame;
	int planesNumToShow;
	bool bDrawAll;
	bool bNextAnimationTrigger;
	vector<GKPlane>* gpl;

	AnimationClassPlaneFace() {}

	void setup() {
		initParam();
	}

	void setGPL(vector<GKPlane>* _gpl) {
		gpl = _gpl;
	}

	void initParam() {
		animationFrame = 0;
		planesNumToShow = 0;
		bDrawAll = false;
		bNextAnimationTrigger = false;
	}

	void update() {
		animationFrame++;
		planesNumToShow++;
		if (planesNumToShow > gpl->size())bNextAnimationTrigger = true;
		if (planesNumToShow > gpl->size()) {
			planesNumToShow = gpl->size();
			bDrawAll = true;
		}
	}

	void draw() {
		glLineWidth(2);
		glColor3f(1, 0, 0);
		for (int i = 0; i < planesNumToShow; i++) {
			gpl->at(i).drawGKPlane();
		}
	}

	bool getNextAnimationTriggerState() {
		return bNextAnimationTrigger;
	}

	bool getThisAnimationEndState() {
		return bDrawAll;
	}

	void resetAnimation() {
		initParam();
	}

};

class Scene_Animation : public GKScene {
public:
	Scene_Animation() {}

	ofxGKUtils gk;
	stringstream ssGlobalLog;
	ofEasyCam cam;
	unsigned long int currentFrame;
	float time;


	ofMesh meshToAnimate;
	vector<GKPlane> gkPlanesCreatedFromMeshToAnimate;
	vector<GKPlane> gkPlanesCreatedManuallyToAnimate;

	bool bPlayAnimation;
	unsigned long int animationFrame;

	AnimationClassMeshVertex amv;
	AnimationClassMeshEdge ame;
	AnimationClassMeshFace amf;
	AnimationClassPlaneFace apf;
	vector<AnimationClass*> animationClasses;
	int animationIndex;

	void setup();
	void resetScene();
	void update();
	void draw();


	void initParam();
	void initSet();
	void initSliders();
	void resetCamera();
	void initAnimationClasses();
	void resetAnimationClasses();

	void createInfo(stringstream& _ssInstruct, stringstream& _ssProgramInfo, stringstream& _ssDebug);

	void drawMainMesh();

	void toggleAnimation();
	void animate();
	void rotateCamera();

	void animateGKPCFM();
	void animateGKPCM();
	void animateMeshVertex(const float& _animationSpeed, vector<GKPlane>& _gpl);
	void animateMeshEdge(const float& _animationSpeed, vector<GKPlane>& _gpl);
	void animateMeshFace(const float& _animationSpeed, vector<GKPlane>& _gpl);
	void animateIntersection();
	void animateGeneration();
	void animateFilling();
	void animateEffect();



	//-----------NO-InUSE-----------//


	void keyPressed(int key) {
		switch (key) {
		case 's':
			toggleAnimation();
			ssGlobalLog << "PLAY" << endl;
			break;
		case 'r':
			resetAnimationClasses();
			ssGlobalLog << "RESET" << endl;
			break;
		}
	}
	void mousePressed(ofMouseEventArgs& args) {
	}
	void mousePressed(int x, int y, int button) {};
	void windowResized(int w, int h) {
		//gk.resizeGUI(guiOne, 13);
		//gk.resizeGUI(guiTwo, 13);
	}

	//-----------NO-InUSE-----------//
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void mouseEntered(int x, int y) {};
	void mouseExited(int x, int y) {};
	void mouseScrolled(int x, int y, float scrollX, float scrollY) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

private:

};

#endif
