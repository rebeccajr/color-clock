//______________________________________________________________________________
// This example tests the Adafruit AW923 GPIO expander.
//______________________________________________________________________________
/*
#include <Adafruit_AW9523.h>

Adafruit_AW9523 aw;

uint8_t LedPin = 0;  // 0 thru 15

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);  // wait for serial port to open
  
  Serial.println("Adafruit AW9523 GPIO Expander test!");

  if (! aw.begin(0x58)) {
    Serial.println("AW9523 not found? Check wiring!");
    while (1) delay(10);  // halt forever
  }

  Serial.println("AW9523 found!");
  aw.pinMode(LedPin, OUTPUT);
}


void loop() {
  aw.digitalWrite(LedPin, HIGH);
  delay(100);
  aw.digitalWrite(LedPin, LOW);
  delay(100);
}


*/
//__________________________________________________________________________________________________________

/*
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AW9523.h>

#define AW9523_ADDR

Adafruit_AW9523 aw;

int red_pin =  8;
int grn_pin =  9;
int blu_pin = 10;

int red_val = 0;
int grn_val = 0;
int blu_val = 0;

void setup()
{
  Serial.begin(9600);

  // Required to interface with I2C
  Wire.begin();

  // Required to interface with AW9523
  aw.begin(AW9523_ADDR);

  aw.pinMode(red_pin, OUTPUT);
  aw.pinMode(grn_pin, OUTPUT);
  aw.pinMode(blu_pin, OUTPUT);

}

void loop()
{
  const int time_delay = 500;
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
    }
    else if (decr && red_val > 1)
    {
      red_val--;
    }
    if (red_val == 0 || red_val == 255)
      incr = !incr;
  }


  aw.analogWrite(red_pin, red_val);
  //aw.AnalogWrite(grn_pin, grn_val);
  //aw.AnalogWrite(blu_pin, blu_val);

  delay(time_delay);
}
*/
