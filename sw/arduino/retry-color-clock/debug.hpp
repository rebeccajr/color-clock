//------------------------------------------------------------------------------
// DESCRIPTION
// This class includes methods to print out statements to the serial console
// for informational and debug purposes
//------------------------------------------------------------------------------

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "classes.hpp"

class Debug{

public:
  static void print_color(RgbColor color);
  static void print_color(HsvColor color);
  static void print_new_line();

};

#endif
