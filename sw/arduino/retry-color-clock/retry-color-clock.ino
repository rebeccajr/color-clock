
#include <Arduino.h>
#include <Wire.h>

#include "logic.hpp"
#include "debug.hpp"

void setup(){
  Serial.begin(9600);
  
  Wire.begin();
}

void loop(){

  RgbColor color;
  Debug::print_new_line();
  Debug::print_color(color);
  delay(1000);
}


