//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains the class for a color clock object.
//------------------------------------------------------------------------------

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

  // when mapping the time to color, a time will fall between
  // two indices of the color times. These variables are the
  // indices that the current time falls between.
  int lo_color_index;                        
  int hi_color_index;

  AlphaDisplay the_alpha_display;
  DS3231       the_rtc;
  RgbColor     color_selection[CYCLE_PARTITIONS];
  float        color_times[CYCLE_PARTITIONS];

  ColorClock(){};
  RgbColor time_to_color();
  void     determine_color_indices();
};
