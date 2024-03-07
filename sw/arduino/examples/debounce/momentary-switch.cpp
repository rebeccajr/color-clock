//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

#include "momentary-switch.hpp"
#include <Arduino.h>

//______________________________________________________________________________
// Registers input after settle time
//______________________________________________________________________________
int MomentarySwitch::debounce_input(int reading){
  unsigned long crnt_ms = millis();

  if (reading != prev_state_)
    prev_ms_ = crnt_ms;

  unsigned long elapsed_time = crnt_ms - prev_ms_;

  if (elapsed_time > settle_time_in_ms_ && reading != sw_state_)
      sw_state_ = reading;

  prev_state_ = reading;

  return sw_state_;
}


//______________________________________________________________________________
// Registers input type after debounce
//______________________________________________________________________________
MomentarySwitch::InputType MomentarySwitch::get_input_type(int reading)
{
  unsigned long crnt_ms = millis();
  unsigned long hold_time;
  int input = debounce_input(reading);

  switch (sw_state_type_)
  {
    //__________________________________________________________________________
    case SwitchState::IDLE:

      // Reset values use for input type determination
      multi_input_count_ = 0;
      on_time_ms_ = 0;
      release_time_ms_ = 0;

      // Transition to next state if button is pressed
      if (input == on_value_)
        sw_state_type_ = SwitchState::PRESS;

      break;

    //__________________________________________________________________________
    case SwitchState::PRESS:
      // Set time of switch on
      on_time_ms_ = crnt_ms;
      multi_input_count_++;
      sw_state_type_ = SwitchState::HOLD;

      Serial.println("PRESS");
      Serial.println("increment");
      break;

    //__________________________________________________________________________
    case SwitchState::HOLD:
      // Check if switch was released
      if (input != on_value_)
        sw_state_type_ = SwitchState::RELEASE;
      break;

    //__________________________________________________________________________
    case SwitchState::RELEASE:
      Serial.println("RELEASE");

      // Set time of switch release
      release_time_ms_ = crnt_ms;
      hold_time = release_time_ms_ - on_time_ms_;

      // Check if over long hold threshold
      if (hold_time > long_hold_time_in_ms_ && multi_input_count_ == 1)
      {
        Serial.println("long");
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
        Serial.print("multi input:         ");
        Serial.println(multi_input_count_);

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
