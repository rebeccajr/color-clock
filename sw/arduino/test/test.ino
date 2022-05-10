//------------------------------------------------------------------------------
// DESCRIPTION
// This script tests the Adfruit LED alphanumeric display with backpack and
// Chronodot clock module
//
//
//------------------------------------------------------------------------------
#include <Wire.h>
#include <DS3231.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
DS3231 clock0;

byte set_hr  = 13;
byte set_min = 54;

bool h12Flag;
bool pmFlag;

void setup() {

  Serial.begin(57600);

  alpha4.begin(0x70);  

  alpha4.writeDigitAscii(0, 'F');
  alpha4.writeDigitAscii(1, 'L');
  alpha4.writeDigitAscii(2, 'U');
  alpha4.writeDigitAscii(3, 'X');
  alpha4.writeDisplay();

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Wire.begin();

  Serial.print("\n---------------------------");
  Serial.print("\n---------------------------");
  Serial.print("\n before setting");
  Serial.print("\n---------------------------");
  Serial.print("\nhour:  ");
  Serial.print(clock0.getHour(h12Flag, pmFlag), DEC);
  Serial.print(" ");
  Serial.print("\nmin:   ");
  Serial.print(clock0.getMinute(), DEC);
 

  //Wire.begin();
  //Wire.onReceive(receiveEvent);
  //Serial.begin(9600);
}



// the loop function runs over and over again forever
void loop() {

  clock0.setHour(set_hr);
  clock0.setMinute(set_min);
  Serial.print("\n---------------------------");
  Serial.print("\n---------------------------");
  Serial.print("\n clock stuff");
  Serial.print("\n---------------------------");
  Serial.print("\nhour:  ");
  Serial.print(clock0.getHour(h12Flag, pmFlag), DEC);
  Serial.print(" ");
  Serial.print("\nmin:   ");
  Serial.print(clock0.getMinute(), DEC);
  Serial.print(" ");
  Serial.print("\nsec:   ");
  Serial.print(clock0.getSecond(), DEC);
  delay(1000);

  /*
  byte deviceAddress = 0xD0;
  byte wordAddress   = 0x02;
  byte hr            = 0x06;

  Wire.beginTransmission(deviceAddress);
  Wire.endTransmission();
  
  //Wire.write(0b0);
  //Wire.write(wordAddress);
  //Wire.write(hr);
  
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(10);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(10);                       // wait for a second
}

void receiveEvent(int howMany)
{
  
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read();     // receive byte as a character
    Serial.print(c);          // print the character
  }
  
  int x = Wire.read();        // receive byte as an integer
  Serial.println(x);          // print the integer
  */
  
}
