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
// Implementation for functions of base class
//______________________________________________________________________
#include "momentary-switch.hpp"
#include <Arduino.h>

//______________________________________________________________________
// Registers input after settle time
//______________________________________________________________________
int MomentarySwitch::debounce_input(){
  unsigned long crnt_ms = millis();

  reading_ =
#ifdef USING_AW9523
  aw_->
#endif
  digitalRead(input_pin_);

  if (reading_ != prev_state_)
    prev_ms_ = crnt_ms;

  unsigned long elapsed_time = crnt_ms - prev_ms_;

  if (elapsed_time > settle_time_in_ms_ && reading_ != sw_state_)
      sw_state_ = reading_;

  prev_state_ = reading_;

  return sw_state_;
}


//______________________________________________________________________
// Registers input type after debounce
//______________________________________________________________________
MomentarySwitch::InputType MomentarySwitch::get_input_type()
{
  //____________________________________________________________________
  // DEBUG
  //Debug::print_labeled_int("get_input_type input pin: ", input_pin_);
  //____________________________________________________________________

  unsigned long crnt_ms = millis();
  unsigned long hold_time;
  int input = debounce_input();

  switch (sw_state_type_)
  {
    //__________________________________________________________________
    case SwitchState::IDLE:
      //________________________________________________________________
      // DEBUG
      //Debug::print_labeled_int("get_input_type input pin: "
      //  , input_pin_);
      //Debug::print_str_with_new_line("get_input_type State::IDLE");
      //________________________________________________________________

      // Reset values use for input type determination
      multi_input_count_ = 0;
      on_time_ms_ = 0;
      release_time_ms_ = 0;

      if (input == on_value_)
        sw_state_type_ = SwitchState::PRESS;

      break;

    //__________________________________________________________________
    case SwitchState::PRESS:

      //________________________________________________________________
      // DEBUG
      //Debug::print_labeled_int("pin: ", input_pin_);
      //Debug::print_new_line();
      //Debug::print_str_with_new_line("PRESS");
      //Debug::print_new_line();
      //________________________________________________________________

      // Set time of switch on
      on_time_ms_ = crnt_ms;
      multi_input_count_++;
      sw_state_type_ = SwitchState::HOLD;

      break;

    //__________________________________________________________________
    case SwitchState::HOLD:
      // Check if switch was released
      if (input != on_value_)
        sw_state_type_ = SwitchState::RELEASE;
      break;

    //__________________________________________________________________
    case SwitchState::RELEASE:
      //________________________________________________________________
      // DEBUG
      //________________________________________________________________
      //Debug::print_labeled_int("pin: ", input_pin_);
      //Debug::print_new_line();
      //Debug::print_str_with_new_line("RELEASE");
      //________________________________________________________________

      // Set time of switch release
      release_time_ms_ = crnt_ms;
      hold_time = release_time_ms_ - on_time_ms_;

      // Check if over long hold threshold
      if (hold_time > long_hold_time_in_ms_ && multi_input_count_ == 1)
      {
        //______________________________________________________________
        // DEBUG
        //______________________________________________________________
        //Debug::print_str_with_new_line(
        //  "MomentarySwitch::get_input_type -- long press");
        //______________________________________________________________
        sw_state_type_ = SwitchState::IDLE;
        return InputType::LONG;
      }

      sw_state_type_ = SwitchState::WAIT;
      break;

    //__________________________________________________________________
    case SwitchState::WAIT:
    {
      unsigned long time_since_off_ = crnt_ms - release_time_ms_;

      if (time_since_off_ < mult_input_time_gap_)
      {
        // Transition to next state if button is pressed
        if (input == on_value_)
        {
         sw_state_type_ = SwitchState::PRESS;
         return InputType::NONE;
        }
      }

      else
      {
        //______________________________________________________________
        // DEBUG
        //______________________________________________________________
        //Debug::print_labeled_int("multi input:         "
        //  , multi_input_count_);
        //______________________________________________________________

        sw_state_type_ = SwitchState::IDLE;

        return static_cast<InputType>(
          static_cast<int>(InputType::SHORT) + multi_input_count_ - 1);
        }

      break;

      }

    //__________________________________________________________________
    default:
      break;
    }

  return InputType::NONE;
}

//______________________________________________________________________
bool MomentarySwitch::is_short_press()
{
  //____________________________________________________________________
  // DEBUG
  //Debug::print_labeled_int("is_short_press pin: ", input_pin_);
  //____________________________________________________________________

  unsigned long crnt_ms = millis();
  unsigned long hold_time;
  int input = debounce_input();

  switch (sw_state_type_)
  {
    //__________________________________________________________________
    case SwitchState::IDLE:
      //________________________________________________________________
      // DEBUG
      //________________________________________________________________
      //Debug::print_labeled_int("get_input_type input pin: "
      //  ,input_pin_);
      //Debug::print_str_with_new_line("get_input_type State::IDLE");
      //________________________________________________________________

      // Reset values use for input type determination
      on_time_ms_ = 0;
      release_time_ms_ = 0;

      if (input == on_value_)
        sw_state_type_ = SwitchState::PRESS;

      break;

    //__________________________________________________________________
    case SwitchState::PRESS:

      //________________________________________________________________
      // DEBUG
      //________________________________________________________________
      //Debug::print_labeled_int("pin: ", input_pin_);
      //Debug::print_new_line();
      //Debug::print_str_with_new_line("PRESS");
      //Debug::print_new_line();
      //________________________________________________________________

      // Set time of switch on
      on_time_ms_ = crnt_ms;
      multi_input_count_++;
      sw_state_type_ = SwitchState::HOLD;

      break;

    //__________________________________________________________________
    case SwitchState::HOLD:
      // Check if switch was released
      if (input != on_value_)
        sw_state_type_ = SwitchState::RELEASE;
      break;

    //__________________________________________________________________
    case SwitchState::RELEASE:
      //________________________________________________________________
      // DEBUG
      //________________________________________________________________
      //Debug::print_labeled_int("pin: ", input_pin_);
      //Debug::print_new_line();
      //Debug::print_str_with_new_line("RELEASE");
      //________________________________________________________________

      // Set time of switch release
      release_time_ms_ = crnt_ms;
      hold_time = release_time_ms_ - on_time_ms_;

      // Check if over long hold threshold
      if (hold_time > short_hold_time_in_ms_)
      {
        //______________________________________________________________
        // DEBUG
        //______________________________________________________________
        //Debug::print_str_with_new_line(
        //  "MomentarySwitch::is_short_press -- "
        //  "hold_time > short_hold_time_in_ms");
        //______________________________________________________________
        sw_state_type_ = SwitchState::IDLE;
        return true;
      }

      break;

    //__________________________________________________________________
    default:
      break;
    }

  return false;
}

