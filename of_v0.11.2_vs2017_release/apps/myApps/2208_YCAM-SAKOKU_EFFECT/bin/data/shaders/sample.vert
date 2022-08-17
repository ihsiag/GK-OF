#version 120

precision mediump float;
attribute vec4 position;
attribute vec4 normal;
attribute vec2 uv;

varying vec2 v_texCoord;
varying vec2 vUv;

void main(void){
  vUv = uv;
  v_texCoord = gl_MultiTexCoord0.xy;
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
  // gl_Position = modelViewProjectionMatrix * position;
}
