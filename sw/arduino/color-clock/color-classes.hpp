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


class RgbColor {

public:

  int r;      // red
  int g;      // green
  int b;      // blue
  
  RgbColor(){}

  // values normalized to 255
  RgbColor(int red, int green, int blue){
  
    this->r = red;
    this->g = green;
    this->b = blue;
    
  }
  
  // enables user to enter RGB values using a 6 digit hex int
  RgbColor(int rgb_hex){
    this->r = (rgb_hex & 0xFF0000) >> 16;
    this->g = (rgb_hex & 0x00FF00) >> 8;
    this->b = (rgb_hex & 0x0000FF);
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

#endif
