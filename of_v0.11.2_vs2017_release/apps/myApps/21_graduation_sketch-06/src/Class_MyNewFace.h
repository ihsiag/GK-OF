#pragma once

#include "ofMain.h"
#include "ofxGKUtils.h"
#include "ofEvents.h"

class Class_MyNewFace {
	public:
		int ID;

		Class_MyNewFace() {}
		~Class_MyNewFace() {}
		void setup() {		
		};
				
		//-----------THIS-TIME-UTILS-----------//	
		void drawMyNewFace() {
		}
		
		//-----------EVENT-----------//
		void keyPressed(const int& key) {
			switch (key) {
			//case ' ':
			//	break;
			}
		};
	
private:
		ofxGKUtils gk;
		stringstream* ssLog;		
};