
//------------------------------------------------------------------------------
// DESCRIPTION
// This class contains logic necessary for momentary switch input.
//------------------------------------------------------------------------------
#ifndef MOMENTARY_SWITCH
#define MOMENTARY_SWITCH

#include <Arduino.h>


//------------------------------------------------------------------------------
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
      , int settle_time_in_ms_ = 50
      , int long_hold_time_in_ms_ = 1000
      , int short_hold_time_in_ms_ = 50
      , int mult_input_time_gap_ = 500
      , int sw_state_ = 0
      , int prev_state_ = 1
      , InputType input_type_ = InputType::NONE
      , int prev_debounced_input_= 0
      , int multi_input_count_ = 0
      , int prev_ms_ = 0
      , unsigned long time_since_off_ = 0
      , int on_value_ = 1
     )
      : input_pin_(input_pin_)
      , settle_time_in_ms_(settle_time_in_ms_)
      , long_hold_time_in_ms_(long_hold_time_in_ms_)
      , short_hold_time_in_ms_(short_hold_time_in_ms_)
      , mult_input_time_gap_(mult_input_time_gap_)
      , sw_state_(sw_state_)
      , on_value_(on_value_)
      {}

    int get_on_val(){ return on_value_;}
    int debounce_input(int reading);
    InputType get_input_type(int reading);
    SwitchState determine_switch_state(int reading);
    InputType off_logic(unsigned long hold_time, unsigned long crnt_ms);
};

#endif
