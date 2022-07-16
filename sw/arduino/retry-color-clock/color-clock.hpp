//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains the class for a color clock object.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <DS3231.h>

#include "alpha-display.hpp"
#include "classes.hpp"
#include "debug.hpp"
#include "logic.hpp"
#include "time-calcs.hpp"

class ColorClock{

public:

  AlphaDisplay the_alpha_display;
  DS3231       the_rtc;

};
