precision mediump float;

//#version 300 es for webgl2

/*
attribute vec4 a_position;
attribute vec4 a_normal;
attribute vec4 a_texCoord;
attribute vec4 a_color;

uniform vec2 u_resolution;  
uniform vec2 u_mouse;       
uniform float u_ime;  
uniform vec3 u_camera;
uniform vec2[10] u_trails[10];     
*/

uniform sampler2D _MainTex;


void main(void){
    gl_FragColor = vec4(vec3(1.0,0.,1.), 1.0);
}


struct Attributes
{
    vec4 positionOS;
    vec2 uv;
};

struct Varyings
{
    vec4 pos;
    vec2 uv;
};


// 2次元ベクトルをシードとして0~1のランダム値を返す
float rand(vec2 co)
{
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43756.5453);
}


// 画面が出っ張っているようにゆがませる
vec2 distort(vec2 uv, float rate)
{
    uv -= 0.5;
    uv /= 1. - length(uv) * rate;
    uv += 0.5;
    return uv;
}

// 3x3のガウシアンフィルタをかける
vec4 gaussian_sample(vec2 uv, vec2 dx, vec2 dy)
{
    vec4 col = vec4(0.);
    //col = texture2D(_MainTex, uv);
    col += texture2D(_MainTex, uv - dx - dy) * 1./16.;
    col += texture2D(_MainTex, uv - dx) * 2./16.;
    col += texture2D(_MainTex, uv - dx + dy) * 1./16.;
    col += texture2D(_MainTex, uv - dy) * 2./16.;
    col += texture2D(_MainTex, uv) * 4./16.;
    col += texture2D(_MainTex, uv + dy) * 2./16.;
    col += texture2D(_MainTex, uv + dx - dy) * 1./16.;
    col += texture2D(_MainTex, uv + dx) * 2./16.;
    col += texture2D(_MainTex, uv + dx + dy) * 1./16.;
    return col;
}

// easing
// 参考: https://easings.net/#easeInOutCubic
float ease_in_out_cubic(const float x)
{
    return x < 0.5
        ? 4. * x * x * x
        : 1. - pow(-2. * x + 2., 3.) / 2.; 
}

// CRTの1画素の上下端が暗くなる現象を再現する
float crt_ease(const float x, const float base, const float offset)
{
    float tmp =  mod(x + offset, 1.);
    float xx = 1. - abs(tmp * 2. - 1.);
    float ease = ease_in_out_cubic(xx);
    return ease * base + base * 0.8;
}


vec4 frag(Varyings IN)
{
    vec2 uv = IN.uv;

    // uvを画面が出っ張ているようにゆがませる
    uv = distort(uv, 0.2);

    // uvが範囲内出なければ黒く塗りつぶす
    if(uv.x < 0. || 1. < uv.x || uv.y < 0. || 1. < uv.y )
    {
        return vec4(0., 0., 0., 1.);
    }

    // 現在のピクセルの色がRGBのどれか
    // x軸だけを見ることで、
    // 1. 縦方向に同じ色の画素が並ぶ
    // を達成する
    const float floor_x = mod(IN.uv.x * _ScreenParams.x / 3., 1.);
    const float isR = floor_x <= 0.3;
    const float isG = 0.3 < floor_x && floor_x <= 0.6;
    const float isB = 0.6 < floor_x;

    // 隣のピクセルまでのUV座標での差を計算しておく
    const vec2 dx = vec2(1. / _ScreenParams.x, 0.);
    const vec2 dy = vec2(0., 1. / _ScreenParams.y);

    // RGBごとにUVをずらすことで、
    // 3. 画素の並びは色ごとに異なるオフセットがある
    // を達成する
    uv += isR * -1. * dy;
    uv += isG * 0. * dy;
    uv += isB * 1. * dy;

    // ガウシアンフィルタによって、境界をぼかす
    // 特に、黒背景にドット絵だけが浮かんでいるような場合に
    // 背景とオブジェクトがハッキリ分かれてしまうことを防いでいる
    half4 col = gaussian_sample(uv, dx, dy);

    // 縦方向をNピクセルごとに分割して端を暗くする処理を加えることで、
    // 2. 上下の画素の中間には暗くなる領域が存在する
    // 4. 暗い部分では画素の大きさが小さくなる
    // を同時に達成する
    const float floor_y = fmod(uv.y * _ScreenParams.y / 6., 1.);
    const float ease_r = crt_ease(floor_y, col.r, rand(uv)* 0.1);
    const float ease_g = crt_ease(floor_y, col.g, rand(uv)* 0.1);
    const float ease_b = crt_ease(floor_y, col.b, rand(uv)* 0.1);

    // 現在のピクセルによってRGBのうち一つの色だけを表示する
    float r = isR * ease_r;
    float g = isG * ease_g;
    float b = isB * ease_b;

    gl_FragColor = vec4(r, g, b, 1.);
}