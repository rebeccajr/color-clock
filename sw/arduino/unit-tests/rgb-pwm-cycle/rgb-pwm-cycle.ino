//______________________________________________________________________
// This program tests the pwm output for three pins, cycling through
// the values of 0 to 255.
//______________________________________________________________________
#include <Arduino.h>
#include <stdint.h>

#define DELAY_MILLIS 10

uint8_t red_pin = D3;
uint8_t grn_pin = D4;
uint8_t blu_pin = D5;

const int freq       = 5000;
const int resolution = 8;
const int led_ch_red = 0;
const int led_ch_grn = 1;
const int led_ch_blu = 2;

void setup()
{
  pinMode(red_pin, OUTPUT);
  pinMode(grn_pin, OUTPUT);
  pinMode(blu_pin, OUTPUT);
}

void loop()
{
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle+=5)
    {
      analogWrite(red_pin, dutyCycle);
      delay(DELAY_MILLIS);
    }

    for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle-=5)
    {
      analogWrite(blu_pin, dutyCycle);
      Serial.println(dutyCycle);
      delay(DELAY_MILLIS);
    }

    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle+=5)
    {
      analogWrite(grn_pin, dutyCycle);
      delay(DELAY_MILLIS);
    }

    for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle-=5)
    {
      analogWrite(red_pin, dutyCycle);
      delay(DELAY_MILLIS);
    }

    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle+=5)
    {
      analogWrite(blu_pin, dutyCycle);
      delay(DELAY_MILLIS);
    }

    for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle-=5)
    {
      analogWrite(grn_pin, dutyCycle);
      delay(DELAY_MILLIS);
    }
}