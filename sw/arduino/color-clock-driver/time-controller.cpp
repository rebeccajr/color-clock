
//______________________________________________________________________________
// DESCRIPTION
// This class contains control logic for the time.
//______________________________________________________________________________

#include "time-controller.hpp"

#define MAX_SEC   59
#define MAX_MIN   59
#define MAX_HR    23
#define MAX_DAY   31
#define MAX_MONTH 12

void TimeController::inc_yr()  { clock_->set_yr(clock_->get_yr()    + 1); }

void TimeController::dec_yr()  { clock_->set_yr(clock_->get_yr()    - 1); }



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

  if (enter_btn_.is_short_press())
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
    inc_btn_.is_short_press();

  bool dec_val =
    dec_btn_.is_short_press();

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
// TODO refactor time set functions to minimize code duplication
//______________________________________________________________________________

//______________________________________________________________________________
// Increments the minute by one
//______________________________________________________________________________
void TimeController::inc_min()
{
  short new_min = clock_->get_min() + 1;

  // Error handling for out of range
  if (new_min  > MAX_MIN)
    new_min = 0;
  if (new_min < 0)
    new_min = MAX_MIN;

  clock_->set_min(new_min);
}


//______________________________________________________________________________
// Decrements the minute by one
//______________________________________________________________________________
void TimeController::dec_min()
{
  short new_min = clock_->get_min()  - 1;

  // Error handling for out of range
  if (new_min  > MAX_MIN)
    new_min = 0;
  if (new_min < 0)
    new_min = MAX_MIN;

  clock_->set_min(new_min);
}


//______________________________________________________________________________
// Increments the hour by one
//______________________________________________________________________________
void TimeController::inc_hr()
{
  int new_hr = clock_->get_hr() + 1;

  // Error handling for out of range
  if (new_hr > MAX_HR)
    new_hr = 0;
  if (new_hr  < 0)
    new_hr = MAX_HR;

  clock_->set_hr(new_hr);
}

//______________________________________________________________________________
// Decrements the hour by one
//______________________________________________________________________________
void TimeController::dec_hr()
{
  int new_hr = clock_->get_hr() - 1;

  // Error handling for out of range
  if (new_hr > MAX_HR)
    new_hr = 0;
  if (new_hr  < 0)
    new_hr = MAX_HR;

  clock_->set_hr(new_hr);
}


//______________________________________________________________________________
// Decrements the day by one
//______________________________________________________________________________
void TimeController::inc_day()
{
  uint8_t new_day = clock_->get_day() + 1;

  // Error handling for out of range
  if (new_day > MAX_DAY)
    new_day = 1;
  if (new_day  <= 0)
    new_day = MAX_DAY;

  clock_->set_day(new_day);
}


//______________________________________________________________________________
// Increments the day by one
//______________________________________________________________________________
void TimeController::dec_day()
{
  uint8_t new_day = clock_->get_day() - 1;

  // Error handling for out of range
  if (new_day > MAX_DAY)
    new_day = 0;
  if (new_day  <= 0)
    new_day = MAX_DAY;

  clock_->set_day(new_day);
  
}


//______________________________________________________________________________
// Increments the month by one
//______________________________________________________________________________
void TimeController::inc_mo()
{
  int new_month = clock_->get_month() + 1;

  // Error handling for out of range
  if (new_month > MAX_MONTH)
    new_month = 1;
  if (new_month <= 0)
    new_month = MAX_MONTH;

  clock_->set_month(new_month);
}


//______________________________________________________________________________
// Decrements the month by one
//______________________________________________________________________________
void TimeController::dec_mo()
{
  int new_month = clock_->get_month() - 1;

  // Error handling for out of range
  if (new_month > MAX_MONTH)
    new_month = 1;
  if (new_month <= 0)
    new_month = MAX_MONTH;

  clock_->set_month(new_month);
}