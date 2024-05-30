//______________________________________________________________________________
// This example tests the Adafruit AW923 GPIO expander.
//______________________________________________________________________________
#include <Arduino.h>
#include <Adafruit_AW9523.h>
#include "debug.hpp"

#define AW9523_ADDR 0x58

Adafruit_AW9523 aw;

//_____________________ // pin-to-gnd_____________________________________________
uint8_t pin_0xFF = 2;   // 
uint8_t pin_0x80 = 3;   // 
uint8_t pin_0x40 = 4;   // 
uint8_t pin_0x10 = 3;   // 
uint8_t pin_0x08 = 6;   // 
uint8_t pin_0x00 = 7;   // 

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
  Serial.println("Adafruit AW9523 Constant Current LED test!");

  if (! aw.begin(AW9523_ADDR)) {
    Serial.println("AW9523 not found? Check wiring!");
    while (1) delay(10);  // halt forever
  }

  Serial.println("AW9523 found!");
  aw.pinMode(pin_0xFF, AW9523_LED_MODE); // const current drive
  //aw.pinMode(pin_0x80, AW9523_LED_MODE); // const current drive
  aw.pinMode(pin_0x40, AW9523_LED_MODE); // const current drive
  //aw.pinMode(pin_0x10, AW9523_LED_MODE); // const current drive
  //aw.pinMode(pin_0x08, AW9523_LED_MODE); // const current drive

  //aw.pinMode(blinky_pin, OUTPUT);
}


uint8_t x = 0;

void loop() {
  //aw.analogWrite(pin_0x00, x++);

  aw.analogWrite(pin_0xFF, 0xFF); 
  aw.analogWrite(pin_0x80, 0x80); 
  //aw.analogWrite(pin_0x40, 0x40); 
  //aw.analogWrite(pin_0x10, 0x10); 
  //aw.analogWrite(pin_0x08, 0x08); 
  delay(10);


  // Loop from 0 to 255 and then wrap around to 0 again
  //aw.analogWrite(LedPin, 0xFF);
  /*
  aw.analogWrite(LedPin, 128);
  //Debug::print_labeled_int("value: ", x, true);
  //led_blink(blinky_pin, 100);
  //Serial.println("Proof of life");
  delay(10);
*/

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

  aw.pinMode(red_pin, AW9523_LED_MODE);
  aw.pinMode(grn_pin, AW9523_LED_MODE);
  aw.pinMode(blu_pin, AW9523_LED_MODE);
  //aw.pinMode(red_pin, OUTPUT);

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

  
  //led_blink(red_pin, time_delay);
  aw.analogWrite(red_pin, 255);
  Serial.println("Proof of life");
  

  //aw.analogWrite(red_pin, red_val);
  //aw.AnalogWrite(grn_pin, grn_val);
  //aw.AnalogWrite(blu_pin, blu_val);
  //delay(time_delay);

}
*/
