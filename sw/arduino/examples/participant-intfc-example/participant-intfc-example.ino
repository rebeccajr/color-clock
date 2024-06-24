//______________________________________________________________
// This example tests the participant-facing user interface.
//______________________________________________________________

#include <Arduino.h>

#include "flux-macros.hpp"
#include "debug.hpp"
#include "momentary-switch.hpp"
#include "rgb-color.hpp"

#define DEFAULT_MOD_AMT 0x7F

using Rgb = RgbColor::PriColor;

int frq_inc_btn_pin =  6;
int red_inc_btn_pin =  7;
int grn_inc_btn_pin =  8;
int blu_inc_btn_pin =  9;
int frq_dec_btn_pin = 10;
int red_dec_btn_pin = 11;
int grn_dec_btn_pin = 12;
int blu_dec_btn_pin = 13;

int frq_led_pin = 0;
int red_led_pin = 1;
int grn_led_pin = 2;
int blu_led_pin = 3;

int frq_led_val = 0xFF;
int red_led_val = 0xFF;
int grn_led_val = 0xFF;
int blu_led_val = 0xFF;

MomentarySwitch frq_inc_btn ;
MomentarySwitch red_inc_btn ;
MomentarySwitch grn_inc_btn ;
MomentarySwitch blu_inc_btn ;
MomentarySwitch frq_dec_btn ;
MomentarySwitch red_dec_btn ;
MomentarySwitch grn_dec_btn ;
MomentarySwitch blu_dec_btn ;

RgbColor rgb;

void setup()
{
  pinMode(frq_led_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);
  pinMode(grn_led_pin, OUTPUT);
  pinMode(blu_led_pin, OUTPUT);

  pinMode(frq_inc_btn_pin, INPUT_PULLUP);
  pinMode(red_inc_btn_pin, INPUT_PULLUP);
  pinMode(grn_inc_btn_pin, INPUT_PULLUP);
  pinMode(blu_inc_btn_pin, INPUT_PULLUP);
  pinMode(frq_dec_btn_pin, INPUT_PULLUP);
  pinMode(red_dec_btn_pin, INPUT_PULLUP);
  pinMode(grn_dec_btn_pin, INPUT_PULLUP);
  pinMode(blu_dec_btn_pin, INPUT_PULLUP);

  rgb = RgbColor(0xFFFF00);

  frq_inc_btn = MomentarySwitch(frq_inc_btn_pin);
  red_inc_btn = MomentarySwitch(red_inc_btn_pin);
  grn_inc_btn = MomentarySwitch(grn_inc_btn_pin);
  blu_inc_btn = MomentarySwitch(blu_inc_btn_pin);
  frq_dec_btn = MomentarySwitch(frq_dec_btn_pin);
  red_dec_btn = MomentarySwitch(red_dec_btn_pin);
  grn_dec_btn = MomentarySwitch(grn_dec_btn_pin);
  blu_dec_btn = MomentarySwitch(blu_dec_btn_pin);
}

void loop()
{

  RgbColor color = RgbColor(red_led_val
    , grn_led_val
    , blu_led_val
  );

  //Serial.println("proof of life");
  if (frq_inc_btn.is_short_press() == true)
  {
    Serial.println("frq_inc pressed");
    frq_led_val += DEFAULT_MOD_AMT;
  }

  if (frq_dec_btn.is_short_press() == true)
  {
    Serial.println("frq_dec pressed");
    frq_led_val -= DEFAULT_MOD_AMT;
  }

  if (red_dec_btn.is_short_press() == true)
  {
    Debug::print_string_with_new_line("\n____________________");
    Serial.println("red_dec pressed");
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
    color.mod_color(Rgb::RED, RgbColor::IncDec::DECREMENT);
  }

  if (red_inc_btn.is_short_press() == true)
  {
    Debug::print_string_with_new_line("\n____________________");
    Serial.println("red_inc pressed");
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
    color.mod_color(Rgb::RED, RgbColor::IncDec::INC);
  }

  if (grn_dec_btn.is_short_press() == true)
  {
    Serial.println("grn_dec pressed");
    color.mod_color(Rgb::GRN, RgbColor::IncDec::DECREMENT);
  }

  if (grn_inc_btn.is_short_press() == true)
  {
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
    Serial.println("grn_inc pressed");
    color.mod_color(Rgb::GRN, RgbColor::IncDec::INC);
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
  }

  if (blu_dec_btn.is_short_press() == true)
  {
    Debug::print_string_with_new_line("\n____________________");
    Serial.println("blu_dec pressed");
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
    color.mod_color(Rgb::BLU, RgbColor::IncDec::DECREMENT);
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
  }

  if (blu_inc_btn.is_short_press() == true)
  {
    Debug::print_string_with_new_line("\n____________________");
    Serial.println("blu_inc pressed");
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
    color.mod_color(Rgb::BLU, RgbColor::IncDec::INC);
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
  }

  color.write_rgb_to_out(red_led_pin
    , grn_led_pin
    , blu_led_pin
  );

  red_led_val = color.rgb_[Rgb::RED];
  grn_led_val = color.rgb_[Rgb::GRN];
  blu_led_val = color.rgb_[Rgb::BLU];

  analogWrite(frq_led_pin, frq_led_val);
}
