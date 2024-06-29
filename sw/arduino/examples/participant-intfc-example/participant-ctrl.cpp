//______________________________________________________________________________
// Implementation for participant user control functions.
//______________________________________________________________________________

#define DEFAULT_MOD_AMT 0x7F
#include <stdint.h>
#include "debug.hpp"
#include "participant-ctrl.hpp"

using Rgb = RgbColor::PriColor;

void ParticipantCtrl::run()
{
  static RgbColor color = RgbColor(0xFFFF00);

  //Serial.println("proof of life");
  if (frq_inc_btn_->is_short_press() == true)
  {
    Serial.println("frq_inc pressed");
    //frq_led_val += DEFAULT_MOD_AMT;
  }

  if (frq_dec_btn_->is_short_press() == true)
  {
    Serial.println("frq_dec pressed");
    //frq_led_val -= DEFAULT_MOD_AMT;
  }

  if (red_dec_btn_->is_short_press() == true)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("red_dec pressed");
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
    color.mod_color(Rgb::RED, RgbColor::IncDec::DECREMENT);
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
  }

  if (red_inc_btn_->is_short_press() == true)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("red_inc pressed");
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
    color.mod_color(Rgb::RED, RgbColor::IncDec::INC);
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
  }

  if (grn_dec_btn_->is_short_press() == true)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("grn_dec pressed");
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
    color.mod_color(Rgb::GRN, RgbColor::IncDec::DECREMENT);
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
  }

  if (grn_inc_btn_->is_short_press() == true)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("grn_inc pressed");
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
    color.mod_color(Rgb::GRN, RgbColor::IncDec::INC);
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
  }

  if (blu_dec_btn_->is_short_press() == true)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("blu_dec pressed");
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
    color.mod_color(Rgb::BLU, RgbColor::IncDec::DECREMENT);
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
  }

  if (blu_inc_btn_->is_short_press() == true)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("blu_inc pressed");
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
    color.mod_color(Rgb::BLU, RgbColor::IncDec::INC);
    Debug::print_new_line();
    Debug::print_color(color);
    Debug::print_new_line();
  }
}