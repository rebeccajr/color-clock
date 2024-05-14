//______________________________________________________________________________
//
//______________________________________________________________________________

#include "time-display.hpp"

//______________________________________________________________________________
// Write the time to the alphanumeric display
//______________________________________________________________________________
void TimeDisplay::write_disp_time(byte time_large, byte time_small){

  led_segments.writeDigitAscii(3, 0x30 + time_small % 10);
  led_segments.writeDigitAscii(2, 0x30 + time_small / 10);
  led_segments.writeDigitAscii(1, 0x30 + time_large % 10);
  led_segments.writeDigitAscii(0, 0x30 + time_large / 10);

  led_segments.writeDisplay();
}


//______________________________________________________________________________
// Writes four character string to display
//______________________________________________________________________________
void TimeDisplay::write_disp_str(const char* str)
{
  led_segments.writeDigitAscii(0, str[0]);
  led_segments.writeDigitAscii(1, str[1]);
  led_segments.writeDigitAscii(2, str[2]);
  led_segments.writeDigitAscii(3, str[3]);

  led_segments.writeDisplay();
}

//______________________________________________________________________________
// Writes two character string and two digit number to display
//______________________________________________________________________________
void TimeDisplay::write_disp_str_num(const char* str, byte num)
{
  led_segments.writeDigitAscii(0, str[0]);
  led_segments.writeDigitAscii(1, str[1]);
  led_segments.writeDigitAscii(2, 0x30 + num / 10);
  led_segments.writeDigitAscii(3, 0x30 + num % 10);

  led_segments.writeDisplay();
}


//______________________________________________________________________________
// Functions for writing time units to
//______________________________________________________________________________
void TimeDisplay::write_disp_yr(byte yr)   { write_disp_str_num("YR", yr);  }
void TimeDisplay::write_disp_mo(byte mo)   { write_disp_str_num("MO", mo);  }
void TimeDisplay::write_disp_day(byte day) { write_disp_str_num("DA", day); }
void TimeDisplay::write_disp_hr(byte hr)   { write_disp_str_num("HR", hr);  }
void TimeDisplay::write_disp_min(byte min) { write_disp_str_num("MI", min); }


//______________________________________________________________________________
// Writes hour and minute to LED alphanumeric display
//______________________________________________________________________________
void TimeDisplay::write_disp_hr_min(byte hr, byte min)
{
  led_segments.writeDigitAscii(3, 0x30 + min % 10);
  led_segments.writeDigitAscii(2, 0x30 + min / 10);
  led_segments.writeDigitAscii(1, 0x30 + hr % 10);
  led_segments.writeDigitAscii(0, 0x30 + hr / 10);

  led_segments.writeDisplay();
}