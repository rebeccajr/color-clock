//______________________________________________________________________________
// DESCRIPTION
// This file contains the driver for the color clock project.
//______________________________________________________________________________

#include <Arduino.h>
#include <vector>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include "color-classes.hpp"
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

int red_pin_0 = A0;
int grn_pin_0 = A3;
int blu_pin_0 = A4;

int red_pin_1 = 0;
int grn_pin_1 = 1;
int blu_pin_1 = 2;

int red_pin_2 = 3;
int grn_pin_2 = 4;
int blu_pin_2 = 5;

int red_pin_3 = 6;
int grn_pin_3 = 7;
int blu_pin_3 = 8;

int inc_pin   = A1;
int dec_pin   = A2;
int enter_pin = A6;

MomentarySwitch inc_sw;
MomentarySwitch dec_sw;
MomentarySwitch enter_sw;

float cc0_period =  6.0 / TimeCalcs::SEC_IN_HR;
float cc1_period = 12.0 / TimeCalcs::SEC_IN_HR;
float cc2_period = 30.0 / TimeCalcs::SEC_IN_HR;
float cc3_period = 60.0 / TimeCalcs::SEC_IN_HR;

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
