//______________________________________________________________________________
// DESCRIPTION
// This file contains the driver for the color clock project.
//______________________________________________________________________________

#include <Arduino.h>
#include <vector>
#include <Wire.h>

#include <Adafruit_AW9523.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include "flux-macros.hpp"

#include "hsv-color.hpp"
#include "rgb-color.hpp"
#include "color-clock.hpp"
#include "debug.hpp"
#include "flux-clock.hpp"
#include "momentary-switch.hpp"
#include "time-calcs.hpp"
#include "time-display.hpp"
#include "top-level.hpp"


#define CC3_CYCLE_TIME_HOURS 24.0
#define CC2_CYCLE_TIME_HOURS  1.0
#define CC1_CYCLE_TIME_HOURS  1.0 / 60.0
#define CC0_CYCLE_TIME_HOURS (12.0 / SECONDS_PER_HOUR)

#define START_YEAR  24
#define START_MONTH  8

TopLevel    top_level;
TimeDisplay display;

ColorClock* cc0;
ColorClock* cc1;
ColorClock* cc2;
ColorClock* cc3;

FluxClock   the_clock;

int red_pin_0 = 8;
int grn_pin_0 = 7;
int blu_pin_0 = 6;

int red_pin_1 = 5;
int grn_pin_1 = 4;
int blu_pin_1 = 3;

int red_pin_2 = 2;
int grn_pin_2 = 1;
int blu_pin_2 = 0;

int red_pin_3 = A4;
int grn_pin_3 = A3;
int blu_pin_3 = A0;

uint8_t inc_pin   = 14;
uint8_t dec_pin   = 13;
uint8_t enter_pin = 15;


MomentarySwitch inc_sw;
MomentarySwitch dec_sw;
MomentarySwitch enter_sw;

//______________________________________________________________________________
// Participant control
//______________________________________________________________________________
Adafruit_AW9523 aw;

MomentarySwitch frq_inc_btn;
MomentarySwitch red_inc_btn;
MomentarySwitch grn_inc_btn;
MomentarySwitch blu_inc_btn;
MomentarySwitch frq_dec_btn;
MomentarySwitch red_dec_btn;
MomentarySwitch grn_dec_btn;
MomentarySwitch blu_dec_btn;

uint8_t frq_inc_btn_pin = 1;
uint8_t red_inc_btn_pin = 2;
uint8_t grn_inc_btn_pin = 3;
uint8_t blu_inc_btn_pin = 4;
uint8_t frq_dec_btn_pin = 5;
uint8_t red_dec_btn_pin = 6;
uint8_t grn_dec_btn_pin = 7;
uint8_t blu_dec_btn_pin = 12;
//______________________________________________________________________________

float cc0_period = CC0_CYCLE_TIME_HOURS;
float cc1_period = CC1_CYCLE_TIME_HOURS;
float cc2_period = CC2_CYCLE_TIME_HOURS;
float cc3_period = CC3_CYCLE_TIME_HOURS;

//______________________________________________________________________________
void setup()
{
  Serial.begin(115200);
  Serial.println("Adafruit AW9523 Constant Current LED test!");

  if (! aw.begin(IO_EXPANDER_ADDR)) {
    Serial.println("AW9523 not found? Check wiring!");
    //while (1) delay(10);  // halt forever
  }

  aw.pinMode(inc_pin, INPUT_PULLUP);
  aw.pinMode(dec_pin, INPUT_PULLUP);
  aw.pinMode(enter_pin, INPUT_PULLUP);

  aw.pinMode(frq_inc_btn_pin, INPUT_PULLUP);
  aw.pinMode(red_inc_btn_pin, INPUT_PULLUP);
  aw.pinMode(grn_inc_btn_pin, INPUT_PULLUP);
  aw.pinMode(blu_inc_btn_pin, INPUT_PULLUP);
  aw.pinMode(frq_dec_btn_pin, INPUT_PULLUP);
  aw.pinMode(red_dec_btn_pin, INPUT_PULLUP);
  aw.pinMode(grn_dec_btn_pin, INPUT_PULLUP);
  aw.pinMode(blu_dec_btn_pin, INPUT_PULLUP);


  pinMode(red_pin_0, OUTPUT);
  pinMode(grn_pin_0, OUTPUT);
  pinMode(blu_pin_0, OUTPUT);

  pinMode(red_pin_1, OUTPUT);
  pinMode(grn_pin_1, OUTPUT);
  pinMode(blu_pin_1, OUTPUT);

  pinMode(red_pin_2, OUTPUT);
  pinMode(grn_pin_2, OUTPUT);
  pinMode(blu_pin_2, OUTPUT);

  inc_sw    = MomentarySwitch(inc_pin, &aw);
  dec_sw    = MomentarySwitch(dec_pin, &aw);
  enter_sw  = MomentarySwitch(enter_pin, &aw);

  frq_inc_btn = MomentarySwitch(frq_inc_btn_pin, &aw);
  red_inc_btn = MomentarySwitch(red_inc_btn_pin, &aw);
  grn_inc_btn = MomentarySwitch(grn_inc_btn_pin, &aw);
  blu_inc_btn = MomentarySwitch(blu_inc_btn_pin, &aw);
  frq_dec_btn = MomentarySwitch(frq_dec_btn_pin, &aw);
  red_dec_btn = MomentarySwitch(red_dec_btn_pin, &aw);
  grn_dec_btn = MomentarySwitch(grn_dec_btn_pin, &aw);
  blu_dec_btn = MomentarySwitch(blu_dec_btn_pin, &aw);

  //____________________________________________________________________________

  Serial.begin(9600);
  display.led_segments.begin(LED_BACKPACK_ADDR);
  Wire.begin();

  //____________________________________________________________________________

  cc0 = new ColorClock(&the_clock, cc0_period, ColorConst::rgb_);
  cc1 = new ColorClock(&the_clock, cc1_period, ColorConst::roygbiv_);
  cc2 = new ColorClock(&the_clock, cc2_period, ColorConst::roygbiv_);
  cc3 = new ColorClock(&the_clock, cc3_period, ColorConst::roygbiv_);

  // TODO make buttons a vector
  top_level = TopLevel(&the_clock
    , &display
    , inc_sw
    , dec_sw
    , enter_sw
    , &aw
    , frq_inc_btn
    , red_inc_btn
    , grn_inc_btn
    , blu_inc_btn
    , frq_dec_btn
    , red_dec_btn
    , grn_dec_btn
    , blu_dec_btn
  );

  top_level.register_color_clock(cc0, red_pin_0, grn_pin_0, blu_pin_0);
  top_level.register_color_clock(cc1, red_pin_1, grn_pin_1, blu_pin_1);
  top_level.register_color_clock(cc2, red_pin_2, grn_pin_2, blu_pin_2);
  top_level.register_color_clock(cc3, red_pin_3, grn_pin_3, blu_pin_3);
  top_level.set_participant_ctrl(cc0);

  the_clock.set_yr(START_YEAR);
  the_clock.set_month(START_MONTH);
}


//______________________________________________________________________________
void loop()
{
  top_level.run();
}
