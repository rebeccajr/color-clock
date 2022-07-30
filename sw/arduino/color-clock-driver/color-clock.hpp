//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains the class for a color clock object.
//------------------------------------------------------------------------------

#ifndef COLOR_CLOCK
#define COLOR_CLOCK

//------------------------------------------------------------------------------
#include <Arduino.h>
#include <vector>
#include <Wire.h>

#include <DS3231.h>

#include "alpha-display.hpp"
#include "classes.hpp"
#include "debug.hpp"
#include "logic.hpp"
#include "time-calcs.hpp"


class ColorClock{

public:
  int   partition_count;
  float cycle_time_in_hrs;

  // The sampled time will fall bewtween two indices of
  // color_times. These variables are the
  // indices that the time falls between.
  int lo_color_index;                        
  int hi_color_index;

  AlphaDisplay the_alpha_display;
  DS3231       the_rtc;

  std::vector<RgbColor>    color_selection;
  std::vector<float>       color_times;

  // RGB constants
  static RgbColor ABS_RGB_RED;
  static RgbColor ABS_RGB_YEL;
  static RgbColor ABS_RGB_GRN;
  static RgbColor ABS_RGB_CYA;
  static RgbColor ABS_RGB_BLU;
  static RgbColor ABS_RGB_MAG;

  static std::vector<RgbColor> default_color_selection;
  static std::vector<RgbColor> initialize_default_vector();

  ColorClock();
  ~ColorClock();
  ColorClock(int num_of_partitions, float cycle_time);

  void     update_display_time();
  RgbColor time_to_color();
  void     determine_color_indices();
};

#endif
