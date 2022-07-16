//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------

#include "alpha-display.hpp"

//------------------------------------------------------------------------------
// Write the time to the alphanumeric display
//------------------------------------------------------------------------------
void AlphaDisplay::write_display_time(byte hr, byte min, byte sec){

  led_segments.writeDigitAscii(3, 0x30 + sec % 10);
  led_segments.writeDigitAscii(2, 0x30 + sec / 10);
  led_segments.writeDigitAscii(1, 0x30 + min % 10);
  led_segments.writeDigitAscii(0, 0x30 + min / 10);

  led_segments.writeDisplay();
}


void AlphaDisplay::write_flux_to_display(){
  led_segments.writeDigitAscii(0, 'F');
  led_segments.writeDigitAscii(1, 'L');
  led_segments.writeDigitAscii(2, 'U');
  led_segments.writeDigitAscii(3, 'X');
  led_segments.writeDisplay();
}
