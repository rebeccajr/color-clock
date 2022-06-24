//------------------------------------------------------------------------------
// DESCRIPTION
// This class contains functionality that interacts with the ChronoDot V2.1
// RTC.
//------------------------------------------------------------------------------

#include "rtc-clock.hpp"

byte RtcClock::rtc_hr;
byte RtcClock::rtc_min;
byte RtcClock::rtc_sec;

bool RtcClock::h12Flag;
bool RtcClock::pmFlag;
//------------------------------------------------------------------------------
// Populates a byte array with the time from a Real Time Clock
//------------------------------------------------------------------------------
void RtcClock::get_rtc_time(byte* the_time, DS3231 clk){
  the_time[2] = clk.getHour(h12Flag, pmFlag);
  the_time[1] = clk.getMinute();
  the_time[0] = clk.getSecond();
}
