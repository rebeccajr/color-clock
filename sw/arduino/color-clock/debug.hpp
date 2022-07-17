//------------------------------------------------------------------------------
// DESCRIPTION
// This class includes methods to print out statements to the serial console
// for informational and debug purposes
//------------------------------------------------------------------------------

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <DS3231.h>

#include "classes.hpp"

class Debug{

public:
  static void print_labeled_dec(char* label, float num);
  static void print_color(RgbColor color);
  static void print_color(HsvColor color);
  static void print_color_array(RgbColor* colors, int array_size);
  static void print_color_array(HsvColor* colors, int array_size);
  static void print_time(DS3231 clk);
  static void print_new_line();
};

#endif
