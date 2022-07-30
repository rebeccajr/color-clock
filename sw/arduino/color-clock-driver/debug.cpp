#include <Wire.h>
#include <Arduino.h>
#include "debug.hpp"


//------------------------------------------------------------------------------
void Debug::print_color(RgbColor color){
  Serial.println("");
  Serial.print("r: 0x");
  Serial.print(color.r, HEX);
  Serial.print("  g: 0x");
  Serial.print(color.g, HEX);
  Serial.print("  b: 0x");
  Serial.print(color.b, HEX);
}


//------------------------------------------------------------------------------
void Debug::print_color(HsvColor color){
  Serial.print("\nhue:   ");
  Serial.print(color.h, DEC);
  Serial.print("\nsat:   ");
  Serial.print(color.s, DEC);
  Serial.print("\nval:   ");
  Serial.print(color.v, DEC);
}


//------------------------------------------------------------------------------
void Debug::print_color_array(std::vector<RgbColor> colors){
  for (int i = 0; i < colors.size(); ++i)
    print_color(colors[i]);
}


//------------------------------------------------------------------------------
void Debug::print_color_array(std::vector<HsvColor> colors){
  for (int i = 0; i < colors.size(); ++i)
    print_color(colors[i]);
}


//------------------------------------------------------------------------------
void Debug::print_interval_times(std::vector<float> times){
  for (int i = 0; i < times.size(); ++i)
    Serial.println(times[i]);
}


//------------------------------------------------------------------------------
void Debug::print_time(DS3231 clk){
  bool foo;
  bool bar;

  byte the_hr  = clk.getHour(foo, bar);
  byte the_min = clk.getMinute();
  byte the_sec = clk.getSecond();

  Serial.println("");
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
