
//______________________________________________________________________________
// DESCRIPTION
// This class contains control logic for the time.
//______________________________________________________________________________

#include "time-controller.hpp"

void TimeController::inc_yr()  { rtc_->setYear(rtc_->getYear()     + 1); }
void TimeController::dec_yr()  { rtc_->setYear(rtc_->getYear()     - 1); }
void TimeController::inc_day() { rtc_->setDate (rtc_->getDate()    + 1); }
void TimeController::dec_day() { rtc_->setDate(rtc_->getDate()     - 1); }
void TimeController::inc_min() { rtc_->setMinute(rtc_->getMinute() + 1); }
void TimeController::dec_min() { rtc_->setMinute(rtc_->getMinute() - 1); }



//______________________________________________________________________________
// State machine for time set
//______________________________________________________________________________
void TimeController::set_time()
{
  int inc_reading   = inc_btn_.get_reading();
  int dec_reading   = dec_btn_.get_reading();
  int enter_reading = enter_btn_.get_reading();

  MomentarySwitch::InputType enter_input_type =
    enter_btn_.get_input_type();

  if (enter_input_type == MomentarySwitch::InputType::DOUBLE)
  {
    Serial.print("Current state: ");
    Serial.println(static_cast<int>(state_));
    set_next_state();
    Serial.print("New state:     ");
    Serial.println(static_cast<int>(state_));
    return;
  }

  //____________________________________________________________________________
  // These bools are required for some of the set functions.
  // See the time set functions for more information.
  bool h12;
  bool h_pm;
  bool century_bit;
  //____________________________________________________________________________

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
      display_->write_disp_str("    ");
      break;

    //__________________________________________________________________________
    case (State::SET_YR):

      if (inc_val)
        inc_yr();

      else if (dec_val)
        dec_yr();

      yr = rtc_->getYear();
      display_->write_disp_yr(yr);

      break;

    //__________________________________________________________________________
    case (State::SET_MO):

      if (inc_val)
        inc_mo();

      else if (dec_val)
        dec_mo();

      mo = rtc_->getMonth(century_bit);
      display_->write_disp_mo(mo);

      break;

    //__________________________________________________________________________
    case (State::SET_DATE):

      if (inc_val)
        inc_day();

      else if (dec_val)
        dec_day();

      day = rtc_->getDate();
      display_->write_disp_day(day);

      break;

    //__________________________________________________________________________
    case (State::SET_HR):

      if (inc_val)
        inc_hr();

      else if (dec_val)
        dec_hr();

      hr = rtc_->getHour(h12, h_pm);
      display_->write_disp_hr(hr);

      break;

    //__________________________________________________________________________
    case (State::SET_MIN):

      if (inc_val)
        inc_min();

      else if (dec_val)
        dec_min();


      min = rtc_->getMinute();
      display_->write_disp_min(min);

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
  // The century_bit toggles when there is roll-over to a new century, e.g.
  // from year 2099 to 2100. The century_bit will likely never be relevant for
  // any use case for this code base. More information about this bit
  // can be found: https://github.com/NorthernWidget/DS3231/blob/master/Documentation/Time-Retrieval.md#getMinute
  bool century_bit;
  rtc_->setMonth(rtc_->getMonth(century_bit)   + 1);
}


//______________________________________________________________________________
// Decrements the month by one
//______________________________________________________________________________
void TimeController::dec_mo()
{
  // The century_bit toggles when there is roll-over to a new century, e.g.
  // from year 2099 to 2100. The century_bit will likely never be relevant for
  // any use case for this code base. More information about this bit
  // can be found: https://github.com/NorthernWidget/DS3231/blob/master/Documentation/Time-Retrieval.md#getMinute
  bool century_bit;
  rtc_->setMonth(rtc_->getMonth(century_bit) - 1);
}


//______________________________________________________________________________
// Increments the hour by one
//______________________________________________________________________________
void TimeController::inc_hr()
{
  // These bools are passed by reference. The values are modified as follows:
  // parameter h12:  true = 12 hr time; false = 24 hr time
  // parameter h_pm: true = PM;         false = AM
  bool h12;
  bool h_pm;
  rtc_->setHour(rtc_->getHour(h12, h_pm) + 1);
}

//______________________________________________________________________________
// Decrements the hour by one
//______________________________________________________________________________
void TimeController::dec_hr()
{
  // These bools are passed by reference. The values are modified as follows:
  // parameter h12:  true = 12 hr time; false = 24 hr time
  // parameter h_pm: true = PM;         false = AM
  bool h12;
  bool h_pm;
  rtc_->setHour(rtc_->getHour(h12, h_pm) - 1);
}