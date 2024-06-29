//______________________________________________________________________________
// This example tests the Adafruit AW923 GPIO expander.
//______________________________________________________________________________
#include <Arduino.h>
#include <Adafruit_AW9523.h>

#include "debug.hpp"
Adafruit_AW9523 aw;

uint8_t LedPin = 2;  // 0 thru 15
uint8_t blinky_pin = 1;  // 0 thru 15

uint8_t pwm_pin = 3;

void led_blink(int pin, int time_delay)
{
  aw.digitalWrite(pin, 1);
  delay(time_delay);
  aw.digitalWrite(pin, 0);
  delay(time_delay);
}

void setup() {
  Serial.begin(115200);
  //while (!Serial) delay(1);  // wait for serial port to open
  
  Serial.println("Adafruit AW9523 Constant Current LED test!");

  if (! aw.begin(0x58)) {
    Serial.println("AW9523 not found? Check wiring!");
    while (1) delay(10);  // halt forever
  }

  Serial.println("AW9523 found!");
  //aw.pinMode(LedPin, AW9523_LED_MODE); // set to constant current drive!

  aw.pinMode(8, AW9523_LED_MODE); // set to constant current drive!
  aw.pinMode(9, AW9523_LED_MODE); // set to constant current drive!
  aw.pinMode(10, AW9523_LED_MODE); // set to constant current drive!
  aw.pinMode(11, AW9523_LED_MODE); // set to constant current drive!
  //aw.pinMode(10, OUTPUT); // set to constant current drive!
  //aw.pinMode(11, OUTPUT); // set to constant current drive!

  //aw.pinMode(blinky_pin, OUTPUT);
  //aw.pinMode(LedPin, OUTPUT);
  //pinMode(pwm_pin, OUTPUT);

  aw.analogWrite(8, 0);
  aw.analogWrite(9, 64);
  aw.analogWrite(10, 128);
  aw.analogWrite(11, 255);
}


uint8_t x = 0;

void loop() {
  // Loop from 0 to 255 and then wrap around to 0 again
  //aw.analogWrite(LedPin, 255); 
  //Debug::print_labeled_int("value: ", x, true);

  //aw.digitalWrite(10, true);
  //aw.digitalWrite(11, false);

  Serial.println("proof of life");

  //delay(.5);

  //analogWrite(pwm_pin, x++); 
  //led_blink(blinky_pin, 100);
}

//__________________________________________________________________________________________________________

//__________________________________________________________________________________________________________
//__________________________________________________________________________________________________________
//__________________________________________________________________________________________________________
/*
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AW9523.h>

#include "debug.hpp"

#define AW9523_ADDR 0x58

Adafruit_AW9523 aw;

int red_pin =  1;
int grn_pin =  2;
int blu_pin =  3;

int red_val = 0;
int grn_val = 0;
int blu_val = 0;

void led_blink(int pin, int time_delay)
{
  aw.digitalWrite(pin, 1);
  delay(time_delay);
  aw.digitalWrite(pin, 0);
  delay(time_delay);
}

void setup()
{ 
  Serial.begin(115200);
  Serial.println("Adafruit AW9523 GPIO Expander test!");

  // Required to interface with AW9523
  if (!aw.begin(AW9523_ADDR))
  {
    Serial.println("AW9523 not found? Check wiring!");
    while (1) delay(10);  // halt forever
  }
  else
    Serial.println("AW9523 found!");
 
  // Required to interface with I2C
  Wire.begin();

  //aw.pinMode(red_pin, AW9523_LED_MODE);
  aw.pinMode(grn_pin, AW9523_LED_MODE);
  aw.pinMode(blu_pin, AW9523_LED_MODE);
  aw.pinMode(red_pin, OUTPUT);

}

void loop()
{
  const int time_delay = 50;
  static bool incr = false;
  static bool red = true;
  static bool grn = false;
  static bool blu = false;

  bool decr = !incr;

  if (red)
  {
    if (incr && red_val < 255)
    {
      red_val++;
      //Serial.println("incr && red_val < 255");
    }
    else if (decr && red_val > 0)
    {
      red_val--;
      //Serial.println("decr && red_val > 1");
    }
    if (red_val == 0 || red_val == 255)
      incr = !incr;

    Debug::print_labeled_int("red: ", red_val, true);
  }

  
  led_blink(red_pin, time_delay);

  //aw.analogWrite(red_pin, red_val);
  //aw.AnalogWrite(grn_pin, grn_val);
  //aw.AnalogWrite(blu_pin, blu_val);
  //delay(time_delay);

}
*/

