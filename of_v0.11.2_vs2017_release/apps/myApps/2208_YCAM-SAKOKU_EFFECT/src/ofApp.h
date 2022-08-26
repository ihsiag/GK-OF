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
	ofShader shader;
	vector<ofImage> textures;
	vector<ofImage> textures_display;
	ofImage texture;
	ofImage texture_lcd;

	float textureAspectRatio;
	glm::vec2 exportSize;

	ofxGuiGroup gui;
	ofxToggle exportSizeSetToAR;
	ofxFloatSlider displayScale;

	ofxFloatSlider slider_darkPart;
	ofxFloatSlider slider_coloredPart_final;
	ofxFloatSlider slider_mosaicUnitSize;
	ofxFloatSlider slider_rgbUnitSize;


	


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
	void loadImages() {

	}
	void initGui() {
		gk.setGUI(gui, 0);
		gui.add(displayScale.setup("displayScale", 0.08, 0.001, 1.00));

		gui.add(slider_darkPart.setup("slider_darkPart", 0.0, 0.0, 1.0));
		gui.add(slider_coloredPart_final.setup("slider_coloredPart_final", 0.0, 0.0, 1.0));
		gui.add(slider_mosaicUnitSize.setup("slider_mosaicUnitSize", 1.0, 0.0001, 20.0));
		gui.add(slider_rgbUnitSize.setup("slider_rgbUnitSize", 3.0, 1.0, 20.0));
	}
	void initValue() {
		texture.loadImage("./shaders/tex/sample.png");
		textureAspectRatio = texture.getWidth() / texture.getHeight();
		texture_lcd.loadImage("./shaders/tex/lcd.png");

		exportSize = { 14173,9449 }; // 14173,9449 or 2000,1333
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
		gk.setCam(&cam);
		cam.setPosition(0, 0, 500);
		cam.lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		cam.enableOrtho();
		cam.disableMouseInput();
	}
	

	// -----------
	void guiListener() {
		//displayScale
		// 
		//sliders for glsl
	}
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
		
		shader.setUniformTexture("u_texture_original", texture.getTexture(), 0);
		shader.setUniform2f("u_texture_original_resolution", texture.getWidth(), texture.getHeight());

		shader.setUniformTexture("u_texture_lcd", texture_lcd.getTexture(), 1);
		shader.setUniform2f("u_texture_lcd_resolution", texture_lcd.getWidth(), texture_lcd.getHeight());
		//shader.setUniform2f("u_texture_lcd_resolution", 10,10);

		shader.setUniform1f("slider_darkPart", slider_darkPart);
		shader.setUniform1f("slider_coloredPart_final", slider_coloredPart_final);
		shader.setUniform1f("slider_mosaicUnitSize", slider_mosaicUnitSize);
		shader.setUniform1f("slider_rgbUnitSize", slider_rgbUnitSize);
		shader.setUniform1f("slider_rgbUnitSize", slider_rgbUnitSize);

	}

	void fboRun() {
		ofPlanePrimitive plane = ofPlanePrimitive(exportSize.x, exportSize.y, 10, 10);
		
		cam.begin();
		shader.begin();

		updateShaderBasics(&shader,&cam);
		updateShader();
				
		plane.drawWireframe();
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
		float _tmpH = fbo.getHeight()*displayScale;
		float _tmpW = fbo.getWidth()*displayScale;
		fbo.draw(-_tmpW / 2, -_tmpH / 2, _tmpW, _tmpH);
		ofPopMatrix();
	}


	// -----------
	void setup() {
		initGui();
		initValue();
		loadShader();
		initBasic();
		initFbo();
		initCam();
	};
	void update() {
		guiListener();
		
		fbo.begin();
		fboClear();
		fboRun();
		fbo.end();
	};
	void draw() {
		drawFbo();
		gui.draw();
		currentFrame++;
	};

	void keyPressed(int key) {
		switch (key) {
		case 's':
			gk.saveFBOtoImage(&fbo);
			break;
		case 'f':
			ofToggleFullscreen();
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
	void windowResized(int w, int h) {
		gk.resizeGUI(gui, 0);
	};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};
		
};
