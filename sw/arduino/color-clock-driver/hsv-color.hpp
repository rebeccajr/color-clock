//______________________________________________________________________________
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
//______________________________________________________________________________

#ifndef COLOR_CLASSES
#define COLOR_CLASSES

#define MAX_RGB_VAL 0xFF
#define MIN_RGB_VAL 0

#include <algorithm>
#include <cmath>
#include <map>

#include "rgb-color.hpp"

//______________________________________________________________________________
// Object that holds an HSV color
// Assumptions:  0 <= hue < 360
//               0 <= sat < 100
//               0 <= val < 100
//______________________________________________________________________________
class HsvColor {

public:

  static HsvColor interpolate_bet_hsvcolors(
                    HsvColor color1, 
                    HsvColor color2, 
                    float    fraction);

  float h;
  float s; 
  float v;

  HsvColor(){}

  HsvColor(float hue, float sat, float value){
    h = hue;
    s = sat;
    v = value;
  }

  RgbColor to_rgb();
};

#endif
