//______________________________________________________________________
//______________________________________________________________________
//      _   __   _   _ _   _   _   _         _
// |   |_| | _  | | | V | | | | / |_/ |_| | /
// |__ | | |__| |_| |   | |_| | \ |   | | | \_
//  _  _         _ ___  _       _ ___   _                        / /
// /  | | |\ |  \   |  | / | | /   |   \                        (^^)
// \_ |_| | \| _/   |  | \ |_| \_  |  _/                        (____)o
//______________________________________________________________________
//______________________________________________________________________
//
//----------------------------------------------------------------------
// Copyright 2024, Rebecca Rashkin
// -------------------------------
// This code may be copied, redistributed, transformed, or built upon in
// any format for educational, non-commercial purposes.
//
// Please give me appropriate credit should you choose to use this
// resource. Thank you :)
//----------------------------------------------------------------------
//
//______________________________________________________________________
// //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\
//______________________________________________________________________
//______________________________________________________________________
// Implementation of Debug functions.
//______________________________________________________________________
//#define ARDUINO_BUILD // just here so IDE doesn't complain
#include "debug.hpp"

#ifdef ARDUINO_BUILD
# include <Arduino.h>
# include <Wire.h>
#endif

#include <stdio.h>
#include <stdint.h>

#ifdef USING_TIME_CALCS
# include "time-calcs.hpp"
#endif


#ifdef USING_RGB_COLOR
//______________________________________________________________________
void Debug::print_color(RgbColor color)
{
#ifdef ARDUINO_BUILD
  Serial.print("r: 0x");
  Serial.print(color.rgb_[RgbColor::PriColor::RED], HEX);
  Serial.print("  g: 0x");
  Serial.print(color.rgb_[RgbColor::PriColor::GRN], HEX);
  Serial.print("  b: 0x");
  Serial.println(color.rgb_[RgbColor::PriColor::BLU], HEX);
#else
  printf("r: 0x%02X  g: 0x%02X  b: 0x%02X"
    , color.rgb_[RgbColor::PriColor::RED]
    , color.rgb_[RgbColor::PriColor::GRN]
    , color.rgb_[RgbColor::PriColor::BLU]
  );
#endif
}
#endif


#ifdef USING_HSV_COLOR
//______________________________________________________________________
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
  printf("hue: 0x%3.4f  sat: 0x%3.4f  val: 0x%3.4f"
    , color.h, color.s, color.v);
#endif
}
#endif


#ifdef USING_RGB_COLOR
//______________________________________________________________________
// Prints each aspect of color in array.
// TODO make template
//______________________________________________________________________
void Debug::print_color_array(std::vector<RgbColor> colors)
{
  for (int i = 0; i < colors.size(); ++i)
  {
    print_new_line();
    print_color(colors[i]);
  }
}
#endif


#ifdef USING_HSV_COLOR
//______________________________________________________________________
void Debug::print_color_array(std::vector<HsvColor> colors)
{
  for (int i = 0; i < colors.size(); ++i)
  {
    print_new_line();
    print_color(colors[i]);
  }
}
#endif


//______________________________________________________________________
void Debug::print_interval_times_in_sec(std::vector<float> times)
{

  print_new_line();

  for (int i = 0; i < times.size(); i++)
#if defined(ARDUINO_BUILD) && defined(USING_TIME_CALCS)
    Serial.println(TimeCalcs::SEC_IN_HR * times[i]);
#else
    printf("%f\n", times[i]);
#endif
}


//______________________________________________________________________
void Debug::print_interval_times(std::vector<float> times)
{
  for (int i = 0; i < times.size(); i++)
#ifdef ARDUINO_BUILD
    Serial.println(times[i] * 1000);
#else
    printf("%f\n", times[i] * 1000);
#endif
}


//______________________________________________________________________
// TODO rewrite for non-Arduino build
//______________________________________________________________________
void Debug::print_time(
#ifdef USING_DS3231
  DS3231 clk
#endif
  )
{
  bool foo;
  bool bar;

  uint8_t the_hr;
  uint8_t the_min;
  uint8_t the_sec;

#ifdef USING_DS3231
  the_hr  = clk.getHour(foo, bar);
  the_min = clk.getMinute();
  the_sec = clk.getSecond();
#endif

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


//______________________________________________________________________
void Debug::print_new_line()
{
#ifdef ARDUINO_BUILD
  Serial.print("\n");
#else
  printf("\n");
#endif
}


//______________________________________________________________________
// Prints value with label in decimal. Does not include new line at end.
//______________________________________________________________________
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


//______________________________________________________________________
// Prints value with label in decimal. Does not include new line at end.
//______________________________________________________________________
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


//______________________________________________________________________
// Prints a string to the console
//______________________________________________________________________
void Debug::print_str_with_new_line(char* str, bool print_new_line)
{
#ifdef ARDUINO_BUILD
  Serial.print(str);
#else
  printf("%s", str);
#endif
  if(print_new_line)
    Debug::print_new_line();
}


//______________________________________________________________________
// Prints a string to the console every second.
// Currently only valid for Arduino builds.
//______________________________________________________________________
void Debug::print_proof_of_life(char* str)
{
#ifdef ARDUINO_BUILD
static unsigned long prev_milli = 0;
unsigned long crnt_milli = millis();

if(crnt_milli - prev_milli > 1000)
{
  print_new_line();
  print_str_with_new_line("Proof of life");
  prev_milli = crnt_milli;
}

#endif

}