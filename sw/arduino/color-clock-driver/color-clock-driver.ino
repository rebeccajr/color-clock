//______________________________________________________________________________
// DESCRIPTION
// This file contains the driver for the color clock project.
//______________________________________________________________________________

#include <Arduino.h>
#include <vector>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <DS3231.h>

#include "classes.hpp"
#include "color-clock.hpp"
#include "debug.hpp"
#include "logic.hpp"
#include "time-calcs.hpp"
#include "time-controller.hpp"
#include "time-display.hpp"

ColorClock* the_first_colorclock;

byte set_yr    = 24;
byte set_mo    = 03;
byte set_day   = 1;
byte set_hr    = 8;
byte set_min   = 0;

bool first_run = true;

std::vector<RgbColor> color_vect;

int red_pin = A0;
int grn_pin = A1;
int blu_pin = A2;

int inc_pin   = 0;
int dec_pin   = 1;
int enter_pin = 2;

int counter = 0;

MomentarySwitch inc_sw;
MomentarySwitch dec_sw;
MomentarySwitch enter_sw;

TimeDisplay     display;
TimeController  time_ctrl;

//______________________________________________________________________________
void setup()
{
  color_vect.push_back(ColorClock::ABS_RGB_RED); // 0
  color_vect.push_back(ColorClock::ABS_RGB_YEL); // 5
  color_vect.push_back(ColorClock::ABS_RGB_GRN); // 10
  color_vect.push_back(ColorClock::ABS_RGB_CYA); // 15
  color_vect.push_back(ColorClock::ABS_RGB_BLU); // 20
  color_vect.push_back(ColorClock::ABS_RGB_MAG); // 25
  //____________________________________________________________________________

  the_first_colorclock = new ColorClock(1.0/120.0, color_vect);

  //____________________________________________________________________________


  //____________________________________________________________________________

  inc_sw    = MomentarySwitch(inc_pin);
  dec_sw    = MomentarySwitch(dec_pin);
  enter_sw  = MomentarySwitch(enter_pin);

  //____________________________________________________________________________

  time_ctrl = TimeController(&(the_first_colorclock->the_rtc)
    , inc_sw
    , dec_sw
    , enter_sw
    , &(the_first_colorclock->the_alpha_display)
  );

  Serial.begin(9600);
  the_first_colorclock->the_alpha_display.led_segments.begin(0x70);
  Wire.begin();

  //____________________________________________________________________________

  pinMode(red_pin, OUTPUT);
  pinMode(grn_pin, OUTPUT);
  pinMode(blu_pin, OUTPUT);

  pinMode(inc_pin,   INPUT_PULLUP);
  pinMode(dec_pin,   INPUT_PULLUP);
  pinMode(enter_pin, INPUT_PULLUP);
}


//______________________________________________________________________________
void loop(){

  time_ctrl.set_time();

}
