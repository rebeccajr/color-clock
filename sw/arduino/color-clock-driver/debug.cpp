#ifndef DEBUG
#include <Arduino.h>
#include <Wire.h>
#endif

#include "debug.hpp"
#include "time-calcs.hpp"


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
  Serial.println("");
  Serial.print("hue:   ");
  Serial.print(color.h, DEC);
  Serial.print("  sat:   ");
  Serial.print(color.s, DEC);
  Serial.print("  val:   ");
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
void Debug::print_interval_times_in_sec(std::vector<float> times){

  Serial.println("");

  for (int i = 0; i < times.size(); i++)
    Serial.println(TimeCalcs::SEC_IN_HR * times[i]);
}


//------------------------------------------------------------------------------
void Debug::print_interval_times(std::vector<float> times){
  for (int i = 0; i < times.size(); i++)
    Serial.println(times[i]);
}


//------------------------------------------------------------------------------
void Debug::print_time(DS3231 clk){
  bool foo;
  bool bar;

  byte the_hr  = clk.getHour(foo, bar);
  byte the_min = clk.getMinute();
  byte the_sec = clk.getSecond();

  Debug::print_new_line();
  Serial.println("---------------------------");
  Serial.print("hour: ");
  Serial.print(the_hr, DEC);
  Serial.print("  min: ");
  Serial.print(the_min, DEC);
  Serial.print("  sec: ");
  Serial.println(the_sec, DEC);
  Serial.println("---------------------------");
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
