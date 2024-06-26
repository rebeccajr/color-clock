
//______________________________________________________________________________
// DESCRIPTION
// This class contains logic necessary for momentary switch input.
//______________________________________________________________________________
#ifndef MOMENTARY_SWITCH
#define MOMENTARY_SWITCH

#include <Arduino.h>

#include "debug.hpp"


//______________________________________________________________________________
class MomentarySwitch{

  public:
    enum class InputType
    { NONE
      , LONG
      , SHORT
      , DOUBLE
      , TRIPLE
    };

    enum class SwitchState
    { IDLE
      , PRESS
      , HOLD
      , RELEASE
      , WAIT
    };

  private:
    int input_pin_;
    int reading_;
    int settle_time_in_ms_;
    int long_hold_time_in_ms_;
    int short_hold_time_in_ms_;
    int mult_input_time_gap_;
    int sw_state_;
    int prev_state_;
    SwitchState sw_state_type_;
    int prev_debounced_input_;
    int multi_input_count_;
    unsigned long prev_ms_;
    unsigned long on_time_ms_;
    unsigned long release_time_ms_;
    unsigned long time_since_off_;
    int on_value_;

  public:
    MomentarySwitch(){}

    MomentarySwitch(int input_pin
      , int settle_time_in_ms         = 50
      , int long_hold_time_in_ms      = 1000
      , int short_hold_time_in_ms     = 50
      , int mult_input_time_gap       = 500
      , int on_value                  = 1
     )
      : input_pin_(input_pin)
      , settle_time_in_ms_(settle_time_in_ms)
      , long_hold_time_in_ms_(long_hold_time_in_ms)
      , short_hold_time_in_ms_(short_hold_time_in_ms)
      , mult_input_time_gap_(mult_input_time_gap)
      , on_value_(on_value)
      {

        prev_debounced_input_ = 0;
        multi_input_count_    = 0;
        sw_state_             = 0;
        prev_state_           = 1;
        prev_ms_              = 0;
        time_since_off_       = 0;
        on_time_ms_           = 0;
        release_time_ms_      = 0;
        time_since_off_       = 0;
      }

    int debounce_input();

    int get_pin(){      return input_pin_;}
    int get_reading(){  return reading_;}

    InputType get_input_type();
};

#endif //MOMENTARY_SWITCH
