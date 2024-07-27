//______________________________________________________________________________
// DESCRIPTION
// This class contains functionality for the alphanumeric display.
//______________________________________________________________________________
#ifndef ALPHA_DISPLAY
#define ALPHA_DISPLAY

#include "flux-macros.hpp"

#ifdef ARDUINO_BUILD
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#endif

class TimeDisplay
{

public:

#ifdef ARDUINO_BUILD
  Adafruit_AlphaNum4 led_segments;
#endif

  void write_disp_str(const char*);
  void write_disp_str_num(const char* str, uint8_t num);
  void write_disp_hr_min(uint8_t hr, uint8_t min);
  void write_disp_time(uint8_t, uint8_t);

  void write_disp_yr(uint8_t yr);
  void write_disp_mo(uint8_t mo);
  void write_disp_day(uint8_t day);
  void write_disp_hr(uint8_t hr);
  void write_disp_min(uint8_t min);
  void write_disp_sec(uint8_t sec);

};

#endif
