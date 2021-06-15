#version 120
precision mediump float;

attribute vec4 position;
attribute vec4 normal;

uniform mat4 modelViewProjectionMatrix;
uniform float scannerPosY;
uniform float scannerWidth;

varying vec4 vPos;
varying vec4 vNormal;
varying float tmpCol;



void main(void){
	vPos = position;
	vNormal = normal;
	if(position.y<scannerPosY && scannerPosY - scannerWidth<position.y){
		tmpCol = 1.0;
	}else{
		tmpCol  = 0.5;
	}
	gl_Position = modelViewProjectionMatrix * position;
}
