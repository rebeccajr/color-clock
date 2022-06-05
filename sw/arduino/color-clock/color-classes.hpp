//--------------------------------------------------------------
// DESCRIPTION
// This file contains classes that represent RGB and HSV
// color objects.
//
// RgbColor contains three member variables:
// r (red)    range: [0, 255] or [0x00, 0xFF]
// g (green)  range: [0, 255] or [0x00, 0xFF]
// b (blue)   range: [0, 255] or [0x00, 0xFF]
//
// RGB colors are used to define the main colors that the clock will cycle
// through.
//
// HsvColor contains three member variables:
// h (hue)        range: [0, 360]
// s (saturation) range: [0, 100]
// v (value)      range: [0, 100]
//--------------------------------------------------------------

#define COLORCLASSES
#ifndef COLORCLASSES

class Color {

public:
  struct Rgb {
    int r;      // red
    int g;      // green
    int b;      // blue
  } 

  struct Hsv {
    float h;    // hue
    float s;    // saturation
    float v;    // value
  }

  Rgb rgb;
  Hsv hsv;

  //------------------------------------
  // CONSTRUCTORS
  //------------------------------------
  Color(){}

  hsv_to_rgb(struct Hsv an_hsv_color);

  Color(struct Rgb an_rgb_color){
    this->hsv = {}; 
  }

  Color(struct Hsv an_hsv_color){
    this->rgb = {}; 
  }
};

//--------------------------------------------------------------
// convert an Hsv color object to an Rgb color object
// 
// This code is implementing the algorithm posted here:
// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
//--------------------------------------------------------------
Color::hsv_to_rgb(){
  float hue = this->hsv.h;
  float sat = this->hsv.s / 100;
  float val = this->hsv.v / 100;
  
  /*
  float c = val * sat;
  float x = c * (1 - abs(fmod((hue / 60), 2) - 1));
  float m = val - c;
  
  float r_prime = 0;
  float g_prime = 0;
  float b_prime = 0;
  
  if (0 <= hue && hue < 60) {
    r_prime = c;
    g_prime = x;
    b_prime = 0;
  }
  else if ( 60 <= hue && hue < 120) {
    r_prime = x;
    g_prime = c;
    b_prime = 0;
  }
  else if (120 <= hue && hue < 180) {
    r_prime = 0;
    g_prime = c;
    b_prime = x;
  }
  else if (180 <= hue && hue < 240) {
    r_prime = 0;
    g_prime = x;
    b_prime = c;
  }
  else if (240 <= hue && hue < 300) {
    r_prime = x;
    g_prime = 0;
    b_prime = c;
  }
  else if (300 <= hue && hue < 360) {
    r_prime = c;
    g_prime = 0;
    b_prime = x;
  }

  int r = round((r_prime + m) * 255);
  int g = round((g_prime + m) * 255);
  int b = round((b_prime + m) * 255);

  return RgbColor(r, g, b);
*/
}
  


class RgbColor {

public:

  int r;      // red
  int g;      // green
  int b;      // blue
  
  RgbColor(){}

  // values normalized to 255
  RgbColor(int red, int green, int blue){
  
    r = red;
    g = green;
    b = blue;
    
  }
  
  // enables user to enter RGB values using a 6 digit hex int
  RgbColor(int rgb_hex){
    
    r = (rgb_hex & 0xFF0000) >> 16;
    g = (rgb_hex & 0x00FF00) >> 8;
    b = (rgb_hex & 0x0000FF);
     
  }
  
  // converts RgbColor to string
  String to_string(){
  
    return "red: "   + String(this->r, 3) +
           "; grn: " + String(this->g, 3) + 
           "; blu: " + String(this->b, 3);
  }

};

//--------------------------------------------------------------
// object that holds an HSV color
// assumptions:  0 <= hue < 360
//               0 <= sat < 100
//               0 <= val < 100
//--------------------------------------------------------------
class HsvColor {

public:
  float h;
  float s; 
  float v;

  //HsvColor(){}

  HsvColor(float hue, float sat, float value){
  
    h = hue;
    s = sat;
    v = value;
 
  }
  
  String to_string(){

    return "hue: "   + String(this->h, 3) +
           "; sat: " + String(this->s, 3) + 
           "; val: " + String(this->v, 3);
  }

};

#endif
