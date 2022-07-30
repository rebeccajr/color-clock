//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains the driver for the color clock project.
//------------------------------------------------------------------------------

#define CYCLE_PARTITIONS 6

#include <Arduino.h>
#include <vector>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <DS3231.h>

#include "alpha-display.hpp"
#include "classes.hpp"
#include "color-clock.hpp"
#include "debug.hpp"
#include "logic.hpp"
#include "time-calcs.hpp"

ColorClock* the_first_colorclock;

byte set_hr    = 13;
byte set_min   = 54;
bool first_run = true;

//------------------------------------------------------------------------------
void setup(){
  the_first_colorclock = new ColorClock(6, 24);
  Serial.begin(9600);
  the_first_colorclock->the_alpha_display.led_segments.begin(0x70);
  Wire.begin();
}

//------------------------------------------------------------------------------
void loop(){

  // initialize clock
  if (first_run == true) {
    the_first_colorclock->the_rtc.setHour(set_hr);
    the_first_colorclock->the_rtc.setMinute(set_min);

    first_run = false;
  }

  Debug::print_color_array(the_first_colorclock->color_selection);
  Debug::print_interval_times(the_first_colorclock->color_times);
  Debug::print_time(the_first_colorclock->the_rtc);
  
  the_first_colorclock->update_display_time();

  delay(1000);
}
