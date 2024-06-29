//______________________________________________________________
// This example tests the participant-facing user interface.
//______________________________________________________________

#include <Arduino.h>

#include "flux-macros.hpp"
#include "debug.hpp"
#include "momentary-switch.hpp"
#include "rgb-color.hpp"
#include "participant-ctrl.hpp"

#define DEFAULT_MOD_AMT 0x7F

using Rgb = RgbColor::PriColor;

Adafruit_AW9523 aw;

int frq_inc_btn_pin = 4;
int red_inc_btn_pin = 5;
int grn_inc_btn_pin = 6;
int blu_inc_btn_pin = 7;
int frq_dec_btn_pin = 0;
int red_dec_btn_pin = 1;
int grn_dec_btn_pin = 2;
int blu_dec_btn_pin = 3;

int frq_led_pin = 0;
int red_led_pin = 1;
int grn_led_pin = 2;
int blu_led_pin = 3;

int frq_led_val = 0xFF;
int red_led_val = 0xFF;
int grn_led_val = 0xFF;
int blu_led_val = 0xFF;

MomentarySwitch frq_inc_btn;
MomentarySwitch red_inc_btn;
MomentarySwitch grn_inc_btn;
MomentarySwitch blu_inc_btn;
MomentarySwitch frq_dec_btn;
MomentarySwitch red_dec_btn;
MomentarySwitch grn_dec_btn;
MomentarySwitch blu_dec_btn;

ParticipantCtrl participant_intfc;
ColorClock cc;
FluxClock clocky;

float cc0_period =  6.0 / 3600.0;

RgbColor color;

void setup()
{
  Serial.begin(115200);
  Serial.println("Adafruit AW9523 Constant Current LED test!");

  if (! aw.begin(0x58)) {
    Serial.println("AW9523 not found? Check wiring!");
    while (1) delay(10);  // halt forever
  }

  //____________________________________________________________
  pinMode(frq_led_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);
  pinMode(grn_led_pin, OUTPUT);
  pinMode(blu_led_pin, OUTPUT);
  //____________________________________________________________
  aw.pinMode(frq_inc_btn_pin, INPUT_PULLUP);
  aw.pinMode(red_inc_btn_pin, INPUT_PULLUP);
  aw.pinMode(grn_inc_btn_pin, INPUT_PULLUP);
  aw.pinMode(blu_inc_btn_pin, INPUT_PULLUP);
  aw.pinMode(frq_dec_btn_pin, INPUT_PULLUP);
  aw.pinMode(red_dec_btn_pin, INPUT_PULLUP);
  aw.pinMode(grn_dec_btn_pin, INPUT_PULLUP);
  aw.pinMode(blu_dec_btn_pin, INPUT_PULLUP);
  //____________________________________________________________
  frq_inc_btn = MomentarySwitch(frq_inc_btn_pin, &aw);
  red_inc_btn = MomentarySwitch(red_inc_btn_pin, &aw);
  grn_inc_btn = MomentarySwitch(grn_inc_btn_pin, &aw);
  blu_inc_btn = MomentarySwitch(blu_inc_btn_pin, &aw);
  frq_dec_btn = MomentarySwitch(frq_dec_btn_pin, &aw);
  red_dec_btn = MomentarySwitch(red_dec_btn_pin, &aw);
  grn_dec_btn = MomentarySwitch(grn_dec_btn_pin, &aw);
  blu_dec_btn = MomentarySwitch(blu_dec_btn_pin, &aw);
  //____________________________________________________________

  cc = ColorClock(&clocky, cc0_period);

  participant_intfc = ParticipantCtrl(&cc
    , &frq_inc_btn
    , &red_inc_btn
    , &grn_inc_btn
    , &blu_inc_btn
    , &frq_dec_btn
    , &red_dec_btn
    , &grn_dec_btn
    , &blu_dec_btn
    
  );

  RgbColor color = RgbColor(red_led_val
    , grn_led_val
    , blu_led_val
  );

}

void loop()
{
  participant_intfc.run();
  color.write_rgb_to_out(red_led_pin
    , grn_led_pin
    , blu_led_pin
  );

  red_led_val = color.rgb_[Rgb::RED];
  grn_led_val = color.rgb_[Rgb::GRN];
  blu_led_val = color.rgb_[Rgb::BLU];

  analogWrite(frq_led_pin, frq_led_val);
}
