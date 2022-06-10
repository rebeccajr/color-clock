//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains the definitions of time constants and implementation of
// color logic functions.
//------------------------------------------------------------------------------

#include "color-logic.hpp"

//int   CYCLE_PARTITIONS    = 6;
float CYCLE_TIME_IN_HOURS =   12.0/3600; //<---- change this
float HOURS_BET_COLORS    = CYCLE_TIME_IN_HOURS / CYCLE_PARTITIONS;

// max and min rgb values
int MAX_VAL       = 60;
int MIN_VAL       = 0;
int MAX_COLOR_VAL = 0xAA;
int MIN_COLOR_VAL = 0x11;

// RGB constants
RgbColor ABS_RGB_RED = RgbColor(0xFF0000);
RgbColor ABS_RGB_YEL = RgbColor(0xFFFF00);
RgbColor ABS_RGB_GRN = RgbColor(0x00FF00);
RgbColor ABS_RGB_CYA = RgbColor(0x00FFFF);
RgbColor ABS_RGB_BLU = RgbColor(0xFF00FF);
RgbColor ABS_RGB_MAG = RgbColor(0xFF00FF);

RgbColor RGB_RED = RgbColor(MAX_COLOR_VAL, MIN_COLOR_VAL, MIN_COLOR_VAL);
RgbColor RGB_YEL = RgbColor(MAX_COLOR_VAL, MAX_COLOR_VAL, MIN_COLOR_VAL);
RgbColor RGB_GRN = RgbColor(MIN_COLOR_VAL, MAX_COLOR_VAL, MIN_COLOR_VAL);
RgbColor RGB_CYA = RgbColor(MIN_COLOR_VAL, MAX_COLOR_VAL, MAX_COLOR_VAL);
RgbColor RGB_BLU = RgbColor(MIN_COLOR_VAL, MIN_COLOR_VAL, MAX_COLOR_VAL);
RgbColor RGB_MAG = RgbColor(MAX_COLOR_VAL, MIN_COLOR_VAL, MAX_COLOR_VAL);

//------------------------------------------------------------------------------
// ARRAY INITIALIZATION FUNCTIONS
//
// The following section of code includes functions to
// initialize arrays used for color and time.
//
// (This description needs improvement)
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Initializes array that stores times associated with main colors
//
// Assumption:
// times are in hours
//------------------------------------------------------------------------------
void initialize_color_times(float* color_times, float hours_between_colors) {

  for (int i = 0; i < (CYCLE_PARTITIONS + 1); i++)
    color_times[i] = i * (hours_between_colors);
}
//--------------------------------------------------------------
// Initialize array that contains main colors. Usese
//--------------------------------------------------------------
void initialize_main_colors(RgbColor* colors){
  
  for(int i = 0; i < CYCLE_PARTITIONS; i++)
    colors[i] = color_selection[i];
  
  colors[CYCLE_PARTITIONS] = colors[0];
}


//--------------------------------------------------------------
// Initialize selection of colors. Currently hard-coded, will
// read from config file or user input eventually
//--------------------------------------------------------------
void initialize_color_selection(RgbColor* colors){  
  colors[0] = RGB_RED;
  colors[1] = RGB_YEL;
  colors[2] = RGB_GRN;
  colors[3] = RGB_CYA;
  colors[4] = RGB_BLU;
  colors[5] = RGB_MAG;
}


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
HsvColor rgb_to_hsv(RgbColor some_color){

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
   
}

//--------------------------------------------------------------
// convert an Hsv color object to an Rgb color object
// 
// This code is implementing the algorithm posted here:
// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
//--------------------------------------------------------------
RgbColor hsv_to_rgb(HsvColor some_hsvcolor){
  
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
}
