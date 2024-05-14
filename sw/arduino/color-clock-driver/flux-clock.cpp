//______________________________________________________________________________
// Implementations for clock functions. Function implmentation are dependent
// on the target platform.
//______________________________________________________________________________

#include "flux-clock.hpp"


//______________________________________________________________________________
//______________________________________________________________________________
short FluxClock::get_yr()
{
#ifdef ARDUINO_BUILD
  return rtc_.getYear();
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_year;
#endif
}


//______________________________________________________________________________
//______________________________________________________________________________
byte FluxClock::get_month()
{
#ifdef ARDUINO_BUILD
  //__________________________________________________________________________
  // The century_bit toggles when there is roll-over to a new century, e.g.
  // from year 2099 to 2100. The century_bit will likely never be relevant for
  // any use case for this code base. More information about this bit
  // can be found: https://github.com/NorthernWidget/DS3231/blob/master/Documentation/Time-Retrieval.md#getMinute
  bool century_bit;
  return rtc_.getMonth(century_bit);
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_mon;
#endif
}


//______________________________________________________________________________
// Returns the day of the month.
//______________________________________________________________________________
byte FluxClock::get_day()
{
#ifdef ARDUINO_BUILD
  return rtc_.getDate();
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_mday;
#endif
}


//______________________________________________________________________________
// Returns the hour of the day.
//______________________________________________________________________________
byte FluxClock::get_hr()
{

#ifdef ARDUINO_BUILD
  //__________________________________________________________________________
  // These bools are passed by reference. The values are modified as follows:
  // parameter h12:  true = 12 hr time; false = 24 hr time
  // parameter h_pm: true = PM;         false = AM
  //__________________________________________________________________________
  bool h12;
  bool h_pm;
  //__________________________________________________________________________
  return rtc_.getHour(h12, h_pm);
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_hour;
#endif
}


//______________________________________________________________________________
// Returns the minute of the hour.
//______________________________________________________________________________
byte FluxClock::get_min()
{

#ifdef ARDUINO_BUILD
  return rtc_.getMinute();
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_min;
#endif
}


//______________________________________________________________________________
// Returns the second of the minute.
//______________________________________________________________________________
byte FluxClock::get_sec()
{
#ifdef ARDUINO_BUILD
  return rtc_.getSecond();
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_sec;
#endif
}

#ifdef ARDUINO_BUILD
//______________________________________________________________________________
void FluxClock::set_yr(short yr)    {rtc_.setYear(yr);}
void FluxClock::set_month(byte mo)  {rtc_.setMonth(mo);}
void FluxClock::set_day(byte day)   {rtc_.setDate(day);}
void FluxClock::set_hr(byte hr)     {rtc_.setHour(hr);}
void FluxClock::set_min(byte min)   {rtc_.setMinute(min);}
void FluxClock::set_sec(byte sec)   {rtc_.setSecond(sec);}
#endif
