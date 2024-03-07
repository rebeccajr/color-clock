//------------------------------------------------------------------------------
// DESCRIPTION
// This class contains functionality for the alphanumeric display.
//------------------------------------------------------------------------------
#ifndef ALPHA_DISPLAY
#define ALPHA_DISPLAY

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

class AlphaDisplay{

public:

  Adafruit_AlphaNum4 led_segments;

  void write_display_time(byte hr, byte min, byte sec);
  void write_flux_to_display();
};

#endif
