//------------------------------------------------------------------------------
// DESCRIPTION
// This class contains functionality that interacts with the ChronoDot V2.1
// RTC.
//------------------------------------------------------------------------------

#include <DS3231.h>

class RtcClock{

public:
  static DS3231 clk;

  static byte rtc_hr;
  static byte rtc_min;
  static byte rtc_sec;
  static bool h12Flag;
  static bool pmFlag;

  static void get_rtc_time(byte* the_time, DS3231 clk);

};
