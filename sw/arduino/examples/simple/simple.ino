//______________________________________________________________________________
// This is a simple test Arduino sketch that uses a header file.
//______________________________________________________________________________

#include <Arduino.h>
#include <Wire.h>

#include <ctime>

#include "simple-header.hpp"

SimpleClass simple;

int out_pin = 5;

void setup()
{
    pinMode(out_pin, OUTPUT);
}

void loop()
{
  //digitalWrite(out_pin, 1);
  //delay(250);
  //digitalWrite(out_pin, 0);
  //delay(250);
  Serial.println("print!");
  //Serial.println(simple.variable);
  Serial.println(FLUX);
}
