#include "logic.hpp"

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
