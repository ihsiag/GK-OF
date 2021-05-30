#version 410

layout (location=0) in vec3 vertex_pos;
layout (location=1) in vec4 vertex_color;
out vec4 color;

uniform mat4 modelViewProjectionMatrix;

void main() {
    gl_Position = modelViewProjectionMatrix * vec4(vertex_pos, 1.0);
    color = vertex_color;
}
