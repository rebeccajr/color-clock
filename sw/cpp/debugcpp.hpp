//------------------------------------------------------------------------------
// DESCRIPTION
// This class includes methods to print out statements to the serial console
// for informational and debug purposes
//------------------------------------------------------------------------------

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <vector>
#include "../arduino/color-clock-driver/classes.hpp"

class Debug{

public:
  static void print_labeled_dec(char* label, float num);
  static void print_color(RgbColor color);
  static void print_color(HsvColor color);
  static void print_color_array(std::vector<RgbColor> colors);
  static void print_color_array(std::vector<HsvColor> colors);
  static void print_interval_times(std::vector<float> times);
  static void print_new_line();
};

#endif
