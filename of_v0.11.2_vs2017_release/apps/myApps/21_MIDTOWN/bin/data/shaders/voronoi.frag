//#version 120
precision mediump float;


//#version 300 es for webgl2


//attribute vec4 a_position;
//attribute vec4 a_normal;
//attribute vec4 a_texCoord;
//attribute vec4 a_color;
//sampler2D colorPallete;
uniform vec2 u_resolution;  
//uniform vec2 u_mouse;       
uniform float u_time; 
//uniform vec3 u_camera;
//uniform float seed;
//uniform vec2[10] u_trails[10];     



vec2 random2( vec2 p ) {
    return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

void main(void) {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    vec3 color = vec3(.0);

    // Scale
    st *= 5.;

    // Tile the space
    vec2 i_st = floor(st);
    vec2 f_st = fract(st);

    float m_dist = 10.;  // minimum distance
    vec2 m_point;        // minimum point

    for (int j=-1; j<=1; j++ ) {
        for (int i=-1; i<=1; i++ ) {
            vec2 neighbor = vec2(float(i),float(j));
            vec2 point = random2(i_st + neighbor);
            point = 0.5 + 0.5*sin(u_time + 6.2831*point);
            vec2 diff = neighbor + point - f_st;
            float dist = length(diff);

            if( dist < m_dist ) {
                m_dist = dist;
                m_point = point;
            }
        }
    }

    // Assign a color using the closest point position
    color += dot(m_point,vec2(.3,.6));

    // Add distance field to closest point center
    // color.g = m_dist;

    // Show isolines
    //color -= abs(sin(40.0*m_dist))*0.07;

    // Draw cell center
    //color += 1.-step(.05, m_dist);

    // Draw grid
    //color.r += step(.98, f_st.x) + step(.98, f_st.y);

    gl_FragColor = vec4(vec3(0.0),color.r);
}



