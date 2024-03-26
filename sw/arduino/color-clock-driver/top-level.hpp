//______________________________________________________________________________
// DESCRIPTION
// This class contains control logic for the time.
//______________________________________________________________________________

#ifndef TOP_LEVEL
#define TOP_LEVEL

#include <DS3231.h>

#include "color-clock.hpp"
#include "time-controller.hpp"
#include "time-display.hpp"
#include "momentary-switch.hpp"


//______________________________________________________________________________
class TopLevel
{
  public:
    enum class State
    { IDLE
      , SET_TIME
      , USR_CTRL
    };

  private:
    DS3231* rtc_;

    MomentarySwitch enter_btn_;
    MomentarySwitch inc_btn_;
    MomentarySwitch dec_btn_;

    ColorClock color_clock0_;
    ColorClock color_clock1_;
    ColorClock color_clock2_;

    int cc0_freq_;
    int cc1_freq_;
    int cc2_freq_;

    TimeController time_ctrl_;

    State state_;

  public:

    TopLevel(){}

    TopLevel(DS3231* rtc
      , MomentarySwitch inc_btn
      , MomentarySwitch dec_btn
      , MomentarySwitch enter_btn
      , TimeDisplay* time_disp
      , float cc0_freq
      , float cc1_freq
      , float cc2_freq
      )
      : rtc_(rtc)
      , inc_btn_(inc_btn)
      , dec_btn_(dec_btn)
      , enter_btn_(enter_btn)
      , time_ctrl_(TimeController(rtc, inc_btn, dec_btn, enter_btn, time_disp))
      , color_clock0_(ColorClock(rtc, cc0_freq))
      , color_clock1_(ColorClock(rtc, cc1_freq))
      , color_clock2_(ColorClock(rtc, cc2_freq))
      , state_(State::IDLE)
      {}

    void run();

    MomentarySwitch get_inc_btn(){ return inc_btn_;}
    MomentarySwitch get_dec_btn(){ return dec_btn_;}
    MomentarySwitch get_enter_btn(){ return enter_btn_;}

};

#endif //TIME_CONTROLLER