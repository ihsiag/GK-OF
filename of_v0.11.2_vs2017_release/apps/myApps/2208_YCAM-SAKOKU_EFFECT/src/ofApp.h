#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp {

public:
	ofxGKUtils gk;
	ofFbo fbo;
	unsigned long int currentFrame;

	ofEasyCam cam;
	ofPlanePrimitive plane;
	ofShader shader;
	ofImage texture;

	glm::vec2 textureSize;
	glm::vec2 exportSize;

	


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
	void initValue() {
		texture.loadImage("./shaders/tex/sample2.png");
		textureSize = {texture.getWidth(),texture.getHeight()};
		//exportSize = { 1000, 1000 };
		exportSize = textureSize;
	}
	void initFbo() {
		fbo.allocate(exportSize.x,exportSize.y, GL_RGBA);
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
		cam.lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		cam.enableOrtho();
		cam.disableMouseInput();
	}
	void initGeo() {
		plane = ofPlanePrimitive(textureSize.x,textureSize.y, 10, 10);
	}

	// -----------
	void fboClear() {
		ofClear(0);
		/*glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
	}

	void updateShaderBasics(ofShader* _shader,ofEasyCam* _cam) {
		glm::mat4x4 modelMatrix;
		glm::mat4x4 viewMatrix;
		viewMatrix = ofGetCurrentViewMatrix();
		glm::mat4x4 projectionMatrix;
		projectionMatrix = _cam->getProjectionMatrix();
		glm::mat4x4 mvpMatrix;
		mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;
		_shader->setUniformMatrix4f("modelViewProjectionMatrix", mvpMatrix);
	}
	void updateShader() {		
		shader.setUniform1f("u_time", currentFrame);
		shader.setUniform2f("u_resolution", fbo.getWidth(), fbo.getHeight());
		shader.setUniformTexture("u_texture_0", texture.getTexture(), 0);
		glm::vec2 imgSize = glm::vec2(texture.getWidth(), texture.getHeight());
		shader.setUniform2f("u_texture_0_resolution", imgSize);
	}
	void fboRun() {
		cam.begin();
		shader.begin();

		updateShaderBasics(&shader,&cam);
		updateShader();
				
		plane.draw();
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
		initValue();
		loadShader();
		initBasic();
		initFbo();
		initCam();
		initGeo();
	};
	void update() {
		fbo.begin();
		fboClear();
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
