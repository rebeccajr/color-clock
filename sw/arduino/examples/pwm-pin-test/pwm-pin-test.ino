//______________________________________________________________________________
// This example is to test the pwm pins on the MKR1010
//______________________________________________________________________________

#include <Arduino.h>
#include <Adafruit_AW9523.h>

// According to the Arduino website, the following pins are available for PWM:
// 0 .. 8, 10, 12, A3, A4
//
// CONFIRMED
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, A3, A4
//
// A0
//
// NO PWM
// 9


uint8_t pin0 = 9;
uint8_t pin1 = 10;

bool color = 0;

void setup()
{
  pinMode(pin0, OUTPUT);
  pinMode(pin1, OUTPUT);
}

void loop()
{

  static uint8_t i = 0;
  uint8_t the_pin  = 0;

  if (color)
    the_pin = pin0;
  else
    the_pin = pin1;
    
  analogWrite(the_pin, ++i);

  if (i == 0)
    color = !color; 

  delay(10);
}
