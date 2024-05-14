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

#include <algorithm>
#include <cmath>
#include <map>

class HsvColor;

class RgbColor {

public:

  enum class PriColor
  { RED
    , GRN
    , BLU
  };

  static std::map <PriColor, short> create_rgb_pin_map(short, short, short);

  int r;      // red
  int g;      // green
  int b;      // blue
  
  //------------------------------------
  // constructors
  //------------------------------------
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

  HsvColor to_hsv();

  void write_rgb_to_out(int, int, int, bool = false);
}; 


//______________________________________________________________________________
// Object that holds an HSV color
// Assumptions:  0 <= hue < 360
//               0 <= sat < 100
//               0 <= val < 100
//______________________________________________________________________________
class HsvColor {

public:

  //------------------------------------------------------------
  // static funtions
  //------------------------------------------------------------
  static HsvColor interpolate_bet_hsvcolors(
                    HsvColor color1, 
                    HsvColor color2, 
                    float    fraction);

  //------------------------------------------------------------
  // class members
  //------------------------------------------------------------
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
