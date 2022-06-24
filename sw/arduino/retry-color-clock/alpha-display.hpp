//------------------------------------------------------------------------------
// DESCRIPTION
// This class contains functionality for the alphanumeric display.
//------------------------------------------------------------------------------

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

class AlphaDisplay{

public:

  static Adafruit_AlphaNum4 the_alpha_display;

  static void write_display_time(byte hr, byte min, byte sec);
  static void write_flux_to_display();
};
