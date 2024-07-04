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
  bool inc_frq = frq_inc_btn_->is_short_press();
  bool dec_frq = frq_dec_btn_->is_short_press();
  bool inc_red = red_inc_btn_->is_short_press();
  bool dec_red = red_dec_btn_->is_short_press();
  bool inc_grn = grn_inc_btn_->is_short_press();
  bool dec_grn = grn_dec_btn_->is_short_press();
  bool inc_blu = blu_inc_btn_->is_short_press();
  bool dec_blu = blu_dec_btn_->is_short_press(); 

  if(
    inc_red  ||
    dec_red  ||
    inc_grn  ||
    dec_grn  ||
    inc_blu  ||
    dec_blu
  )
  {
    Debug::print_string_with_new_line("\n_________________________");
    Debug::print_string_with_new_line("BEFORE MOD");
    Debug::print_new_line();
    clock_->print();
    Debug::print_new_line();
  }

  //____________________________________________________________________________
  // Frequency is multiplicative inverse of cycle time, i.e.
  // frequency increase = cycle time decrease
  // frequency decrease = cycle time increase
  //____________________________________________________________________________
  if (dec_frq)
  {
    Serial.println("frq_dec pressed");
    clock_->mod_cycle_time(RgbColor::IncDec::INC);
  }

  if (inc_frq)
  {
    Serial.println("frq_inc pressed");
    clock_->mod_cycle_time(RgbColor::IncDec::DECREMENT);
  }

  if (dec_red)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("red_dec pressed");
    clock_->mod_color_selection(Rgb::RED, RgbColor::IncDec::DECREMENT);
  }

  if (inc_red)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("red_inc pressed");
    clock_->mod_color_selection(Rgb::RED, RgbColor::IncDec::INC);
  }

  if (dec_grn)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("grn_dec pressed");
    clock_->mod_color_selection(Rgb::GRN, RgbColor::IncDec::DECREMENT);
  }

  if (inc_grn)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("grn_inc pressed");
    clock_->mod_color_selection(Rgb::GRN, RgbColor::IncDec::INC);
  }

  if (dec_blu)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("blu_dec pressed");
    clock_->mod_color_selection(Rgb::BLU, RgbColor::IncDec::DECREMENT);
  }

  if (inc_blu)
  {
    Debug::print_string_with_new_line("\n_________________________");
    Serial.println("blu_inc pressed");
    clock_->mod_color_selection(Rgb::BLU, RgbColor::IncDec::INC);
  }

  if(
    inc_red  ||
    dec_red  ||
    inc_grn  ||
    dec_grn  ||
    inc_blu  ||
    dec_blu
  )
  {
    //Debug::print_string_with_new_line("\n_________________________");
    //Debug::print_string_with_new_line("AFTER MOD");
    //Debug::print_new_line();
    //Debug::print_string_with_new_line((char*)("_________________________"));
    //Debug::print_string_with_new_line((char*)(" Current Color Selection "));
    //Debug::print_string_with_new_line((char*)("_________________________"));
    //Debug::print_color_array(clock_->crnt_color_selection_);
    //Debug::print_new_line();
  }
}