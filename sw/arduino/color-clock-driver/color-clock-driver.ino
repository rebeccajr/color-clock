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
#include "time-display.hpp"

#include "top-level.hpp"

ColorClock* the_first_colorclock;
DS3231 rtc;

bool first_run = true;

std::vector<RgbColor> color_vect;

int red_pin = A0;
int grn_pin = A1;
int blu_pin = A2;

int inc_pin   = 0;
int dec_pin   = 1;
int enter_pin = 2;

MomentarySwitch inc_sw;
MomentarySwitch dec_sw;
MomentarySwitch enter_sw;

TimeDisplay     display;
TopLevel top_level;

float cc0_freq = 1.0/120.0;
float cc1_freq = 1.0/240.0;
float cc2_freq = 1.0/60.0;

//______________________________________________________________________________
void setup()
{

  //____________________________________________________________________________
  color_vect.push_back(ColorClock::RED); // 0
  color_vect.push_back(ColorClock::YEL); // 5
  color_vect.push_back(ColorClock::GRN); // 10
  color_vect.push_back(ColorClock::CYA); // 15
  color_vect.push_back(ColorClock::BLU); // 20
  color_vect.push_back(ColorClock::MAG); // 25
  //____________________________________________________________________________

  the_first_colorclock = new ColorClock(&rtc, 1.0/120.0, color_vect);

  //____________________________________________________________________________

  inc_sw    = MomentarySwitch(inc_pin);
  dec_sw    = MomentarySwitch(dec_pin);
  enter_sw  = MomentarySwitch(enter_pin);

  //____________________________________________________________________________

  Serial.begin(9600);
  display.led_segments.begin(0x70);
  Wire.begin();

  //____________________________________________________________________________

  pinMode(red_pin, OUTPUT);
  pinMode(grn_pin, OUTPUT);
  pinMode(blu_pin, OUTPUT);

  pinMode(inc_pin,   INPUT_PULLUP);
  pinMode(dec_pin,   INPUT_PULLUP);
  pinMode(enter_pin, INPUT_PULLUP);

  top_level = TopLevel(&rtc
    , inc_sw
    , dec_sw
    , enter_sw
    , &display
    , cc0_freq
    , cc1_freq
    , cc2_freq);
}


//______________________________________________________________________________
void loop()
{
  top_level.run();
}
