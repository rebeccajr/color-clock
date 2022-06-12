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

#ifndef COLORCLASSES
#define COLORCLASSES

#include <algorithm>
#include <cmath>

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

  RgbColor(int rgb_hex){
    this->r = (rgb_hex & 0xFF0000) >> 16;
    this->g = (rgb_hex & 0x00FF00) >> 8;
    this->b = (rgb_hex & 0x0000FF);
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

  HsvColor(){}

  HsvColor(float hue, float sat, float value){
  
    h = hue;
    s = sat;
    v = value;
 
  }
};

#endif
