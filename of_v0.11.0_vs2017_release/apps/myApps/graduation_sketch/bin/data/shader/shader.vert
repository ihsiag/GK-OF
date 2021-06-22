#version 120
precision mediump float;

attribute vec4 position;
attribute vec4 normal;

uniform mat4 modelViewProjectionMatrix;
uniform float scannerPosY;
uniform float scannerWidth;
uniform float colWhenBright;
uniform float colWhenDark;

varying vec4 vPos;
varying vec4 vNormal;
varying float tmpCol;



void main(void){
	vPos = position;
	vNormal = normal;
	if(position.y<scannerPosY && scannerPosY - scannerWidth<position.y){
		tmpCol = colWhenBright;
	}else{
		tmpCol  = colWhenDark;
	}
	gl_Position = modelViewProjectionMatrix * position;
}
