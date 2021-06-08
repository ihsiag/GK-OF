#pragma once

#include "ofMain.h"
#include "ofApp.h"

class myController {
public:
    ofVec2f controllerPos;
    ofVec2f controllerSize;
    ofVec2f sliderPos;
    float sliderR;
    float widthRange[2];
    float heightRange[2];
    ofColor baseColor;
    ofColor changedColor;
    bool isBeingSlided;
    bool mouseIsPressed;
    bool mouseIsDragged;
    float mouseX;
    float mouseY;
    
    myController(){}

    void init(float _x, float _y) {
        isBeingSlided = false;
        controllerPos = ofVec2f(int(_x), int(_y));
        controllerSize = ofVec2f(ofGetWidth() / 4 * 0.8, 3);
        sliderPos = ofVec2f(int(_x), int(_y));
        sliderR = 10;
        widthRange[0] = controllerPos.x;
        widthRange[1] = controllerPos.x + controllerSize.x;
        heightRange[0] = controllerPos.y;
        heightRange[1] = controllerPos.y + controllerSize.y;
        heightRange[0] -= 20;
        heightRange[1] += 20;
        baseColor.set(150, 150, 150);
        changedColor.set(255, 0, 0);
        mouseIsPressed = false;
        isBeingSlided = false;
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
        float value = ofMap(sliderPos.x - controllerPos.x, 0, controllerSize.x, 0, 1);
        return value;
    }


    void event() {
        if (mouseIsDragged == true) {
            if (mouseY > heightRange[0] && mouseY < heightRange[1]) {
                ofSetColor(changedColor);
                if (mouseX > widthRange[0] && mouseX < widthRange[1]) {
                    sliderPos.x = mouseX;
                }
                else if (mouseX < widthRange[0]) {
                    sliderPos.x = widthRange[0];
                }
                else if (mouseX > widthRange[1]) {
                    sliderPos.x = widthRange[1];
                }
            }
        }
        else {
            ofFill();
            ofSetColor(baseColor);
        }
    }
};
