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
// DESCRIPTION
// This class includes methods to print out statements to the serial
// console for informational and debug purposes
//______________________________________________________________________

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "flux-macros.hpp"

#include <vector>

#ifdef USING_DS3231
  #include <DS3231.h>
#endif

#ifdef USING_HSV_COLOR
#include "hsv-color.hpp"
#endif

#ifdef USING_RGB_COLOR
#include "rgb-color.hpp"
#endif


class Debug
{

public:
  static void print_str_with_new_line(char*, bool = true);
  static void print_labeled_int(char*, int);
  static void print_labeled_float(char*, float);

#ifdef USING_RGB_COLOR
  static void print_color(RgbColor);
  static void print_color_array(std::vector<RgbColor>);
#endif

#ifdef USING_HSV_COLOR
  static void print_color(HsvColor);
  static void print_color_array(std::vector<HsvColor>);
#endif

  static void print_interval_times(std::vector<float>);
  static void print_interval_times_in_sec(std::vector<float>);
  static void print_new_line();

  static void print_time(
#ifdef USING_DS3231
    DS3231
#endif
  );

  static void print_proof_of_life(char*);
};

#endif
