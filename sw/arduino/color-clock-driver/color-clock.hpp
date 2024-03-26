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

#include "time-display.hpp"
#include "classes.hpp"
#include "debug.hpp"
#include "logic.hpp"
#include "time-calcs.hpp"


class ColorClock
{

public:
  int   partition_count_;
  float cycle_time_in_hrs_;

  // The sampled time will fall bewtween two indices of
  // color_times_. These variables are the
  // indices that the time falls between.
  int lo_color_index_;
  int hi_color_index;

  TimeDisplay time_display_;
  DS3231* rtc_;

  std::vector<RgbColor>    color_selection_;
  std::vector<float>       color_times_;

  // RGB constants
  static RgbColor RED;
  static RgbColor YEL;
  static RgbColor GRN;
  static RgbColor CYA;
  static RgbColor BLU;
  static RgbColor MAG;

  static std::vector<RgbColor> default_color_selection;
  static std::vector<RgbColor> initialize_default_vector();

  ColorClock();
  ~ColorClock();
  ColorClock(DS3231* rtc, float cycle_time_in_hrs,
    std::vector<RgbColor> colors = default_color_selection);

  void     update_display_time();
  RgbColor time_to_color();
  void     determine_color_indices(float time);
};

#endif
