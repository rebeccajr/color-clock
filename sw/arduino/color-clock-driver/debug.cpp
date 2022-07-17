#include <Wire.h>
#include <Arduino.h>
#include "debug.hpp"


//------------------------------------------------------------------------------
void Debug::print_color(RgbColor color){
  Serial.println("RgbColor");
  Serial.println("\nred:     ");
  Serial.println(color.r, HEX);
  Serial.println("\ngreen:   ");
  Serial.println(color.g, HEX);
  Serial.println("\nblue:    ");
  Serial.println(color.b, HEX);
}


//------------------------------------------------------------------------------
void Debug::print_color(HsvColor color){
  Serial.println("HsvColor");
  Serial.println("\nhue:     ");
  Serial.println(color.h, DEC);
  Serial.println("\nsat:   ");
  Serial.println(color.s, DEC);
  Serial.println("\nval:    ");
  Serial.println(color.v, DEC);
}


//------------------------------------------------------------------------------
void Debug::print_color_array(RgbColor* colors, int array_size){
  for (int i = 0; i < array_size; ++i)
    print_color(colors[i]);
}

//------------------------------------------------------------------------------
void Debug::print_color_array(HsvColor* colors, int array_size){
  for (int i = 0; i < array_size; ++i)
    print_color(colors[i]);
}


//------------------------------------------------------------------------------
void Debug::print_time(DS3231 clk){
  bool foo;
  bool bar;

  byte the_hr  = clk.getHour(foo, bar);
  byte the_min = clk.getMinute();
  byte the_sec = clk.getSecond();

  Serial.println("---------------------------");
  Serial.println(" Time");
  Serial.println("---------------------------");

  Serial.println("hour:  ");
  Serial.println(the_hr, DEC);
  Serial.println(" ");
  Serial.println("min:   ");
  Serial.println(the_min, DEC);
  Serial.println(" ");
  Serial.println("sec:   ");
  Serial.println(the_sec, DEC);
}


//------------------------------------------------------------------------------
void Debug::print_new_line(){
  Serial.print("\n");
}


//------------------------------------------------------------------------------
void Debug::print_labeled_dec(char* label, float num){
  Serial.println(label);
  Serial.print(":     ");
  Serial.print(num, DEC);
}
