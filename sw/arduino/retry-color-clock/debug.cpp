#include <Wire.h>
#include <Arduino.h>
#include "debug.hpp"


//------------------------------------------------------------------------------
void Debug::print_color(RgbColor color){
  Serial.print("RgbColor");
}


//------------------------------------------------------------------------------
void Debug::print_color(HsvColor color){
  Serial.print("HsvColor");
}


//------------------------------------------------------------------------------
void print_time(byte hr, byte minute, byte sec){
  Serial.print("\n---------------------------");
  Serial.print("\n Time");
  Serial.print("\n---------------------------");

  Serial.print("\nhour:  ");
  Serial.print(hr, DEC);
  Serial.print(" ");
  Serial.print("\nmin:   ");
  Serial.print(minute, DEC);
  Serial.print(" ");
  Serial.print("\nsec:   ");
  Serial.print(sec, DEC);
}


//------------------------------------------------------------------------------
void Debug::print_new_line(){
  Serial.print("\n");
}

