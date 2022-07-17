#define CYCLE_PARTITIONS 6

#include <Arduino.h>
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

ColorClock the_first_colorclock;

byte set_hr    = 13;
byte set_min   = 54;
bool first_run = true;


//------------------------------------------------------------------------------
void setup(){
  Serial.begin(9600);
  the_first_colorclock.the_alpha_display.led_segments.begin(0x70);
  Wire.begin();

  // left off here - don't know why I can't see these
  // might want to move forward with a color clock object
  //initialize_color_selection(color_selection);
  //initialize_main_colors(main_colors);
}

//------------------------------------------------------------------------------
void loop(){

  // initialize clock
  if (first_run == true) {
    the_first_colorclock.the_rtc.setHour(set_hr);
    the_first_colorclock.the_rtc.setMinute(set_min);

    Debug::print_color_array(
      the_first_colorclock.color_selection,
      the_first_colorclock.cycle_partitions);

    first_run = false;
  }

  Debug::print_time(the_first_colorclock.the_rtc);
  
  the_first_colorclock.update_display_time();

  delay(1000);
}
