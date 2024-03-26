//______________________________________________________________________________
// DESCRIPTION
// This class contains control logic for the time.
//______________________________________________________________________________

#ifndef TIME_CONTROLLER
#define TIME_CONTROLLER

#include <DS3231.h>

#include "time-display.hpp"
#include "momentary-switch.hpp"


//______________________________________________________________________________
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
    DS3231*         rtc_;
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

    TimeController(DS3231* rtc
      , MomentarySwitch inc_btn
      , MomentarySwitch dec_btn
      , MomentarySwitch enter_btn
      , TimeDisplay* display
      )
      : rtc_(rtc)
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