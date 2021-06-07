#version 120


uniform float time;
uniform vec2 resolution;

varying vec4 vPos;
varying vec4 vNormal;

void main(){
	gl_FragColor = vec4(vec3(0.5),1.0);
}