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
// Implementations for clock functions. Function implmentation is
// dependent on the target platform.
//______________________________________________________________________

#include "flux-clock.hpp"
#include "flux-macros.hpp"


//______________________________________________________________________
short FluxClock::get_yr()
{
#ifdef USING_DS3231
  return rtc_.getYear();
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_year;
#endif
}


//______________________________________________________________________
//______________________________________________________________________
uint8_t FluxClock::get_month()
{
#ifdef USING_DS3231
  //__________________________________________________________________
  // The century_bit toggles when there is roll-over to a new century, e.g.
  // from year 2099 to 2100. The century_bit will likely never be relevant for
  // any use case for this code base. More information about this bit
  // can be found: https://github.com/NorthernWidget/DS3231/blob/master/Documentation/Time-Retrieval.md#getMinute
  //__________________________________________________________________
  bool century_bit;
  return rtc_.getMonth(century_bit);
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_mon;
#endif
}


//______________________________________________________________________
// Returns the day of the month.
//______________________________________________________________________
uint8_t FluxClock::get_day()
{
#ifdef USING_DS3231
  return rtc_.getDate();
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_mday;
#endif
}


//______________________________________________________________________
// Returns the hour of the day.
//______________________________________________________________________
uint8_t FluxClock::get_hr()
{

#ifdef USING_DS3231
  //____________________________________________________________________
  // Bools passed by reference. The values are modified as follows:
  // parameter h12:  true = 12 hr time; false = 24 hr time
  // parameter h_pm: true = PM;         false = AM
  //____________________________________________________________________
  bool h12;
  bool h_pm;
  //____________________________________________________________________
  return rtc_.getHour(h12, h_pm);
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_hour;
#endif
}


//______________________________________________________________________
// Returns the minute of the hour.
//______________________________________________________________________
uint8_t FluxClock::get_min()
{

#ifdef USING_DS3231
  return rtc_.getMinute();
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_min;
#endif
}


//______________________________________________________________________
// Returns the second of the minute.
//______________________________________________________________________
uint8_t FluxClock::get_sec()
{
#ifdef USING_DS3231
  return rtc_.getSecond();
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_sec;
#endif
}


//______________________________________________________________________
// Returns the milli second of the second.
// Note: The RTC does not return milliseconds as a built in function,
// so this function incorporates the built-in Arduino function millis.
//______________________________________________________________________
int FluxClock::get_milli(uint8_t crnt_sec)
{
#ifdef USING_DS3231

  static uint8_t prev_sec = 0;
  static long int prev_millis = 0;
         long int crnt_millis = millis();

  // Resent millisecond count if its a new second
  if (crnt_sec != prev_sec)
  {
    prev_sec = crnt_sec;
    prev_millis = crnt_millis;
  }

  return static_cast<int>(crnt_millis - prev_millis);

#else
  return 0;
#endif
}


#ifdef USING_DS3231
//______________________________________________________________________
void FluxClock::set_yr(short yr)    {rtc_.setYear(yr);}
void FluxClock::set_month(uint8_t mo)  {rtc_.setMonth(mo);}
void FluxClock::set_day(uint8_t day)   {rtc_.setDate(day);}
void FluxClock::set_hr(uint8_t hr)     {rtc_.setHour(hr);}
void FluxClock::set_min(uint8_t min)   {rtc_.setMinute(min);}
void FluxClock::set_sec(uint8_t sec)   {rtc_.setSecond(sec);}
#endif
