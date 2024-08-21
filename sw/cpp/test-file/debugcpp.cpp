#include "debugcpp.hpp"

//------------------------------------------------------------------------------
void Debug::print_color(RgbColor color){
  printf("\nr: 0x%02x", color.r);
  printf("    g: 0x%02x", color.g);
  printf("    b: 0x%02x", color.b);
}


//------------------------------------------------------------------------------
void Debug::print_color(HsvColor color){
  printf("\nh: %5.2f", color.h);
  printf("  s: %5.2f", color.s);
  printf("  v: %5.2f", color.v);
}


//------------------------------------------------------------------------------
void Debug::print_color_array(std::vector<RgbColor> colors){
  for (int i = 0; i < colors.size(); ++i)
    print_color(colors[i]);
}


//------------------------------------------------------------------------------
void Debug::print_color_array(std::vector<HsvColor> colors){
  for (int i = 0; i < colors.size(); ++i)
    print_color(colors[i]);
}


//------------------------------------------------------------------------------
void Debug::print_interval_times(std::vector<float> times){
  for (int i = 0; i < times.size(); ++i)
    printf("%f ",times[i]);
}
