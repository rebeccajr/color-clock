//______________________________________________________________________________
// This example tests the DS3231 module with the time-display
//______________________________________________________________________________

#include <Arduino.h>
#include <Wire.h>

#include "time-display.hpp"
#include "flux-clock.hpp"

TimeDisplay display;
FluxClock   clocky;

int threshold = 1000;
int long_threshold = 5000;

using byte = unsigned char;

void setup()
{
  Serial.begin(9600);

  // Setup up required for time-display
  display.led_segments.begin(0x70);

  // Required to interface with I2C
  Wire.begin();

  // Initialize clock
  clocky.set_hr(15);
  clocky.set_min(15);

}


void loop()
{
  static long prev_sec = 0;
         long crnt_sec = millis();

  byte clk_sec = clocky.get_sec();
  byte clk_min = clocky.get_min();

  static int i = 0;

  if(crnt_sec - prev_sec >= threshold)
  {
    Serial.println("_____________");
    Serial.print("count: ");
    Serial.println(i++);
    Serial.println("proof of life");

    Serial.print("sec:   ");
    Serial.println(int(clk_sec));
    prev_sec = crnt_sec;
  }

  display.write_disp_time(clk_min, clk_sec);

}