#version 120

uniform vec4 position;
varying vec4 vPos;

void main(){
	vPos = position;
	gl_Position = position;
}
