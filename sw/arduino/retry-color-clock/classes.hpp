//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------

#ifndef COLORCLASSES
#define COLORCLASSES

#include <algorithm>
#include <cmath>

class HsvColor;

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

  HsvColor to_hsv();

  
 
}; 


//------------------------------------------------------------------------------
// object that holds an HSV color
// assumptions:  0 <= hue < 360
//               0 <= sat < 100
//               0 <= val < 100
//------------------------------------------------------------------------------
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


//--------------------------------------------------------------
// COLOR TYPE CONVERSIONS
//
// The following section of code includes functions that
// convert color objects to different types of color objects,
// e.g. RgbColor to HsvColor and vice versa
//--------------------------------------------------------------
//--------------------------------------------------------------
// Convert an Rgb color object to an Hsv color object
// 
// This code was heavily inspired by a program posted
// by Geeks For Geeks "Program to Change RGB color model
// to HSV color model" found:
// https://www.geeksforgeeks.org/
//         program-change-rgb-color-model-hsv-color-model/
//
// and the algorithm posted here
// https://www.rapidtables.com/convert/color/rgb-to-hsv.html
//--------------------------------------------------------------
//HsvColor rgb_to_hsv(RgbColor some_color){
/*

  float red_norm   = some_color.r/255.0;
  float green_norm = some_color.g/255.0;
  float blue_norm  = some_color.b/255.0;
  
  // get max of normalized values
  float cmax = std::max(red_norm,
               std::max(green_norm,
                        blue_norm));
  
  // get min of normalized values
  float cmin = std::min(red_norm,
               std::min(green_norm,
                        blue_norm));
                   
  float diff = cmax - cmin;
  
  // hue calculation
  float hue = -1;

  // if r, g, and b are equal, then the color is grey
  // i.e. the hue doesn't matter
  // this if condition lets us avoid a div by 0 error
  if (diff == 0)
    hue = 0;
  else if (cmax == red_norm)
    hue = fmod((60.0 * (green_norm - blue_norm) / diff + 360) , 360);
  
  else if (cmax == green_norm)
    hue = 60.0 * (((blue_norm - red_norm)   / diff) + 2);
  
  else if (cmax == blue_norm)
    hue = 60.0 * (((red_norm - green_norm)  / diff) + 4);
 
  hue = fmod((hue + 360), 360);
 
  // sat calculation
  float sat = -1;
  
  if (cmax == 0) sat = 0;
  else           sat = (diff / cmax) * 100;
    
  // value computations
  float value = cmax * 100;

  return HsvColor(hue, sat, value);
*/
//  return HsvColor();
   
//}

//--------------------------------------------------------------
// convert an Hsv color object to an Rgb color object
// 
// This code is implementing the algorithm posted here:
// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
//--------------------------------------------------------------
//RgbColor hsv_to_rgb(HsvColor some_hsvcolor){
  
/*
  float hue = some_hsvcolor.h;
  float sat = some_hsvcolor.s / 100;
  float val = some_hsvcolor.v / 100;
  
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
//  return RgbColor();
//}
#endif
