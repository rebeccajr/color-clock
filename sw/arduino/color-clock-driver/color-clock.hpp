//______________________________________________________________________
//______________________________________________________________________
//      _   __   _   _ _   _   _   _         _
// |   |_| | _  | | | V | | | | / |_/ |_| | /
// |__ | | |__| |_| |   | |_| | \ |   | | | \_
//  _  _         _ ___  _       _ ___   _                        / /
// /  | | |\ |  \   |  | / | | /   |   \                        (^^)
// \_ |_| | \| _/   |  | \ |_| \_  |  _/                        (____)o
//______________________________________________________________________
//______________________________________________________________________
//
//----------------------------------------------------------------------
// Copyright 2024, Rebecca Rashkin
// -------------------------------
// This code may be copied, redistributed, transformed, or built upon in
// any format for educational, non-commercial purposes.
//
// Please give me appropriate credit should you choose to use this
// resource. Thank you :)
//----------------------------------------------------------------------
//
//______________________________________________________________________
// //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\
//______________________________________________________________________
//______________________________________________________________________
// This file contains the class declaration for a color clock object.
//______________________________________________________________________

#ifndef COLOR_CLOCK
#define COLOR_CLOCK

#ifdef ARDUINO_BUILD
#include <Arduino.h>
#include <Wire.h>
#endif
#include <vector>

#include "flux-macros.hpp"

#ifdef UNIT_TEST
# include "mock-flux-clock.hpp"
#else
# include "flux-clock.hpp"
#endif

#include "hsv-color.hpp"
#include "rgb-color.hpp"
#include "color-const.hpp"
#include "time-calcs.hpp"

class FluxClock;

//______________________________________________________________________
class ColorClock
{
  using Rgb = RgbColor::PriColor;

public:
  double cycle_time_in_hrs_;

  // The sampled time will fall bewtween two indices of
  // color_times_. These variables are the
  // indices that the time falls between.
  int lo_color_index_;
  int hi_color_index_;

  FluxClock* clock_;

  float mod_cycle_amt_;
  float min_cycle_time_;
  float max_cycle_time_;

  std::vector<RgbColor>    init_color_selection_;
  std::vector<RgbColor>    crnt_color_selection_;
  std::vector<float>       color_times_;

  ColorClock(){};
  ~ColorClock()
  {
    color_times_.clear();
    crnt_color_selection_.clear();
  }

  ColorClock(FluxClock* the_clock
  , double cycle_time_in_hrs
  , std::vector<RgbColor> colors = ColorConst::roygbiv_
  );

  void reset_color_selection()
  {
    crnt_color_selection_ = init_color_selection_;
  }

  RgbColor time_to_color();

  void set_cycle_time(double);
  void set_min_max_cycle_time(float, float);
  void set_mod_cycle_amt(float);
  void determine_color_indices(float);
  void mod_color_selection(Rgb, RgbColor::IncDec);
  void mod_cycle_time(RgbColor::IncDec);

  void print();
  void print_color_selections();
};

#endif
