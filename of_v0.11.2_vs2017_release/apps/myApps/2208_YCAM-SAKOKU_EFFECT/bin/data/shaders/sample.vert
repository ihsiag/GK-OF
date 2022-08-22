#version 150
precision mediump float;

uniform mat4 modelViewProjectionMatrix;
in vec3 position;
in vec2 texcoord;
out vec2 v_texcoord;

void main(){
  v_texcoord = texcoord;
  gl_Position = modelViewProjectionMatrix*vec4(position,1.);
}
