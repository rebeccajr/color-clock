#include "color-clock.hpp"

RgbColor ColorClock::ABS_RGB_RED = RgbColor(0xFF0000);
RgbColor ColorClock::ABS_RGB_YEL = RgbColor(0xFFFF00);
RgbColor ColorClock::ABS_RGB_GRN = RgbColor(0x00FF00);
RgbColor ColorClock::ABS_RGB_CYA = RgbColor(0x00FFFF);
RgbColor ColorClock::ABS_RGB_BLU = RgbColor(0xFF00FF);
RgbColor ColorClock::ABS_RGB_MAG = RgbColor(0xFF00FF);

ColorClock::ColorClock(){
  this->color_selection[0] = ABS_RGB_RED;
  this->color_selection[1] = ABS_RGB_YEL;
  this->color_selection[2] = ABS_RGB_GRN;
  this->color_selection[3] = ABS_RGB_CYA;
  this->color_selection[4] = ABS_RGB_BLU;
  this->color_selection[5] = ABS_RGB_MAG;
  
}
