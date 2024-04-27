//______________________________________________________________________________
// This file contains class implementations for color types.
//______________________________________________________________________________

//#define ARDUINO_BUILD //just here so VS code doesn't complain
#include <map>

#include "color-classes.hpp"
#include "debug.hpp"

#ifdef ARDUINO_BUILD
#include <Arduino.h>
#endif


//______________________________________________________________________________
// COLOR TYPE CONVERSIONS
//______________________________________________________________________________
// This section includes functions that convert color objects to different
// types of color objects, e.g. RgbColor to HsvColor and vice versa
//______________________________________________________________________________

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
HsvColor RgbColor::to_hsv(){

  float red_norm   = this->r/255.0;
  float green_norm = this->g/255.0;
  float blue_norm  = this->b/255.0;

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
}


//--------------------------------------------------------------
// Convert an Hsv color object to an Rgb color object.
//
// This code is implementing the algorithm posted here:
// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
//--------------------------------------------------------------
RgbColor HsvColor::to_rgb(){

  float hue = this->h;
  float sat = this->s / 100;
  float val = this->v / 100;

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
}

//______________________________________________________________________________
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

  float delta = abs(color2.h - color1.h);

  // Determine direction of interpolation over HSV circle
  clockwise = color1.h > color2.h;
  if (delta > 180)
  {
    clockwise = !clockwise;
    delta = 360 - delta;
  }

  fraction = delta * fraction;
  
  float new_hue = 0;

  if (clockwise)
    new_hue = color1.h - fraction;
  else
    new_hue = color1.h + fraction;

  new_hue = fmod(360.0 + new_hue, 360.0);

  //____________________________________________________________________________
  // Reusing delta variable
  //____________________________________________________________________________
  delta = color2.s - color1.s;
  float new_sat = (fraction * delta) + color1.s;

  delta = color2.v - color1.v;
  float new_val  = (fraction * delta) + color1.v;

  //____________________________________________________________________________
  // TODO incorporate max sat and val
  //____________________________________________________________________________
  // Max out saturation and value for now
  //return HsvColor(new_hue, new_sat, new_val);
  return HsvColor(new_hue, 100, 100);
}


//______________________________________________________________________________
// Writes RGB values to output
// If this is a build to the Arduino, writes the ouput pins
//______________________________________________________________________________
void RgbColor::write_rgb_to_out(int red_out, int grn_out, int blu_out)
{
#ifdef ARDUINO_BUILD
  analogWrite(red_out, r);
  analogWrite(grn_out, g);
  analogWrite(blu_out, b);
#endif
}


//______________________________________________________________________________
// Create map of pin assignments to 
//______________________________________________________________________________
std::map <RgbColor::PriColor, short> RgbColor::create_rgb_pin_map(short r_pin
  , short g_pin
  , short b_pin
)
{
  std::map <RgbColor::PriColor, short> mappy;
  mappy.insert({PriColor::RED, r_pin});
  mappy.insert({PriColor::GRN, g_pin});
  mappy.insert({PriColor::BLU, b_pin});

  return mappy;
}