#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include "classes.hpp"
#include "debug.hpp"
#include "logic.hpp"
#include "time-calcs.hpp"
#include "rtc-clock.hpp"


Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();



void write_display_time(){

  alpha4.writeDigitAscii(3, 0x30 + RtcClock::rtc_sec % 10);
  alpha4.writeDigitAscii(2, 0x30 + RtcClock::rtc_sec / 10);
  alpha4.writeDigitAscii(1, 0x30 + RtcClock::rtc_min % 10);
  alpha4.writeDigitAscii(0, 0x30 + RtcClock::rtc_min / 10);

  alpha4.writeDisplay();
}

void write_flux_to_display(){
  alpha4.writeDigitAscii(0, 'F');
  alpha4.writeDigitAscii(1, 'L');
  alpha4.writeDigitAscii(2, 'U');
  alpha4.writeDigitAscii(3, 'X');
  alpha4.writeDisplay();
}

void setup(){
  Serial.begin(9600);
  alpha4.begin(0x70);

  Wire.begin();


}


void loop(){
  RgbColor color;
  Debug::print_new_line();
  Debug::print_color(color);
  write_flux_to_display();
  delay(1000);
}
