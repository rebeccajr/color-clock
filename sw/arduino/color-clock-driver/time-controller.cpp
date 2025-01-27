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

#include "time-controller.hpp"

#define MAX_SEC   59
#define MAX_MIN   59
#define MAX_HR    23
#define MAX_DAY   31
#define MAX_MONTH 12

void TimeController::inc_yr()
  { clock_->set_yr(clock_->get_yr()    + 1); }

void TimeController::dec_yr()
  { clock_->set_yr(clock_->get_yr()    - 1); }

//______________________________________________________________________
// State machine for time set
//______________________________________________________________________
void TimeController::set_time()
{
  bool state_changed = false;

  int inc_reading   = inc_btn_.get_reading();
  int dec_reading   = dec_btn_.get_reading();
  int enter_reading = enter_btn_.get_reading();

  MomentarySwitch::InputType enter_input_type =
    enter_btn_.get_input_type();

  //____________________________________________________________________
  // Debug
  if (state_changed)
  {
    //Debug::print_labeled_int(
    //  "TimeController::set_time -- Current state: "
    //  , static_cast<int>(state_));
    state_changed = false;
  }
  //____________________________________________________________________

  if (enter_btn_.is_short_press())
  {
    set_next_state();
    state_changed = true;
    //Debug::print_labeled_int(
    //  "TimeController::set_time -- New state:     "
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
    //__________________________________________________________________
    case (State::IDLE):
      // TODO fix this function so it doesn't break when your string is
      // less than 4 characters
      display_->write_disp_str("IDLE");
      break;

    //__________________________________________________________________
    case (State::SET_YR):

      if (inc_val)
        inc_yr();

      else if (dec_val)
        dec_yr();

      yr = clock_->get_yr();
      display_->write_disp_yr(yr);

      break;

    //__________________________________________________________________
    case (State::SET_MO):

      if (inc_val)
        inc_mo();

      else if (dec_val)
        dec_mo();

      mo = clock_->get_month();
      display_->write_disp_mo(mo);

      break;

    //__________________________________________________________________
    case (State::SET_DATE):

      if (inc_val)
        inc_day();

      else if (dec_val)
        dec_day();

      day = clock_->get_day();
      display_->write_disp_day(day);

      break;

    //__________________________________________________________________
    case (State::SET_HR):

      if (inc_val)
        inc_hr();

      else if (dec_val)
        dec_hr();

      hr = clock_->get_hr();
      display_->write_disp_hr(hr);

      break;

    //__________________________________________________________________
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

    //__________________________________________________________________
    default:
      break;
  }

  return;
}

//______________________________________________________________________
// Sets the next state based on the current state.
//______________________________________________________________________
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

//______________________________________________________________________
// TODO refactor time set functions to minimize code duplication
//______________________________________________________________________

//______________________________________________________________________
// Increments the minute by one
//______________________________________________________________________
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


//______________________________________________________________________
// Decrements the minute by one
//______________________________________________________________________
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


//______________________________________________________________________
// Increments the hour by one
//______________________________________________________________________
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

//______________________________________________________________________
// Decrements the hour by one
//______________________________________________________________________
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


//______________________________________________________________________
// Decrements the day by one
//______________________________________________________________________
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


//______________________________________________________________________
// Increments the day by one
//______________________________________________________________________
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


//______________________________________________________________________
// Increments the month by one
//______________________________________________________________________
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


//______________________________________________________________________
// Decrements the month by one
//______________________________________________________________________
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