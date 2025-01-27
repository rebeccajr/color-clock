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
//
//______________________________________________________________________

#include "time-display.hpp"

//______________________________________________________________________
// Write the time to the alphanumeric display
//______________________________________________________________________
void TimeDisplay::write_disp_time(uint8_t time_large
  , uint8_t time_small)
{

#ifdef ARDUINO_BUILD
  led_segments.writeDigitAscii(3, 0x30 + time_small % 10);
  led_segments.writeDigitAscii(2, 0x30 + time_small / 10);
  led_segments.writeDigitAscii(1, 0x30 + time_large % 10);
  led_segments.writeDigitAscii(0, 0x30 + time_large / 10);

  led_segments.writeDisplay();
#endif
}


//______________________________________________________________________
// Writes four character string to display
//______________________________________________________________________
void TimeDisplay::write_disp_str(const char* str)
{
#ifdef ARDUINO_BUILD
  led_segments.writeDigitAscii(0, str[0]);
  led_segments.writeDigitAscii(1, str[1]);
  led_segments.writeDigitAscii(2, str[2]);
  led_segments.writeDigitAscii(3, str[3]);

  led_segments.writeDisplay();
#endif
}

//______________________________________________________________________
// Writes two character string and two digit number to display
//______________________________________________________________________
void TimeDisplay::write_disp_str_num(const char* str, uint8_t num)
{
#ifdef ARDUINO_BUILD
  led_segments.writeDigitAscii(0, str[0]);
  led_segments.writeDigitAscii(1, str[1]);
  led_segments.writeDigitAscii(2, 0x30 + num / 10);
  led_segments.writeDigitAscii(3, 0x30 + num % 10);

  led_segments.writeDisplay();
#endif
}


//______________________________________________________________________
// Functions for writing time units to
//______________________________________________________________________
void TimeDisplay::write_disp_yr(uint8_t yr)   { write_disp_str_num("YR", yr);  }
void TimeDisplay::write_disp_mo(uint8_t mo)   { write_disp_str_num("MO", mo);  }
void TimeDisplay::write_disp_day(uint8_t day) { write_disp_str_num("DA", day); }
void TimeDisplay::write_disp_hr(uint8_t hr)   { write_disp_str_num("HR", hr);  }
void TimeDisplay::write_disp_min(uint8_t min) { write_disp_str_num("MI", min); }
void TimeDisplay::write_disp_sec(uint8_t sec) { write_disp_str_num("SC", sec); }


//______________________________________________________________________
// Writes hour and minute to LED alphanumeric display
//______________________________________________________________________
void TimeDisplay::write_disp_hr_min(uint8_t hr, uint8_t min)
{
#ifdef ARDUINO_BUILD
  led_segments.writeDigitAscii(3, 0x30 + min % 10);
  led_segments.writeDigitAscii(2, 0x30 + min / 10);
  led_segments.writeDigitAscii(1, 0x30 + hr % 10);
  led_segments.writeDigitAscii(0, 0x30 + hr / 10);

  led_segments.writeDisplay();
#endif
}