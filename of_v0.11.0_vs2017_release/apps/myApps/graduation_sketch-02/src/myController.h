#pragma once

#include "ofMain.h"
#include "ofApp.h"

class myController {
public:
    ofTrueTypeFont font;
    float fontSize;

    std::string controllerName;
    float controllerRangeMin, controllerRangeMax;
    ofVec2f controllerPos,sliderPos;
    ofVec2f controllerSize;
    float sliderR;

    float tolerance;
    float toleranceRangeWidth[2], toleranceRangeHeight[2];
    ofColor fillColor;
    ofColor baseColor;
    ofColor changedColor;

    ofVec2f margin;
    float dist;
    
    bool mouseIsDragged;
    float mouseX, mouseY;

    
    myController(){}

    void init(int _index, std::string _name, float _min, float _max, ofVec2f _areaNW, ofVec2f _areaSE) {
        //font
        fontSize = 10;
        ofTrueTypeFont::setGlobalDpi(72);
        font.load("font/SourceCodePro-Light.ttf", fontSize);
        font.setLineHeight(fontSize);
        font.setLetterSpacing(1.0);

        //
        margin = (_areaSE-_areaNW)/10;
        dist = fontSize * 2;

        controllerName = _name;
        controllerRangeMin = _min;
        controllerRangeMax = _max;      
        controllerPos = _areaNW+margin+ofVec2f(0,dist*_index);      
        controllerSize = ofVec2f((_areaSE.x - _areaNW.x) / 10, 1);
        
        sliderPos = controllerPos;
        sliderR = 10;
        tolerance = sliderR;
      
        toleranceRangeWidth[0] = controllerPos.x;
        toleranceRangeWidth[1] = controllerPos.x + controllerSize.x;
        toleranceRangeHeight[0] = controllerPos.y;
        toleranceRangeHeight[1] = controllerPos.y + controllerSize.y;
        toleranceRangeHeight[0] -= tolerance;
        toleranceRangeHeight[1] += tolerance;        
        mouseIsDragged = false;
        mouseX = 0;
        mouseY = 0;

        baseColor.set(150, 150, 150);
        changedColor.set(255, 0, 0);
    }

    void update() {
        //decidePoss();
        mouseEvent();
    }

    void show() {
        ofFill();
        ofSetColor(fillColor);
        ofDrawRectangle(controllerPos.x, controllerPos.y-controllerSize.y/2, controllerSize.x, controllerSize.y);
        ofDrawEllipse(sliderPos.x, sliderPos.y, sliderR, sliderR);
        string posToPrint = controllerName + ":" + ofToString(bridgeValue());
        ofSetColor(255);
        ofRectangle bb = font.getStringBoundingBox(posToPrint, 0, 0);
        ofDrawRectangle(bb.x,bb.y,bb.width,bb.height);
        ofSetColor(255);
        font.drawString(posToPrint, controllerPos.x + controllerSize.x + 20, controllerPos.y);
    }

    float bridgeValue() {
        float value = ofMap(sliderPos.x - controllerPos.x, 0, controllerSize.x, controllerRangeMin, controllerRangeMax);
        return value;
    }


    void mouseEvent() {
        if (mouseIsDragged == true) {
            if (mouseY > toleranceRangeHeight[0] && mouseY < toleranceRangeHeight[1]) {
                if (mouseX > toleranceRangeWidth[0] && mouseX < toleranceRangeWidth[1]) {
                    fillColor = changedColor;
                    sliderPos.x = mouseX;
                }
                else if (mouseX < toleranceRangeWidth[0]) {
                    sliderPos.x = toleranceRangeWidth[0];
                }
                else if (mouseX > toleranceRangeWidth[1]) {
                    sliderPos.x = toleranceRangeWidth[1];
                }
            }
            else {
                fillColor = baseColor;
            }
        }
        else {
            fillColor = baseColor;
        }
    }

    void windowResizeEvent(int _index,ofVec2f _areaNW, ofVec2f _areaSE) {
    }
};
