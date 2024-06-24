//______________________________________________________________________________
// DESCRIPTION
// This file contains the driver for the color clock project.
//______________________________________________________________________________

#include <Arduino.h>
#include <vector>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include "hsv-color.hpp"
#include "rgb-color.hpp"
#include "color-clock.hpp"
#include "debug.hpp"
#include "flux-clock.hpp"
#include "momentary-switch.hpp"
#include "time-calcs.hpp"
#include "time-display.hpp"
#include "top-level.hpp"


TopLevel    top_level;
TimeDisplay display;

ColorClock* cc0;
ColorClock* cc1;
ColorClock* cc2;
ColorClock* cc3;

FluxClock   the_clock;

int red_pin_0 = 0;
int grn_pin_0 = 1;
int blu_pin_0 = 2;

int red_pin_1 = 3;
int grn_pin_1 = 4;
int blu_pin_1 = 5;

int red_pin_2 = 6;
int grn_pin_2 = 7;
int blu_pin_2 = 8;

int red_pin_3 = A0;
int grn_pin_3 = A3;
int blu_pin_3 = A4;

int inc_pin   = 10;
int dec_pin   = 13;
int enter_pin = 14;

MomentarySwitch inc_sw;
MomentarySwitch dec_sw;
MomentarySwitch enter_sw;

float cc0_period =  6.0 / 3600.0;
float cc1_period = 12.0 / 3600.0;
float cc2_period = 30.0 / 3600.0;
float cc3_period = 60.0 / 3600.0;

//______________________________________________________________________________
void setup()
{
  pinMode(red_pin_0, OUTPUT);
  pinMode(grn_pin_0, OUTPUT);
  pinMode(blu_pin_0, OUTPUT);

  pinMode(red_pin_1, OUTPUT);
  pinMode(grn_pin_1, OUTPUT);
  pinMode(blu_pin_1, OUTPUT);

  pinMode(red_pin_2, OUTPUT);
  pinMode(grn_pin_2, OUTPUT);
  pinMode(blu_pin_2, OUTPUT);

  pinMode(inc_pin,   INPUT_PULLUP);
  pinMode(dec_pin,   INPUT_PULLUP);
  pinMode(enter_pin, INPUT_PULLUP);

  inc_sw    = MomentarySwitch(inc_pin);
  dec_sw    = MomentarySwitch(dec_pin);
  enter_sw  = MomentarySwitch(enter_pin);

  //____________________________________________________________________________

  Serial.begin(9600);
  display.led_segments.begin(0x70);
  Wire.begin();

  //____________________________________________________________________________

  cc0 = new ColorClock(&the_clock, cc0_period, ColorConstants::rmbcgy_);
  cc1 = new ColorClock(&the_clock, cc1_period, ColorConstants::rmbcgy_);
  cc2 = new ColorClock(&the_clock, cc2_period, ColorConstants::rmbcgy_);
  cc3 = new ColorClock(&the_clock, cc3_period, ColorConstants::rmbcgy_);

  top_level = TopLevel(&the_clock
    , inc_sw
    , dec_sw
    , enter_sw
    , &display
  );

  top_level.register_color_clock(cc0, red_pin_0, grn_pin_0, blu_pin_0);
  top_level.register_color_clock(cc1, red_pin_1, grn_pin_1, blu_pin_1);
  top_level.register_color_clock(cc2, red_pin_2, grn_pin_2, blu_pin_2);
  top_level.register_color_clock(cc3, red_pin_3, grn_pin_3, blu_pin_3);

}


//______________________________________________________________________________
void loop()
{
  top_level.run();
}
