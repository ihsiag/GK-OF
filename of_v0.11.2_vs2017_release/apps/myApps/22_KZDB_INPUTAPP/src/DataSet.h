#pragma once
#ifndef DATA_SET_H  
#define DATA_SET_H

#include "ofMain.h"
#include "ofxCsv.h"

struct DataSet {
	DataSet() {}
	ofxCsv csvA;
	ofxCsv csvB;
	string companyID;
	string materialID;
	string projectID;
	string imgID;
};
#endif
