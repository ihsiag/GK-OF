#version 120
precision mediump float;

attribute vec4 position;
attribute vec4 normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

varying vec4 vPos;
varying vec4 vNormal;


void main(void){
	vPos = position;
	vNormal = normal;
	gl_Position = modelViewProjectionMatrix * position;
}
