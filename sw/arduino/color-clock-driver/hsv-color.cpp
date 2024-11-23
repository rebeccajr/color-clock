//______________________________________________________________________________
// This file contains class implementations for color types.
//______________________________________________________________________________

//#define ARDUINO_BUILD //just here so VS code doesn't complain
#include <map>
#include <vector>

#ifdef ARDUINO_BUILD
#include <Arduino.h>
#endif

#include "hsv-color.hpp"
#include "rgb-color.hpp"

//______________________________________________________________________________
// Convert an Rgb color object to an Hsv color object
//
// This code was heavily inspired by a program posted by Geeks For Geeks
// "Program to Change RGB color model to HSV color model" found:
// https://www.geeksforgeeks.org/
//  program-change-rgb-color-model-hsv-color-model/
//
// and the algorithm posted here
// https://www.rapidtables.com/convert/color/rgb-to-hsv.html
//______________________________________________________________________________

RgbColor HsvColor::to_rgb(){

  float hue = this->h;
  float sat = this->s / 100.0;
  float val = this->v / 100.0;

  float c = val * sat;
  float fm = fmod(hue /60.0, 2.0);
  float ab = fabs(fm - 1.0);
  float x = c * (1.0 - ab);

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
}




//______________________________________________________________________________
// COLOR TYPE CONVERSIONS
//______________________________________________________________________________
// This section includes functions that convert color objects to different
// types of color objects, e.g. RgbColor to HsvColor and vice versa
//______________________________________________________________________________




//--------------------------------------------------------------
// Convert an Hsv color object to an Rgb color object.
//
// This code is implementing the algorithm posted here:
// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
//--------------------------------------------------------------
///______________________________________________________________________________
// This function returns a new HsvColor object that falls
// between two HsvColors based on a fraction that represents
// the percentage distance from one color to another.
//
// Assumption:
// color is in correct range and fraction is between 0 and 1
//______________________________________________________________________________
HsvColor HsvColor::interpolate_bet_hsvcolors(HsvColor color1,
   HsvColor color2,
   float    fraction
)
{
  // This variable determines which direction in the circle to interpolate over
  bool clockwise = false;

  float delta = fabs(color2.h - color1.h);

  // Determine direction of interpolation over HSV circle
  clockwise = color1.h > color2.h;
  if (delta > 180)
  {
    clockwise = !clockwise;
    delta = 360 - delta;
  }

  delta = delta * fraction;

  float new_hue = 0;

  if (clockwise)
    new_hue = color1.h - delta;
  else
    new_hue = color1.h + delta;

  new_hue = fmod(360.0 + new_hue, 360.0);

  //____________________________________________________________________________
  // Reusing delta variable
  //____________________________________________________________________________
  delta = fabs(color2.s - color1.s);
  delta = fraction * delta;

  if (color2.s < color1.s)
    delta = -delta;

  float new_sat = delta + color1.s;


  delta = fabs(color2.v - color1.v);
  delta = fraction * delta;

  if (color2.v < color1.v)
    delta = -delta;

  float new_val = delta + color1.v;

  //____________________________________________________________________________
  // TODO incorporate max sat and val
  //____________________________________________________________________________
  // Max out saturation and value for now
  return HsvColor(new_hue, new_sat, new_val);
}
