#include <Wire.h>
#include <Arduino.h>
#include "debug.hpp"


//------------------------------------------------------------------------------
void Debug::print_color(RgbColor color){
  #ifdef DEBUG
  Serial.print("RgbColor");
  Serial.print("\nred:     ");
  Serial.print(RgbColor.r, HEX);
  Serial.print("\ngreen:   ");
  Serial.print(RgbColor.g, HEX);
  Serial.print("\nblue:    ");
  Serial.print(RgbColor.b, HEX);
  #endif
}


//------------------------------------------------------------------------------
void Debug::print_color(HsvColor color){
  #ifdef DEBUG
  Serial.print("HsvColor");
  Serial.print("\nhue:     ");
  Serial.print(HsvColor.h, HEX);
  Serial.print("\nsat:   ");
  Serial.print(HsvColor.s, HEX);
  Serial.print("\nval:    ");
  Serial.print(HsvColor.v, HEX);
  #endif
}


//------------------------------------------------------------------------------
void Debug::print_color_array(RgbColor* colors, int array_size){
  #ifdef DEBUG
  for (int i = 0; i < array_size; ++i)
    print_color(colors[i]);
  #endif
}

//------------------------------------------------------------------------------
void Debug::print_color_array(HsvColor* colors, int array_size){
  #ifdef DEBUG
  for (int i = 0; i < array_size; ++i)
    print_color(colors[i]);
  #endif
}


//------------------------------------------------------------------------------
void print_time(DS3231 clk){
  #ifdef DEBUG

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
  #endif
}


//------------------------------------------------------------------------------
void Debug::print_new_line(){
  #ifdef DEBUG
  Serial.print("\n");
  #endif
}


//------------------------------------------------------------------------------
void Debug::print_labeled_dec(char* label, float num){
  #ifdef DEBUG
  print_new_line();
  Serial.print(label);
  Serial.print(":     ");
  Serial.print(the_hr, DEC);
  #endif
}
