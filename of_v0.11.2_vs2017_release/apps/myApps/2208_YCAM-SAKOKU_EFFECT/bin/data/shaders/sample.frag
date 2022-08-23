#version 150
precision mediump float;

uniform vec2 u_resolution;
uniform float u_time;

uniform sampler2DRect u_texture_original;
uniform vec2 u_texture_original_resolution;
uniform sampler2DRect u_texture_lcd;
uniform vec2 u_texture_lcd_resolution;

uniform float slider_darkPart;
uniform float slider_coloredPart_final;
uniform float slider_mosaicUnitSize;
uniform float slider_rgbUnitSize;

in vec2 v_texcoord;
out vec4 fragColor;



void main(){
  vec2 uv = v_texcoord * u_texture_original_resolution;
  vec3 col = vec3(1.);

  vec2 pixelizedUv = floor(uv) + vec2(0.5);
  // vec4 pixelColor = texture2DRect(u_texture_original,pixelizedUv);
  // col = pixelColor.rgb;

  vec2 mosaicUnitSize = vec2(slider_mosaicUnitSize);
  vec2 mosaicUv = mosaicUnitSize * floor(uv/mosaicUnitSize);
  vec4 mosaicColor = texture2DRect(u_texture_original,mosaicUv);
  col = mosaicColor.rgb;

  vec2 uv_lcd = v_texcoord * u_texture_lcd_resolution;
  vec2 pixelizedUv_lcd = floor(uv_lcd) + vec2(0.5);
  vec4 pixelColor_lcd = texture2DRect(u_texture_lcd,mod(uv,vec2(slider_rgbUnitSize))/vec2(slider_rgbUnitSize)*u_texture_lcd_resolution);
  
  if(pixelColor_lcd.r > 0.)pixelColor_lcd.r += 0.;
  else pixelColor_lcd.r += slider_darkPart;
  if(pixelColor_lcd.g > 0.)pixelColor_lcd.g += 0.;
  else pixelColor_lcd.g += slider_darkPart;
  if(pixelColor_lcd.b > 0.)pixelColor_lcd.b += 0.;
  else pixelColor_lcd.b += slider_darkPart;
  
  col *= pixelColor_lcd.rgb;
  
  if(col.r > 0.)col.r += slider_coloredPart_final;
  else col.r += 0.0;
  if(col.g > 0.)col.g +=slider_coloredPart_final;
  else col.g += 0.0;
  if(col.b > 0.)col.b += slider_coloredPart_final;
  else col.b += 0.0;

  // vec4 interpolatedColor = texture2DRect(u_texture_original,uv);
  // vec3 col = interpolatedColor.rgb;
  
  fragColor = vec4(col,1.);
}