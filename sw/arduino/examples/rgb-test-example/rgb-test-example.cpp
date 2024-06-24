#include <stdio.h>
#include "hsv-color.hpp"
#include "rgb-color.hpp"
#include "flux-macros.hpp"
#include "debug.hpp"

int main()
{
  RgbColor color = RgbColor(0xFF, 0x00, 0x00);
  color.bounds_check();
  Debug::print_new_line();
  Debug::print_new_line();

  Debug::print_color(color);

  Debug::print_new_line();
  Debug::print_new_line();

  char* line = (char*)("\n\n_______________________________");

  Debug::print_string_with_new_line(line);
  color.mod_color(RgbColor::PriColor::RED, RgbColor::IncDec::DECREMENT);
  color.bounds_check();
  Debug::print_color(color);
  Debug::print_string_with_new_line(line);
  color.mod_color(RgbColor::PriColor::BLU, RgbColor::IncDec::DECREMENT);
  color.bounds_check();
  Debug::print_color(color);

  Debug::print_new_line();
  Debug::print_new_line();
  return 0;
}
