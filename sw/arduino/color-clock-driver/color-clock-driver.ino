//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains the driver for the color clock project.
//------------------------------------------------------------------------------

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

byte set_hr    = 1;
byte set_min   = 12;
bool first_run = true;

std::vector<RgbColor> color_vect;

int red_pin = A0;
int grn_pin = A1;
int blu_pin = A2;


//------------------------------------------------------------------------------
void setup(){
  color_vect.push_back(ColorClock::ABS_RGB_RED); // 0
  color_vect.push_back(ColorClock::ABS_RGB_YEL); // 5
  color_vect.push_back(ColorClock::ABS_RGB_GRN); // 10
  color_vect.push_back(ColorClock::ABS_RGB_CYA); // 15
  color_vect.push_back(ColorClock::ABS_RGB_BLU); // 20
  color_vect.push_back(ColorClock::ABS_RGB_MAG); // 25

  the_first_colorclock = new ColorClock(1.0/120.0, color_vect);

  Serial.begin(9600);
  the_first_colorclock->the_alpha_display.led_segments.begin(0x70);
  Wire.begin();

  pinMode(red_pin, OUTPUT);
  pinMode(grn_pin, OUTPUT);
  pinMode(blu_pin, OUTPUT);
}


//------------------------------------------------------------------------------
void loop(){

  // initialize clock
  if (first_run == true) {
    the_first_colorclock->the_rtc.setHour(set_hr);
    the_first_colorclock->the_rtc.setMinute(set_min);

    first_run = false;
  }

  Debug::print_time(the_first_colorclock->the_rtc);
  RgbColor crnt_color_time = the_first_colorclock->time_to_color();

  Serial.println("");
  Serial.println("_________________________________________________");
  Serial.println("_________________________________________________");
  Serial.println("Interval times");
  Debug::print_interval_times_in_sec(the_first_colorclock->color_times);
  Serial.println("");
  Serial.println("");
  Serial.print("cycle time in sec: ");
  Serial.println(3600 * the_first_colorclock->cycle_time_in_hrs);
  Serial.print("partition count:   ");
  Serial.println(the_first_colorclock->partition_count);
  Serial.println("_________________________________________________");

  analogWrite(red_pin, crnt_color_time.r);
  analogWrite(grn_pin, crnt_color_time.g);
  analogWrite(blu_pin, crnt_color_time.b);
  
  the_first_colorclock->update_display_time();

  delay(1000);
}
