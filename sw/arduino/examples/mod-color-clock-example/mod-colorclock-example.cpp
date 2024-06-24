#include "debug.hpp"
#include "color-clock.hpp"

int main()
{
  using Rgb = RgbColor::PriColor;

  Debug::print_new_line();
  Debug::print_new_line();

  FluxClock clk;
  ColorClock c = ColorClock(&clk, 1.0/240.0);

  c.mod_color_selection(Rgb::GRN, RgbColor::IncDec::INC);

  Debug::print_new_line();
  c.print_color_selections();
  Debug::print_new_line();
  Debug::print_new_line();

  return 0;
}
