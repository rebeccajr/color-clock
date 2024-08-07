//______________________________________________________________________________
// DESCRIPTION
// This class contains control logic for the time.
//______________________________________________________________________________

#ifndef TOP_LEVEL
#define TOP_LEVEL

#include <Adafruit_AW9523.h>
#include <Wire.h>

#include "color-clock.hpp"
#include "flux-macros.hpp"
#include "hsv-color.hpp"
#include "momentary-switch.hpp"
#include "participant-ctrl.hpp"
#include "rgb-color.hpp"
#include "time-controller.hpp"
#include "time-display.hpp"



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

    //__________________________________________________________________________
    // Time controller buttons
    //__________________________________________________________________________
    TimeController time_ctrl_;

    MomentarySwitch enter_btn_;
    MomentarySwitch inc_btn_;
    MomentarySwitch dec_btn_;
    //__________________________________________________________________________

    //__________________________________________________________________________
    // Participant control
    //__________________________________________________________________________
    ParticipantCtrl participant_intfc_;

    MomentarySwitch frq_inc_btn_;
    MomentarySwitch red_inc_btn_;
    MomentarySwitch grn_inc_btn_;
    MomentarySwitch blu_inc_btn_;
    MomentarySwitch frq_dec_btn_;
    MomentarySwitch red_dec_btn_;
    MomentarySwitch grn_dec_btn_;
    MomentarySwitch blu_dec_btn_;
    //__________________________________________________________________________

    State state_;

    std::map <ColorClock*, pin_map> cc_out_pin_map_;

  public:

    TopLevel(){}

    TopLevel(FluxClock* the_clock
      , TimeDisplay* time_disp
      , MomentarySwitch inc_btn
      , MomentarySwitch dec_btn
      , MomentarySwitch enter_btn
      , Adafruit_AW9523* aw
      , MomentarySwitch frq_inc_btn
      , MomentarySwitch red_inc_btn
      , MomentarySwitch grn_inc_btn
      , MomentarySwitch blu_inc_btn
      , MomentarySwitch frq_dec_btn
      , MomentarySwitch red_dec_btn
      , MomentarySwitch grn_dec_btn
      , MomentarySwitch blu_dec_btn
      )
      : clock_(the_clock)
      , inc_btn_(inc_btn)
      , dec_btn_(dec_btn)
      , enter_btn_(enter_btn)
      , time_ctrl_(TimeController(the_clock
        , inc_btn
        , dec_btn
        , enter_btn
        , time_disp))
      , frq_inc_btn_(frq_inc_btn)
      , red_inc_btn_(red_inc_btn)
      , grn_inc_btn_(grn_inc_btn)
      , blu_inc_btn_(blu_inc_btn)
      , frq_dec_btn_(frq_dec_btn)
      , red_dec_btn_(red_dec_btn)
      , grn_dec_btn_(grn_dec_btn)
      , blu_dec_btn_(blu_dec_btn)
      , state_(State::IDLE)
      {}

    void run();

    MomentarySwitch get_inc_btn(){ return inc_btn_;}
    MomentarySwitch get_dec_btn(){ return dec_btn_;}
    MomentarySwitch get_enter_btn(){ return enter_btn_;}

    void set_participant_ctrl(ColorClock*);
    void register_color_clock(ColorClock*, short, short, short);
};

#endif //TIME_CONTROLLER