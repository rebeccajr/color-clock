//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------

#include "alpha-display.hpp"

Adafruit_AlphaNum4 AlphaDisplay::the_alpha_display = Adafruit_AlphaNum4();

//------------------------------------------------------------------------------
// Write the time to the alphanumeric display
//------------------------------------------------------------------------------
void AlphaDisplay::write_display_time(byte hr, byte min, byte sec){

  the_alpha_display.writeDigitAscii(3, 0x30 + sec % 10);
  the_alpha_display.writeDigitAscii(2, 0x30 + sec / 10);
  the_alpha_display.writeDigitAscii(1, 0x30 + min % 10);
  the_alpha_display.writeDigitAscii(0, 0x30 + min / 10);

  the_alpha_display.writeDisplay();
}


void AlphaDisplay::write_flux_to_display(){
  the_alpha_display.writeDigitAscii(0, 'F');
  the_alpha_display.writeDigitAscii(1, 'L');
  the_alpha_display.writeDigitAscii(2, 'U');
  the_alpha_display.writeDigitAscii(3, 'X');
  the_alpha_display.writeDisplay();
}
