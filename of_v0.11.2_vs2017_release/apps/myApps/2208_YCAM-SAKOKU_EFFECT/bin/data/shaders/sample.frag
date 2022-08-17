#version 120
precision mediump float;

uniform sampler2D u_texture_0;
varying vec2 v_texCoord;
varying vec2 vUv;
// uniform float u_time;


void main(){
  // vec3 col = texture(u_texture_0,v_texCoord).rgb;
  vec3 col = texture(u_texture_0,vUv).rgb;
  gl_FragColor = vec4(col,1.) +vec4(0.5,0.0,0.0,0.0);
}