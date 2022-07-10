//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains the logic that maps the time to color for the ColorClock.
// 
// The ColorClock is a colored light that maps the current time
// to a color. The clock will cycle through a series of colors over a period
// of time. A viewer can tell the approximate time from the color 
// of the light.
//
// HsvColor is used for calculations because this type of color object
// provides a smoother transition.
//------------------------------------------------------------------------------

#ifndef COLOR_LOGIC_HPP
#define COLOR_LOGIC_HPP

//------------------------------------------------------------------------------
// INCLUDE LIBRARIES
//------------------------------------------------------------------------------
#include "classes.hpp"

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

// configuration values
#define CYCLE_PARTITIONS 6   

extern float CYCLE_TIME_IN_HOURS;
extern float HOURS_BET_COLORS;

// arrays used for initialization of the clock
extern float    main_color_times[CYCLE_PARTITIONS];
extern RgbColor main_colors[CYCLE_PARTITIONS + 1];
extern RgbColor color_selection[CYCLE_PARTITIONS];

// max and min rgb values
extern int MAX_VAL; 
extern int MIN_VAL; 
extern int MAX_COLOR_VAL; 
extern int MIN_COLOR_VAL; 

// RGB constants
extern RgbColor ABS_RGB_RED;
extern RgbColor ABS_RGB_YEL;
extern RgbColor ABS_RGB_GRN;
extern RgbColor ABS_RGB_CYA;
extern RgbColor ABS_RGB_BLU;
extern RgbColor ABS_RGB_MAG;

extern RgbColor RGB_RED;
extern RgbColor RGB_YEL;
extern RgbColor RGB_GRN;
extern RgbColor RGB_CYA;
extern RgbColor RGB_BLU;
extern RgbColor RGB_MAG;


//------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
void initialize_color_times(float* color_times, float hours_between_colors);
void initialize_main_colors(RgbColor* colors);
void get_indices_of_colors (int* indices, float* color_times, float the_time);

RgbColor map_time_to_color(
  float  hrs_since_cycle_restart,
  float* times, RgbColor* colors,
  int    array_size);

#endif
