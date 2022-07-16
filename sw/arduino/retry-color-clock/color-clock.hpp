//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains the class for a color clock object.
//------------------------------------------------------------------------------

#ifndef COLOR_CLOCK
#define COLOR_CLOCK

//------------------------------------------------------------------------------
#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <DS3231.h>

#include "alpha-display.hpp"
#include "classes.hpp"
#include "debug.hpp"
#include "logic.hpp"
#include "time-calcs.hpp"

#define CYCLE_PARTITIONS 6

class ColorClock{

public:
  int cycle_partitions;

  // The sampled time will fall bewtween two indices of
  // color_times. These variables are the
  // indices that the time falls between.
  int lo_color_index;                        
  int hi_color_index;

  AlphaDisplay the_alpha_display;
  DS3231       the_rtc;
  RgbColor     color_selection[CYCLE_PARTITIONS];
  float        color_times[CYCLE_PARTITIONS];

  // RGB constants
  static RgbColor ABS_RGB_RED;
  static RgbColor ABS_RGB_YEL;
  static RgbColor ABS_RGB_GRN;
  static RgbColor ABS_RGB_CYA;
  static RgbColor ABS_RGB_BLU;
  static RgbColor ABS_RGB_MAG;

  ColorClock();

  void     update_display_time();
  RgbColor time_to_color();
  void     determine_color_indices();
};

#endif
