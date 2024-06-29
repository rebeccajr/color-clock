//______________________________________________________________________________
// Implementation for functions of base class
//______________________________________________________________________________
#include "momentary-switch.hpp"
#include <Arduino.h>

//______________________________________________________________________________
// Registers input after settle time
//______________________________________________________________________________
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


//______________________________________________________________________________
// Registers input type after debounce
//______________________________________________________________________________
MomentarySwitch::InputType MomentarySwitch::get_input_type()
{
  //____________________________________________________________________________
  // DEBUG
  //Debug::print_labeled_int("get_input_type input pin: ", input_pin_);
  //____________________________________________________________________________

  unsigned long crnt_ms = millis();
  unsigned long hold_time;
  int input = debounce_input();

  switch (sw_state_type_)
  {
    //__________________________________________________________________________
    case SwitchState::IDLE:
      //________________________________________________________________________
      // DEBUG
      //Debug::print_labeled_int("get_input_type input pin: ",input_pin_);
      //Debug::print_string_with_new_line("get_input_type State::IDLE");
      //________________________________________________________________________

      // Reset values use for input type determination
      multi_input_count_ = 0;
      on_time_ms_ = 0;
      release_time_ms_ = 0;

      if (input == on_value_)
        sw_state_type_ = SwitchState::PRESS;

      break;

    //__________________________________________________________________________
    case SwitchState::PRESS:

      //________________________________________________________________________
      // DEBUG
      //Debug::print_labeled_int("pin: ", input_pin_);
      //Debug::print_new_line();
      //Debug::print_string_with_new_line("PRESS");
      //Debug::print_new_line();
      //________________________________________________________________________

      // Set time of switch on
      on_time_ms_ = crnt_ms;
      multi_input_count_++;
      sw_state_type_ = SwitchState::HOLD;

      break;

    //__________________________________________________________________________
    case SwitchState::HOLD:
      // Check if switch was released
      if (input != on_value_)
        sw_state_type_ = SwitchState::RELEASE;
      break;

    //__________________________________________________________________________
    case SwitchState::RELEASE:
      //________________________________________________________________________
      // DEBUG
      //Debug::print_labeled_int("pin: ", input_pin_);
      //Debug::print_new_line();
      //Debug::print_string_with_new_line("RELEASE");
      //________________________________________________________________________

      // Set time of switch release
      release_time_ms_ = crnt_ms;
      hold_time = release_time_ms_ - on_time_ms_;

      // Check if over long hold threshold
      if (hold_time > long_hold_time_in_ms_ && multi_input_count_ == 1)
      {
        //______________________________________________________________________
        // DEBUG
        //Debug::print_string_with_new_line(
        //  "MomentarySwitch::get_input_type -- long press");
        //______________________________________________________________________
        sw_state_type_ = SwitchState::IDLE;
        return InputType::LONG;
      }

      sw_state_type_ = SwitchState::WAIT;
      break;

    //__________________________________________________________________________
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
        //______________________________________________________________________
        // DEBUG
        //Debug::print_labeled_int("multi input:         ", multi_input_count_);
        //______________________________________________________________________

        sw_state_type_ = SwitchState::IDLE;

        return static_cast<InputType>(
          static_cast<int>(InputType::SHORT) + multi_input_count_ - 1);
        }

      break;

      }

    //__________________________________________________________________________
    default:
      break;
    }

  return InputType::NONE;
}

//______________________________________________________________________________
bool MomentarySwitch::is_short_press()
{
  //____________________________________________________________________________
  // DEBUG
  //Debug::print_labeled_int("is_short_press pin: ", input_pin_);
  //____________________________________________________________________________

  unsigned long crnt_ms = millis();
  unsigned long hold_time;
  int input = debounce_input();

  switch (sw_state_type_)
  {
    //__________________________________________________________________________
    case SwitchState::IDLE:
      //________________________________________________________________________
      // DEBUG
      //Debug::print_labeled_int("get_input_type input pin: ",input_pin_);
      //Debug::print_string_with_new_line("get_input_type State::IDLE");
      //________________________________________________________________________

      // Reset values use for input type determination
      on_time_ms_ = 0;
      release_time_ms_ = 0;

      if (input == on_value_)
        sw_state_type_ = SwitchState::PRESS;

      break;

    //__________________________________________________________________________
    case SwitchState::PRESS:

      //________________________________________________________________________
      // DEBUG
      //Debug::print_labeled_int("pin: ", input_pin_);
      //Debug::print_new_line();
      //Debug::print_string_with_new_line("PRESS");
      //Debug::print_new_line();
      //________________________________________________________________________

      // Set time of switch on
      on_time_ms_ = crnt_ms;
      multi_input_count_++;
      sw_state_type_ = SwitchState::HOLD;

      break;

    //__________________________________________________________________________
    case SwitchState::HOLD:
      // Check if switch was released
      if (input != on_value_)
        sw_state_type_ = SwitchState::RELEASE;
      break;

    //__________________________________________________________________________
    case SwitchState::RELEASE:
      //________________________________________________________________________
      // DEBUG
      //Debug::print_labeled_int("pin: ", input_pin_);
      //Debug::print_new_line();
      //Debug::print_string_with_new_line("RELEASE");
      //________________________________________________________________________

      // Set time of switch release
      release_time_ms_ = crnt_ms;
      hold_time = release_time_ms_ - on_time_ms_;

      // Check if over long hold threshold
      if (hold_time > short_hold_time_in_ms_)
      {
        //______________________________________________________________________
        // DEBUG
        //Debug::print_string_with_new_line(
        //  "MomentarySwitch::is_short_press -- hold_time > short_hold_time_in_ms");
        //______________________________________________________________________
        sw_state_type_ = SwitchState::IDLE;
        return true;
      }

      break;

    //__________________________________________________________________________
    default:
      break;
    }

  return false;
}

