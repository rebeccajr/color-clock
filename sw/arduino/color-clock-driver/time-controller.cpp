
//______________________________________________________________________________
// DESCRIPTION
// This class contains control logic for the time.
//______________________________________________________________________________

#include "time-controller.hpp"

void TimeController::inc_yr()  { clock_->set_yr(clock_->get_yr()    + 1); }
void TimeController::inc_day() { clock_->set_day (clock_->get_day() + 1); }
void TimeController::inc_min() { clock_->set_min(clock_->get_min()  + 1); }

void TimeController::dec_yr()  { clock_->set_yr(clock_->get_yr()    - 1); }
void TimeController::dec_day() { clock_->set_day(clock_->get_day()  - 1); }
void TimeController::dec_min() { clock_->set_min(clock_->get_min()  - 1); }



//______________________________________________________________________________
// State machine for time set
//______________________________________________________________________________
void TimeController::set_time()
{
  bool state_changed = false;

  int inc_reading   = inc_btn_.get_reading();
  int dec_reading   = dec_btn_.get_reading();
  int enter_reading = enter_btn_.get_reading();

  MomentarySwitch::InputType enter_input_type =
    enter_btn_.get_input_type();

  //____________________________________________________________________________
  // Debug
  if (state_changed)
  {
    //Debug::print_labeled_int("TimeController::set_time -- Current state: "
    //  , static_cast<int>(state_));
    state_changed = false;
  }
  //____________________________________________________________________________

  if (enter_input_type == MomentarySwitch::InputType::SHORT)
  {
    set_next_state();
    state_changed = true;
    //Debug::print_labeled_int("TimeController::set_time -- New state:     "
    //  , static_cast<int>(state_));
    return;
  }

  short yr;
  short mo;
  short day;
  short hr;
  short min;

  bool inc_val =
    inc_btn_.get_input_type() == MomentarySwitch::InputType::SHORT;

  bool dec_val =
    dec_btn_.get_input_type() == MomentarySwitch::InputType::SHORT;

  switch (state_)
  {
    //__________________________________________________________________________
    case (State::IDLE):
      // TODO fix this function so it doesn't break when your string is less
      // than 4 characters
      display_->write_disp_str("IDLE");
      break;

    //__________________________________________________________________________
    case (State::SET_YR):

      if (inc_val)
        inc_yr();

      else if (dec_val)
        dec_yr();

      yr = clock_->get_yr();
      display_->write_disp_yr(yr);

      break;

    //__________________________________________________________________________
    case (State::SET_MO):

      if (inc_val)
        inc_mo();

      else if (dec_val)
        dec_mo();

      mo = clock_->get_month();
      display_->write_disp_mo(mo);

      break;

    //__________________________________________________________________________
    case (State::SET_DATE):

      if (inc_val)
        inc_day();

      else if (dec_val)
        dec_day();

      day = clock_->get_day();
      display_->write_disp_day(day);

      break;

    //__________________________________________________________________________
    case (State::SET_HR):

      if (inc_val)
        inc_hr();

      else if (dec_val)
        dec_hr();

      hr = clock_->get_hr();
      display_->write_disp_hr(hr);

      break;

    //__________________________________________________________________________
    case (State::SET_MIN):

      if (inc_val)
        inc_min();

      else if (dec_val)
        dec_min();


      min = clock_->get_min();
      display_->write_disp_min(min);

      break;

    case(State::DONE):
      set_next_state();
      break;

    //__________________________________________________________________________
    default:
      break;
  }

  return;
}

//______________________________________________________________________________
// Sets the next state based on the current state.
//______________________________________________________________________________
void TimeController::set_next_state()
{
  switch (state_)
  {
    case (State::IDLE):
      state_ = State::SET_YR;
      break;

    case (State::SET_YR):
      state_ = State::SET_MO;
      break;

    case (State::SET_MO):
      state_ = State::SET_DATE;
      break;

    case (State::SET_DATE):
      state_ = State::SET_HR;
      break;

    case (State::SET_HR):
      state_ = State::SET_MIN;
      break;

    case (State::SET_MIN):
      state_ = State::DONE;
      break;

    case (State::DONE):
      state_ = State::IDLE;
      break;

    default:
      state_ = State::IDLE;
      break;
  }

}

//______________________________________________________________________________
// Increments the month by one
//______________________________________________________________________________
void TimeController::inc_mo()
{
  clock_->set_month(clock_->get_month()   + 1);
}


//______________________________________________________________________________
// Decrements the month by one
//______________________________________________________________________________
void TimeController::dec_mo()
{
  clock_->set_month(clock_->get_month() - 1);
}


//______________________________________________________________________________
// Increments the hour by one
//______________________________________________________________________________
void TimeController::inc_hr()
{
  clock_->set_hr(clock_->get_hr() + 1);
}

//______________________________________________________________________________
// Decrements the hour by one
//______________________________________________________________________________
void TimeController::dec_hr()
{
  clock_->set_hr(clock_->get_hr() - 1);
}
