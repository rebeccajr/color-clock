#include <Arduino.h>
#include <Wire.h>

int red_pin = A0;
int grn_pin = A1;
int blu_pin = A2;
bool first_run = true;
int cycle_count = 0;
//______________________________________________________________________________

void setup(){
  Wire.begin();

  Serial.begin(9600);
  pinMode(red_pin, OUTPUT);
  pinMode(grn_pin, OUTPUT);
  pinMode(blu_pin, OUTPUT);
}
//______________________________________________________________________________
void loop(){

  // initialize clock
  if (first_run == true) {
    first_run = false;
  }

  int on  = 0xFF;
  int off = 0x00;

  if (cycle_count % 3 == 0)
  {
    analogWrite(red_pin, on);
    analogWrite(grn_pin, 0);
    analogWrite(blu_pin, 0);
  }

  else if (cycle_count % 3 == 1)
  {
    analogWrite(red_pin, 0);
    analogWrite(grn_pin, on);
    analogWrite(blu_pin, 0);
  }

  else if (cycle_count % 3 == 2)
  {
    analogWrite(red_pin, 0);
    analogWrite(grn_pin, 0);
    analogWrite(blu_pin, on);
  }


  delay(500);

  analogWrite(red_pin, 0);
  analogWrite(grn_pin, 0);
  analogWrite(blu_pin, 0);

  delay(500);

  cycle_count++;

} 