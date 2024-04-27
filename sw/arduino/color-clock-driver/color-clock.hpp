//______________________________________________________________________________
// This file contains the class declaration for a color clock object.
//______________________________________________________________________________

#ifndef COLOR_CLOCK
#define COLOR_CLOCK

#include <Arduino.h>
#include <vector>
#include <Wire.h>

#include "flux-clock.hpp"
#include "color-classes.hpp"
#include "color-const.hpp"
#include "time-calcs.hpp"
#include "time-display.hpp"


//______________________________________________________________________________
class ColorClock
{

public:
  double cycle_time_in_hrs_;

  // The sampled time will fall bewtween two indices of
  // color_times_. These variables are the
  // indices that the time falls between.
  int lo_color_index_;
  int hi_color_index_;

  TimeDisplay time_display_;
  FluxClock* clock_;

  std::vector<RgbColor>    color_selection_;
  std::vector<float>       color_times_;

  ColorClock(){};
  ~ColorClock()
  {
    color_times_.clear();
    color_selection_.clear();
  }

  ColorClock(FluxClock* the_clock
  , double cycle_time_in_hrs
  , std::vector<RgbColor> colors = ColorConstants::roygbiv_
  );

  RgbColor time_to_color();
  void set_cycle_time(double);
  void determine_color_indices(float);
  void print();
};

#endif
