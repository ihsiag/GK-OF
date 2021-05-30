#version 410

in vec4 color;
layout (location=0) out vec4 frag_color;

uniform vec2 hatching;

void main() {
    vec2 st = gl_FragCoord.xy;

    if (hatching.x > 0 && (mod(floor(st.x), hatching.x) == 0)) discard;
    if (hatching.y > 0 && (mod(floor(st.y), hatching.y) == 0)) discard;
    
    frag_color = color;
}
