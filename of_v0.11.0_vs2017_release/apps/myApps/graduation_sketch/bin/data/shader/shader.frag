#version 120
precision mediump float;

uniform float time;
uniform vec2 resolution;

varying vec4 vPos;
varying vec4 vNormal;

void main(void){
	gl_FragColor = vec4(vec3(1.0),1.0);
}