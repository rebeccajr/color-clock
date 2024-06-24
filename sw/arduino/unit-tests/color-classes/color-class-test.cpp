#include <stdio.h>
#include "hsv-color.hpp"
#include "rgb-color.hpp"
//#include "color-const.hpp"
#include "debug.hpp"

void interpolate_test(int rgb1, int rgb2, float f);

int main(void)
{
  interpolate_test(0xFF0000, 0xFF00FF, 0.75);
  interpolate_test(0xFF00FF, 0xFF0000, 0.75);
  interpolate_test(0x00FF00, 0xFF0000, 0.25);
  interpolate_test(0xFF0000, 0x00FF00, 0.25);
}

void interpolate_test(int rgb1, int rgb2, float f)
{
  RgbColor color1 = RgbColor(rgb1);
  RgbColor color2 = RgbColor(rgb2);

  printf("\n____________________");
  Debug::print_new_line();
  Debug::print_new_line();
  printf("color1 rgb:");
  Debug::print_new_line();
  Debug::print_color(color1);
  Debug::print_new_line();
  printf("color1 hsv:");
  Debug::print_new_line();
  Debug::print_color(color1.to_hsv());
  Debug::print_new_line();
  Debug::print_new_line();
  printf("color2 rgb:");
  Debug::print_new_line();
  Debug::print_color(color2);
  Debug::print_new_line();
  HsvColor color1_hsv = color1.to_hsv();
  HsvColor color2_hsv = color2.to_hsv();
  Debug::print_color(color2_hsv);
  Debug::print_new_line();
  Debug::print_new_line();

  Debug::print_labeled_float("fraction = %f", f);
  Debug::print_new_line();
  Debug::print_new_line();
  Debug::print_color(HsvColor::interpolate_bet_hsvcolors(color1_hsv, color2_hsv, f));
  Debug::print_new_line();
  Debug::print_new_line();
}