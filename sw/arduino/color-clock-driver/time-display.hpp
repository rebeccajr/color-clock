//______________________________________________________________________________
// DESCRIPTION
// This class contains functionality for the alphanumeric display.
//______________________________________________________________________________
#ifndef ALPHA_DISPLAY
#define ALPHA_DISPLAY

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

class TimeDisplay
{

public:

  Adafruit_AlphaNum4 led_segments;

  void write_disp_str(const char*);
  void write_disp_str_num(const char* str, byte num);
  void write_disp_hr_min(byte hr, byte min);
  void write_disp_time(byte, byte);

  void write_disp_yr(byte yr);
  void write_disp_mo(byte mo);
  void write_disp_day(byte day);
  void write_disp_hr(byte hr);
  void write_disp_min(byte min);

};

#endif
