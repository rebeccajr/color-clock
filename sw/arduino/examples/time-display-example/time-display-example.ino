//______________________________________________________________________________
// This file is a test for the TimeDisplay class.
//______________________________________________________________________________

#include <Arduino.h>
#include <Wire.h>

#include "time-display.hpp"

TimeDisplay display;

void setup()
{
  Serial.begin(9600);
  display.led_segments.begin(0x70);
  Wire.begin();
}

void loop()
{
    static int i = 0;
    if(millis() % 1000 == 0)
    {
        Serial.println(i++);
        Serial.println("proof of life");
    }

    display.write_disp_str("FLUX");
}