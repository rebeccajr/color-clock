//______________________________________________________________________________
// This is a simple test Arduino sketch that uses a header file.
//______________________________________________________________________________

#include <Arduino.h>
#include <Wire.h>

#include "simple-header.hpp"

SimpleClass simple;

int out_pin0 = 4;
int out_pin1 = 6;

void setup()
{
    pinMode(out_pin0, OUTPUT);
    pinMode(out_pin1, OUTPUT);
}

void loop()
{
  Serial.println("blink!");
  digitalWrite(out_pin0, 1);
  digitalWrite(out_pin1, 0);
  delay(250);
  digitalWrite(out_pin0, 0);
  digitalWrite(out_pin1, 1);
  delay(250);
  
  //Serial.println(simple.variable);
  //Serial.println(FLUX);
}
