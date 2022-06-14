#include "classes.hpp"

//-----------------------------------------------------------------------------
// COLOR TYPE CONVERSIONS
//-----------------------------------------------------------------------------
// This section includes functions that convert color objects to different
// types of color objects, e.g. RgbColor to HsvColor and vice versa
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Convert an Rgb color object to an Hsv color object
// 
// This code was heavily inspired by a program posted by Geeks For Geeks
// "Program to Change RGB color model to HSV color model" found:
// https://www.geeksforgeeks.org/
//  program-change-rgb-color-model-hsv-color-model/
//
// and the algorithm posted here
// https://www.rapidtables.com/convert/color/rgb-to-hsv.html
//-----------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
// This function returns a new HsvColor object that falls
// between two HsvColors based on a fraction that represents
// the percentage distance from one color to another.
//
// Assumption:
// color is in correct range and fraction is between 0 and 1
//------------------------------------------------------------------------------
HsvColor HsvColor::interpolate_bet_hsvcolors(HsvColor color1, 
                                   HsvColor color2, 
                                   float    fraction){

  // correct in case delta is negative
  float delta = color2.h - color1.h + 360.0;

  delta = fmod(delta, 360.0);
  float new_hue = (fraction * delta) + color1.h;
  
  delta = color2.s - color1.s;
  float new_sat = (fraction * delta) + color1.s;
  
  delta = color2.v - color1.v;
  float new_val  = (fraction * delta) + color1.v; 
  
  return HsvColor(new_hue, new_sat, new_val);                          
}

