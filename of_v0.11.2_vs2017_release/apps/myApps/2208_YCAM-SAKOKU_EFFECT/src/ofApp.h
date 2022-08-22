#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp {

public:
	ofxGKUtils gk;
	ofFbo fbo;
	ofShader shader;
	unsigned long int currentFrame;

	ofEasyCam cam;
	ofImage texture;

	ofRectangle area;


	// ------------
	void loadShader() {
		shader.load("./shaders/sample.vert", "./shaders/sample.frag");
		if (shader.isLoaded()) {
			std::cout << "shaders ok" << std::endl;
		}
		else {
			std::cout << "no" << std::endl;
		}
	}
	void initFbo() {
		fbo.allocate(4000, 4000, GL_RGBA);
	}
	void initBasic() {
		ofSetBackgroundAuto(true);
		ofSetBackgroundColor(220);
		ofEnableAlphaBlending();
		//ofEnableBlendMode(); //OF_BLENDMODE_DISABLED, OF_BLENDMODE_ALPHA, OF_BLENDMODE_ADD, OF_BLENDMODE_SUBTRACT, OF_BLENDMODE_MULTIPLY, OF_BLENDMODE_SCREEN
		ofSetFrameRate(30);
		ofEnableAntiAliasing();
		//ofEnableDepthTest();
		ofSetWindowTitle("YCAM-SAKOKU_RGB-EFFECT : by Gaishi Kudo");
		currentFrame = 0;
	}
	void initCam() {
		cam.setNearClip(0.1);
		cam.setFarClip(1000);
		cam.setPosition(0, 0, 500);
		cam.enableOrtho();
		cam.disableMouseInput();
	}
	void initShader() {
		texture;
		texture.loadImage("./shaders/tex/sample2.png");
	}

	// -----------
	void makeArea() {
		area = ofRectangle(-2000 / 2, -2000 / 2, 2000, 2000);
	}
	void fboRun() {
		/*glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
		makeArea();
		cam.begin();
		cam.lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		texture.getTexture().bind();
		shader.begin();

		ofMatrix4x4 modelMatrix;
		ofMatrix4x4 viewMatrix;
		viewMatrix = ofGetCurrentViewMatrix();
		ofMatrix4x4 projectionMatrix;
		projectionMatrix = cam.getProjectionMatrix();
		ofMatrix4x4 mvpMatrix;
		mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;
		
		shader.setUniformMatrix4f("modelViewProjectionMatrix", mvpMatrix);
		shader.setUniformTexture("u_texture_0", texture.getTexture(), 0);
		glm::vec2 imgSize = glm::vec2(texture.getWidth(), texture.getHeight());
		shader.setUniform2f("u_texture_0_resolution", imgSize);
		shader.setUniform1f("u_time", currentFrame);
		shader.setUniform2f("u_resolution", fbo.getWidth(), fbo.getHeight());
		
		ofDrawRectangle(area);
		shader.end();
		texture.getTexture().unbind();
		cam.end();
		/*
		cam.begin();
		ofPushMatrix();
		ofTranslate(-fbo.getWidth() / 2, -fbo.getHeight() / 2, 0);
		if (arrangeToGridToggle) { arrangeToGrid(); }
		else { arrangeRandom(); }
		ofPopMatrix();
		cam.end();
		*/
	}


	// -----------
	void drawFbo() {
		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
		if (ofGetWidth() >= ofGetHeight()) {
			float _tmpH = ofGetHeight();
			float _tmpW = fbo.getWidth() * ofGetHeight() / fbo.getHeight();
			fbo.draw(-_tmpW / 2, -_tmpH / 2, _tmpW, _tmpH);
		}
		else {
			float _tmpW = ofGetWidth();
			float _tmpH = fbo.getHeight() * ofGetWidth() / fbo.getWidth();
			fbo.draw(-_tmpW / 2, -_tmpH / 2, _tmpW, _tmpH);
		}
		ofPopMatrix();
	}


	// -----------
	void setup() {
		initBasic();
		loadShader();
		initShader();
		initFbo();
		initCam();
	};
	void update() {
		fbo.begin();
		ofClear(0);
		fboRun();
		fbo.end();
	};
	void draw() {
		drawFbo();
		currentFrame++;
	};

	void keyPressed(int key) {
		switch (key) {
		case 's':
			gk.saveFBOtoImage(&fbo);
			break;
		}
	};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void mouseEntered(int x, int y) {};
	void mouseExited(int x, int y) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};
		
};
