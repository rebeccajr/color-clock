//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains classes that represent RGB and HSV
// color objects.
//
// RgbColor contains three member variables:
// r (red)    range: [0, 255] or [0x00, 0xFF]
// g (green)  range: [0, 255] or [0x00, 0xFF]
// b (blue)   range: [0, 255] or [0x00, 0xFF]
//
// RGB colors are used to define the main colors that the clock will cycle
// through.
//
// HsvColor contains three member variables:
// h (hue)        range: [0, 360]
// s (saturation) range: [0, 100]
// v (value)      range: [0, 100]
//------------------------------------------------------------------------------

#define DEBUG 1

#include <algorithm>
#include <cmath>
#include <stdio.h>
#include "debugcpp.cpp"
#include "../arduino/color-clock-driver/classes.hpp"
#include "../arduino/color-clock-driver/time-calcs.hpp"

int main()
{
  RgbColor RED = RgbColor(0xFF0000);
  RgbColor YEL = RgbColor(0xFFFF00);
  RgbColor GRN = RgbColor(0x00FF00);
  RgbColor CYA = RgbColor(0x00FFFF);
  RgbColor BLU = RgbColor(0xFF00FF);
  RgbColor MAG = RgbColor(0xFF00FF);

  std::vector<RgbColor> rgb_color_selection;
  std::vector<HsvColor> hsv_color_selection;

  HsvColor h = HsvColor(64.421985,100,100);
  RgbColor r = h.to_rgb();
  Debug::print_color(h);
  Debug::print_color(r);
  Debug::print_color(r.to_hsv());
  Debug::print_color(h.to_rgb());

  rgb_color_selection.push_back(RED);
  rgb_color_selection.push_back(YEL);
  rgb_color_selection.push_back(GRN);
  rgb_color_selection.push_back(CYA);
  rgb_color_selection.push_back(BLU);
  rgb_color_selection.push_back(MAG);
  printf("\n\n");
  Debug::print_color_array(rgb_color_selection);
  printf("\n\n");

  TimeCalcs::get_time_as_fractional_offset(10, 20, 13);

}
