#version 120
precision mediump float;


attribute vec4 position;
uniform mat modelViewProjectionMatrix;

void main(void){
	gl_Position = modelViewProjectionMatrix * position;
}
