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
// DESCRIPTION
// This class contains control logic for the time.
//______________________________________________________________________

#ifndef TIME_CONTROLLER
#define TIME_CONTROLLER

#include "debug.hpp"
#include "flux-clock.hpp"
#include "time-display.hpp"
#include "momentary-switch.hpp"


//______________________________________________________________________
class TimeController
{
  public:
    enum class State
    { IDLE
      , SET_YR
      , SET_MO
      , SET_DATE
      , SET_HR
      , SET_MIN
      , DONE
    };

  private:
    FluxClock*      clock_;
    TimeDisplay*    display_;
    MomentarySwitch inc_btn_;
    MomentarySwitch dec_btn_;
    MomentarySwitch enter_btn_;
    State           state_;

  public:

    void inc_yr();
    void dec_yr();
    void inc_mo();
    void dec_mo();
    void inc_day();
    void dec_day();
    void inc_hr();
    void dec_hr();
    void inc_min();
    void dec_min();

    void set_time();
    void set_next_state();

    TimeController(){}

    TimeController(FluxClock* clock
      , MomentarySwitch inc_btn
      , MomentarySwitch dec_btn
      , MomentarySwitch enter_btn
      , TimeDisplay* display
      )
      : clock_(clock)
      , inc_btn_(inc_btn)
      , dec_btn_(dec_btn)
      , enter_btn_(enter_btn)
      , display_(display)
      {
        state_ = State::IDLE;
      }

      MomentarySwitch get_inc_btn(){ return inc_btn_;}
      MomentarySwitch get_dec_btn(){ return dec_btn_;}
      MomentarySwitch get_enter_btn(){ return enter_btn_;}
      TimeDisplay* get_display(){ return display_;}
      State get_state(){ return state_;}
};

#endif //TIME_CONTROLLER