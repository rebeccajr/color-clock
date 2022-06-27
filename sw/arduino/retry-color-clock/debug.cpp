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
void print_time(DS3231 clk){

  bool foo;
  bool bar;

  byte the_hr  = clk.getHour(foo, bar);
  byte the_min = clk.getMinute();
  byte the_sec = clk.getSecond();

  Serial.print("\n---------------------------");
  Serial.print("\n Time");
  Serial.print("\n---------------------------");

  Serial.print("\nhour:  ");
  Serial.print(the_hr, DEC);
  Serial.print(" ");
  Serial.print("\nmin:   ");
  Serial.print(the_min, DEC);
  Serial.print(" ");
  Serial.print("\nsec:   ");
  Serial.print(the_sec, DEC);
}


//------------------------------------------------------------------------------
void Debug::print_new_line(){
  Serial.print("\n");
}

