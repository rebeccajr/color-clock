//______________________________________________________________________________
// Class that controls a ColorClock object through a control panel of buttons.
//______________________________________________________________________________

#ifndef PARTICIPANT_CTRL
#define PARTICIPANT_CTRL

#include "flux-macros.hpp"
#include "debug.hpp"

#include "color-clock.hpp"
#include "momentary-switch.hpp"

class ParticipantCtrl
{
 public:
  ColorClock* clock_;

  MomentarySwitch* frq_inc_btn_;
  MomentarySwitch* red_inc_btn_;
  MomentarySwitch* grn_inc_btn_;
  MomentarySwitch* blu_inc_btn_;
  MomentarySwitch* frq_dec_btn_;
  MomentarySwitch* red_dec_btn_;
  MomentarySwitch* grn_dec_btn_;
  MomentarySwitch* blu_dec_btn_;

  ParticipantCtrl(){};

  ParticipantCtrl(ColorClock* cc
    , MomentarySwitch* frq_inc_btn
    , MomentarySwitch* red_inc_btn
    , MomentarySwitch* grn_inc_btn
    , MomentarySwitch* blu_inc_btn
    , MomentarySwitch* frq_dec_btn
    , MomentarySwitch* red_dec_btn
    , MomentarySwitch* grn_dec_btn
    , MomentarySwitch* blu_dec_btn
  ) : clock_(cc)
    , frq_inc_btn_(frq_inc_btn)
    , red_inc_btn_(red_inc_btn)
    , grn_inc_btn_(grn_inc_btn)
    , blu_inc_btn_(blu_inc_btn)
    , frq_dec_btn_(frq_dec_btn)
    , red_dec_btn_(red_dec_btn)
    , grn_dec_btn_(grn_dec_btn)
    , blu_dec_btn_(blu_dec_btn)
    {}

  void run();
};

#endif