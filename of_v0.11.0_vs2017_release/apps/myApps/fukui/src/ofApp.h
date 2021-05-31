#pragma once

#include "ofMain.h"
//#include "ofWalker.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//my defs
		void initSetting();
		void initParam();
		void makeGrid(int _gridSize);
		void makeDimension();
		void func01(float _x, float _y, float _dThickness);
		void func02(float _x, float _y, float _dThickness);
		void func03(ofPoint _pos);
		void func04();
		void func05(ofPoint _pos);


		//my class
		//ofWalker walker;


		//global param
		int currentFrame;
		float X, Y;
		float deltaThickness;

		static const int num_pt = 4;
		ofPoint pt[num_pt];

		int tmpFrame;
};
