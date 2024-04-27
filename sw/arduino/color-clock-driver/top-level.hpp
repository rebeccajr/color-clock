//______________________________________________________________________________
// DESCRIPTION
// This class contains control logic for the time.
//______________________________________________________________________________

#ifndef TOP_LEVEL
#define TOP_LEVEL

#include<Wire.h>

#include "color-classes.hpp"
#include "color-clock.hpp"
#include "time-controller.hpp"
#include "time-display.hpp"
#include "momentary-switch.hpp"


//______________________________________________________________________________
class TopLevel
{
  public:
    using pin_map = std::map <RgbColor::PriColor, short>;

    enum class State
    { IDLE
      , SET_TIME
      , USR_CTRL
    };

  private:
    FluxClock* clock_;

    MomentarySwitch enter_btn_;
    MomentarySwitch inc_btn_;
    MomentarySwitch dec_btn_;

    TimeController time_ctrl_;

    State state_;

    std::map <ColorClock*, pin_map> cc_out_pin_map_;

  public:

    TopLevel(){}

    TopLevel(FluxClock* the_clock
      , MomentarySwitch inc_btn
      , MomentarySwitch dec_btn
      , MomentarySwitch enter_btn
      , TimeDisplay* time_disp
      )
      : clock_(the_clock)
      , inc_btn_(inc_btn)
      , dec_btn_(dec_btn)
      , enter_btn_(enter_btn)
      , time_ctrl_(TimeController(the_clock, inc_btn, dec_btn, enter_btn, time_disp))
      , state_(State::IDLE)
      {}

    void run();

    MomentarySwitch get_inc_btn(){ return inc_btn_;}
    MomentarySwitch get_dec_btn(){ return dec_btn_;}
    MomentarySwitch get_enter_btn(){ return enter_btn_;}

    void register_color_clock(ColorClock*, short, short, short);

};

#endif //TIME_CONTROLLER