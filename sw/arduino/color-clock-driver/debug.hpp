//______________________________________________________________________________
// DESCRIPTION
// This class includes methods to print out statements to the serial console
// for informational and debug purposes
//______________________________________________________________________________

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <vector>

#include "color-classes.hpp"
#include "flux-macros.hpp"

#ifdef USING_DS3231
#include <DS3231.h>
#endif


class Debug{

public:
  static void print_string_with_new_line(char*, bool = true);
  static void print_labeled_int(char*, int);
  static void print_labeled_float(char*, float);
  static void print_color(RgbColor);
  static void print_color(HsvColor);
  static void print_color_array(std::vector<RgbColor>);
  static void print_color_array(std::vector<HsvColor>);
  static void print_interval_times(std::vector<float>);
  static void print_interval_times_in_sec(std::vector<float>);
  static void print_new_line();
#ifdef USING_DS3231
  static void print_time(DS3231);
#endif

};

#endif
