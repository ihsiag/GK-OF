#version 150
precision mediump float;

uniform sampler2DRect u_texture_0;
uniform vec2 u_texture_0_resolution;
uniform vec2 u_resolution;
uniform float u_time;

in vec2 v_texcoord;
out vec4 fragColor;


void main(){
  vec2 uv = v_texcoord * u_texture_0_resolution;
  vec3 col = texture2DRect(u_texture_0,uv).rgb;
  fragColor = vec4(col,1.);
}