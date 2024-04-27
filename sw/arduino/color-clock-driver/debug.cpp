//______________________________________________________________________________
// Implementation of Debug functions.
//______________________________________________________________________________
//#define ARDUINO_BUILD // just here so IDE doesn't complain
#ifdef ARDUINO_BUILD 
# include <Arduino.h>
# include <Wire.h>
#endif

#include <stdio.h>

#include "debug.hpp"
#include "time-calcs.hpp"


//______________________________________________________________________________
void Debug::print_color(RgbColor color)
{
#ifdef ARDUINO_BUILD
  Serial.print("r: 0x");
  Serial.print(color.r, HEX);
  Serial.print("  g: 0x");
  Serial.print(color.g, HEX);
  Serial.print("  b: 0x");
  Serial.println(color.b, HEX);
#else
  printf("r: 0x%02X  g: 0x%02X  b: 0x%02X", color.r, color.g, color.b);
#endif
}


//______________________________________________________________________________
void Debug::print_color(HsvColor color)
{
#ifdef ARDUINO_BUILD
  Serial.print("hue:   ");
  Serial.print(color.h, DEC);
  Serial.print("  sat:   ");
  Serial.print(color.s, DEC);
  Serial.print("  val:   ");
  Serial.println(color.v, DEC);
#else

  printf("hue: 0x%3.4f  sat: 0x%3.4f  val: 0x%3.4f", color.h, color.s, color.v);
#endif
}


//______________________________________________________________________________
// Prints each aspect of color in array.
// TODO make template
//______________________________________________________________________________
void Debug::print_color_array(std::vector<RgbColor> colors)
{
  for (int i = 0; i < colors.size(); ++i)
    print_color(colors[i]);
}


//______________________________________________________________________________
void Debug::print_color_array(std::vector<HsvColor> colors)
{
  for (int i = 0; i < colors.size(); ++i)
    print_color(colors[i]);
}


//______________________________________________________________________________
void Debug::print_interval_times_in_sec(std::vector<float> times)
{

  print_new_line(); 

  for (int i = 0; i < times.size(); i++)
#ifdef  ARDUINO_BUILD
    Serial.println(TimeCalcs::SEC_IN_HR * times[i] * 1000);
#else
    printf("%f\n", times[i]);
#endif
}


//______________________________________________________________________________
void Debug::print_interval_times(std::vector<float> times)
{
  for (int i = 0; i < times.size(); i++)
#ifdef ARDUINO_BUILD
    Serial.println(times[i] * 1000);
#else
    printf("%f\n", times[i] * 1000);
#endif
}


//______________________________________________________________________________
// TODO rewrite for non-Arduino build
//______________________________________________________________________________
#ifdef ARDUINO_BUILD
void Debug::print_time(DS3231 clk)
{
  bool foo;
  bool bar;

  byte the_hr  = clk.getHour(foo, bar);
  byte the_min = clk.getMinute();
  byte the_sec = clk.getSecond();

  print_new_line();
#ifdef ARDUINO_BUILD
  Serial.println("---------------------------");
  Serial.print("hour: ");
  Serial.print(the_hr, DEC);
  Serial.print("  min: ");
  Serial.print(the_min, DEC);
  Serial.print("  sec: ");
  Serial.println(the_sec, DEC);
  Serial.println("---------------------------");
#endif
}
#endif


//______________________________________________________________________________
void Debug::print_new_line()
{
#ifdef ARDUINO_BUILD
  Serial.print("\n");
#else
  printf("\n");
#endif
}


//______________________________________________________________________________
// Prints value with label in decimal. Does not include new line at end.
//______________________________________________________________________________
void Debug::print_labeled_float(char* label, float num)
{
  Debug::print_new_line();
#ifdef ARDUINO_BUILD
  Serial.print(label);
  Serial.print(num, DEC);
#else
  printf("%s:  %f", label, num);
#endif
}


//______________________________________________________________________________
// Prints value with label in decimal. Does not include new line at end.
//______________________________________________________________________________
void Debug::print_labeled_int(char* label, int num)
{
  Debug::print_new_line();
#ifdef ARDUINO_BUILD
  Serial.print(label);
  Serial.print(num);
#else
  printf("%s:  %d", label, num);
#endif
}


//______________________________________________________________________________
// Prints a string to the console
//______________________________________________________________________________
void Debug::print_string_with_new_line(char* str, bool print_new_line)
{
#ifdef ARDUINO_BUILD
  Serial.print(str);
#else
  printf("%s", str);
#endif
  if(print_new_line)
    Debug::print_new_line();
}
