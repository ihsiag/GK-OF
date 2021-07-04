#version 120
precision mediump float;

uniform float time;
uniform vec2 resolution;
uniform float alpha;

uniform float scannerPosY;
varying vec4 vPos;
varying vec4 vNormal;
varying float tmpCol;

void main(void){

		gl_FragColor = vec4(vec3(tmpCol),alpha);

}