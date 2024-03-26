//______________________________________________________________________________
// Implementation of TopLevel functions
//______________________________________________________________________________
#include "top-level.hpp"
#include "momentary-switch.hpp"

//______________________________________________________________________________
// State machine to run color clocks and set time
//______________________________________________________________________________
void TopLevel::run()
{
  switch(state_)
  {
    //__________________________________________________________________________
    case(State::IDLE):
      //________________________________________________________________________
      // DEBUG
      //Serial.println("TopLevel::run IDLE");
      //________________________________________________________________________

      time_ctrl_.get_display()->write_disp_str("USER");

      if (enter_btn_.get_input_type() == MomentarySwitch::InputType::LONG)
        state_ = State::SET_TIME;

      break;

    //__________________________________________________________________________
    case(State::SET_TIME):
      //________________________________________________________________________
      // DEBUG
      //Serial.println("TopLevel::run SET_TIME");
      //________________________________________________________________________
      time_ctrl_.set_time();
      if (time_ctrl_.get_state() == TimeController::State::DONE)
        state_ = State::IDLE;

      break;

    default:
      break;
  }

  return;
}
