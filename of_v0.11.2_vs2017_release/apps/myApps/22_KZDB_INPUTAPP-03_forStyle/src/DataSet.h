#pragma once
#ifndef DATA_SET_H  
#define DATA_SET_H

#include "ofMain.h"
#include "ofxCsv.h"

struct DataSet {
	DataSet() {
		prjId = "not selected";
		imgId = "not selected";
		posX = "not selected";
		posY = "not selected";
	}
	string prjId;
	string imgId;
	string posX;
	string posY;
};
#endif
