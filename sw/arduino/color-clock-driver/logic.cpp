//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains the definitions of time constants and implementation of
// color logic functions.
//------------------------------------------------------------------------------

#include "debug.hpp"
#include "logic.hpp"
#include "time-calcs.hpp"

// max and min rgb values
int MAX_VAL       = 60;
int MIN_VAL       = 0;
int MAX_COLOR_VAL = 0xAA;
int MIN_COLOR_VAL = 0x11;

// RGB constants
RgbColor RED = RgbColor(0xFF0000);
RgbColor YEL = RgbColor(0xFFFF00);
RgbColor GRN = RgbColor(0x00FF00);
RgbColor CYA = RgbColor(0x00FFFF);
RgbColor BLU = RgbColor(0xFF00FF);
RgbColor MAG = RgbColor(0xFF00FF);

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
// Initialize array that contains main colors.
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
// This function is the "main" part of the program that
// determines the RgbColor associated with the current time
// based on the program presets.
//
// Arguments:
// times  - array of times that correspond with main colors
// colors - array of main colors
//--------------------------------------------------------------
RgbColor map_time_to_color(
  float  hrs_since_cycle_restart,
  float* times, RgbColor* colors, int array_size){

  Debug::print_labeled_dec("hours since cycle restart",
    hrs_since_cycle_restart);

  // modifies the indices of the colors from the main_colors array
  // in which the current time falls between
  int index[2];
  get_indices_of_colors(index, times, hrs_since_cycle_restart);

  //print("\n\nindices of boundary colors: " + str(index[0]) + ", "
                                           //+ str(index[1]));

  // convert colors from main_colors array to hsv
  // for smoother transitions between colors
  HsvColor hsvcolor0 = colors[index[0]].to_hsv();
  HsvColor hsvcolor1 = colors[index[1]].to_hsv();

  float fraction  =
    TimeCalcs::get_time_as_fractional_offset(times[index[0]],
                                                  times[index[1]],
                                                  hrs_since_cycle_restart);

  HsvColor crnt_hsvcolor_time
    = HsvColor::interpolate_bet_hsvcolors(hsvcolor0, hsvcolor1, fraction);

  // convert hsv to rgb in order to display properly
  RgbColor crnt_rgbcolor_time = crnt_hsvcolor_time.to_rgb();

  return crnt_rgbcolor_time;
}
