Confirmed PWM Pins on MKR1010?

There is a discrepency in the PWM pins listed between the website, datasheet, and `analogWrite` for the MKR 1010.

The product page lists the following PWM pins:
https://store-usa.arduino.cc/products/arduino-mkr-wifi-1010
D0-D8, D10, D12, A3, A4

The datasheet lists the following PWM pins:
https://docs.arduino.cc/resources/datasheets/ABX00023-datasheet.pdf
D0-9

And the page for `analogWrite` lists:
https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/


I did a manual test of all the pins and found the following pins could output a PWM signal:
D0-8, D10, A3, A4, A0(?), D11(?)

D9 and D12 did not appear to output a PWM signal.

I found that pins A0 and D11 could output a PWM output signal, yet these pins were not listed on the website, nor the datasheet.

# Arduino information
Board: MKR1010
Environment: MacOS 11.7.8, Arduino CLI version 0.35.3 

# Test Case
I used visual inspection to determine if an RGB LED was dimming. The light would alternate between two colors, slowly increase in brightness until maximum brightness, then switch to the other color, starting from minimum brightness.

## Test Code
```
#include <Arduino.h>

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
```
