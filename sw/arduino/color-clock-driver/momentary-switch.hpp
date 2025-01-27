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
// This class contains logic necessary for momentary switch input.
//______________________________________________________________________
#ifndef MOMENTARY_SWITCH
#define MOMENTARY_SWITCH

#include <Arduino.h>
#include "flux-macros.hpp"

#ifdef USING_AW9523
# include <Adafruit_AW9523.h>
#endif

#include "debug.hpp"


//______________________________________________________________________
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

#ifdef USING_AW9523
    Adafruit_AW9523* aw_;
#endif


    int on_value_;
    int reading_;

    int settle_time_in_ms_;
    int long_hold_time_in_ms_;
    int short_hold_time_in_ms_;
    int mult_input_time_gap_;

    // TODO rename for better description
    int sw_state_;
    int prev_state_;

    SwitchState sw_state_type_;

    int prev_debounced_input_;
    int multi_input_count_;

    unsigned long prev_ms_;
    unsigned long on_time_ms_;
    unsigned long release_time_ms_;
    unsigned long time_since_off_;


  public:
    MomentarySwitch(){}

    MomentarySwitch(int input_pin
#ifdef USING_AW9523
      , Adafruit_AW9523* aw
#endif
      , int settle_time_in_ms         = 50
      , int short_hold_time_in_ms     = 50
      , int long_hold_time_in_ms      = 1000
      , int mult_input_time_gap       = 500
      , int on_value                  = 1
     )
      : input_pin_(input_pin)
#ifdef USING_AW9523
      , aw_(aw)
#endif
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
    bool is_short_press();
};

#endif //MOMENTARY_SWITCH
