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

#define SEC_IN_HR 3600

#define CC0_IN_SEC 
#define CC1_IN_SEC
#define CC2_IN_SEC 60
#define CC3_IN_SEC 120

//#define CC0_IN_HR CC0_IN_SEC / SEC_IN_HR
//#define CC1_IN_HR CC1_IN_SEC / SEC_IN_HR
#define CC0_IN_HR 1
#define CC1_IN_HR 24
#define CC2_IN_HR CC2_IN_SEC / SEC_IN_HR
#define CC3_IN_HR CC3_IN_SEC / SEC_IN_HR


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

float cc0_period = CC0_IN_HR;
float cc1_period = CC1_IN_HR;
float cc2_period = CC2_IN_HR;
float cc3_period = CC3_IN_HR;

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
