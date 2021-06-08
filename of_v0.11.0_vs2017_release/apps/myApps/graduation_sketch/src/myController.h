#pragma once

#include "ofMain.h"
#include "ofApp.h"

class myController {
public:
    ofVec2f controllerPos;
    ofVec2f controllerSize;
    ofVec2f sliderPos;
    float sliderR;
    float tolerance;
    float toleranceRangeWidth[2];
    float toleranceRangeHeight[2];
    ofColor baseColor;
    ofColor changedColor;
    bool mouseIsDragged;
    float mouseX, mouseY;

    
    myController(){}

    void init(float _x, float _y, std::string _name) {
        controllerPos = ofVec2f(int(_x), int(_y));
        controllerSize = ofVec2f(ofGetWidth() / 4 * 0.8, 1);
        sliderPos = ofVec2f(int(_x), int(_y));
        sliderR = 10;
        tolerance = 20;
        toleranceRangeWidth[0] = controllerPos.x;
        toleranceRangeWidth[1] = controllerPos.x + controllerSize.x;
        toleranceRangeHeight[0] = controllerPos.y;
        toleranceRangeHeight[1] = controllerPos.y + controllerSize.y;
        toleranceRangeHeight[0] -= tolerance;
        toleranceRangeHeight[1] += tolerance;
        baseColor.set(150, 150, 150);
        changedColor.set(255, 0, 0);
        mouseIsDragged = false;
        mouseX = 0;
        mouseY = 0;
    }

    void update() {
        event();
    }

    void show() {
        ofFill();
        ofDrawRectangle(controllerPos.x, controllerPos.y, controllerSize.x, controllerSize.y);
        ofDrawEllipse(sliderPos.x, sliderPos.y + controllerSize.y / 2, sliderR, sliderR);
    }

    float bridgeValue() {
        float value = ofMap(sliderPos.x - controllerPos.x, 0, controllerSize.x, 0.00, 1.00);
        return value;
    }


    void event() {
        if (mouseIsDragged == true) {
            if (mouseY > toleranceRangeHeight[0] && mouseY < toleranceRangeHeight[1]) {
                ofSetColor(changedColor);
                if (mouseX > toleranceRangeWidth[0] && mouseX < toleranceRangeWidth[1]) {
                    sliderPos.x = mouseX;
                }
                else if (mouseX < toleranceRangeWidth[0]) {
                    sliderPos.x = toleranceRangeWidth[0];
                }
                else if (mouseX > toleranceRangeWidth[1]) {
                    sliderPos.x = toleranceRangeWidth[1];
                }
            }
        }
        else {
            ofFill();
            ofSetColor(baseColor);
        }
    }
};
