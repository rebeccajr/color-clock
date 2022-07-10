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

#define DEBUG 0

DS3231 the_first_rtc;

byte set_hr    = 13;
byte set_min   = 54;
bool first_run = true;


//------------------------------------------------------------------------------
void setup(){
  Serial.begin(9600);
  AlphaDisplay::the_alpha_display.begin(0x70);
  Wire.begin();
}

//------------------------------------------------------------------------------
void loop(){

  // initialize clock
  if (first_run == true) {
    the_first_rtc.setHour(set_hr);
    the_first_rtc.setMinute(set_min);
    first_run = false;
  }

  RgbColor color;
  Debug::print_new_line();
  Debug::print_color(color);

  Debug::print_time(the_first_rtc);
  AlphaDisplay::write_flux_to_display();

  delay(1000);
}
