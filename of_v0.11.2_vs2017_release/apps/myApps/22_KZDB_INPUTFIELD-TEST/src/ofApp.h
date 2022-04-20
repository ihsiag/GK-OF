#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxImGui.h"

#if defined (_WIN32)
#include "ofxImGui-master/IMM32IMGUI/imgui_imm32_onthespot.h"
//#include "ofxImGui-master/IMM32IMGUI/imgui_imm32_onthespot_sdl.h" /* If you are using SDL, include imgui_imm32_onthesport_sdl.h */
#endif

class ofApp : public ofBaseApp{

	public:
		
		ofxImGui::Gui gui;
		ofxTextField field;

		ImGUIIMMCommunication imguiIMMCommunication{};
		//VERIFY(imguiIMMCommunication.subclassify(window));
		


		void setup();
		void update();
		void draw();

		void HelpMarker(const char* desc);

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
		
};
