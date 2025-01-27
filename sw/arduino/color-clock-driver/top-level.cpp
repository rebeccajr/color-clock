//______________________________________________________________________
//______________________________________________________________________
//      _   __   _   _ _   _   _   _         _
// |   |_| | _  | | | V | | | | / |_/ |_| | /
// |__ | | |__| |_| |   | |_| | \ |   | | | \_
//  _  _         _ ___  _       _ ___   _                        / /
// /  | | |\ |  \   |  | / | | /   |   \                        (^^)
// \_ |_| | \| _/   |  | \ |_| \_  |  _/                        (____)o
//______________________________________________________________________
//______________________________________________________________________
//
//----------------------------------------------------------------------
// Copyright 2024, Rebecca Rashkin
// -------------------------------
// This code may be copied, redistributed, transformed, or built upon in
// any format for educational, non-commercial purposes.
//
// Please give me appropriate credit should you choose to use this
// resource. Thank you :)
//----------------------------------------------------------------------
//
//______________________________________________________________________
// //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\
//______________________________________________________________________
//______________________________________________________________________
// Implementation of TopLevel functions
//______________________________________________________________________
#include "debug.hpp"
#include "top-level.hpp"
#include "momentary-switch.hpp"

//______________________________________________________________________
// State machine to run color clocks and set time
//______________________________________________________________________
void TopLevel::run()
{
  participant_intfc_.run();

  std::map<ColorClock*, pin_map>::iterator it;
  for (it = cc_out_pin_map_.begin(); it != cc_out_pin_map_.end(); it++)
  {
    RgbColor out_color = it->first->time_to_color();
    short r_pin = it->second[RgbColor::PriColor::RED];
    short g_pin = it->second[RgbColor::PriColor::GRN];
    short b_pin = it->second[RgbColor::PriColor::BLU];

    // These LEDs are common anode - boolean here sends the inverted
    // values to analog pins, e.g. full on = 0 instead of 255
    out_color.write_rgb_to_out(r_pin, g_pin, b_pin, true);
    //out_color.write_rgb_to_out(r_pin, g_pin, b_pin, false);
    //__________________________________________________________________
    // Debug
    //__________________________________________________________________
    /*
    static short prev_sec = 0;
    short crnt_sec = it->first->clock_->get_sec();
    if (prev_sec != crnt_sec)
    {
      Serial.println(it->first->cycle_time_in_hrs_);
      Debug::print_time(it->first->clock_->rtc_);
      Debug::print_color(out_color);
      prev_sec = crnt_sec;
    }
    */
    //__________________________________________________________________

  }

  switch(state_)
  {
    //__________________________________________________________________
    case(State::IDLE):
      //________________________________________________________________
      // DEBUG
      //________________________________________________________________
      //Debug::print_str_with_new_line("TopLevel::run IDLE");
      //________________________________________________________________

      //time_ctrl_.get_display()->write_disp_str("FLUX");
      time_ctrl_.get_display()->write_disp_sec(clock_->get_sec());


      if (enter_btn_.is_short_press())
        state_ = State::SET_TIME;

      break;

    //__________________________________________________________________
    case(State::SET_TIME):
      //________________________________________________________________
      // DEBUG
      //________________________________________________________________
      //Debug::print_str_with_new_line("TopLevel::run SET_TIME");
      //________________________________________________________________

      time_ctrl_.set_time();
      if (time_ctrl_.get_state() == TimeController::State::DONE)
        state_ = State::IDLE;

      break;

    default:
      break;
  }

  return;
}


//______________________________________________________________________
// Add ColorClock object and RGB pins to map
//______________________________________________________________________
void TopLevel::register_color_clock(ColorClock* color_clock
  , short r_pin
  , short g_pin
  , short b_pin)
{

  cc_out_pin_map_.insert({
    color_clock, RgbColor::create_rgb_pin_map(r_pin, g_pin, b_pin)
  });
}


//______________________________________________________________________
// Register participant controlled clock
//______________________________________________________________________
void TopLevel::set_participant_ctrl(ColorClock* cc)
{
  participant_intfc_ = ParticipantCtrl(cc
    , &frq_inc_btn_
    , &red_inc_btn_
    , &grn_inc_btn_
    , &blu_inc_btn_
    , &frq_dec_btn_
    , &red_dec_btn_
    , &grn_dec_btn_
    , &blu_dec_btn_
  );
}