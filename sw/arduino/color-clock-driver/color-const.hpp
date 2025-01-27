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
// This file contains constants as related to colors.
//______________________________________________________________________
#ifndef COLOR_CONSTANTS
#define COLOR_CONSTANTS

#include <vector>

#include "hsv-color.hpp"
#include "rgb-color.hpp"


//______________________________________________________________________
class ColorConst
{
 public:

  // RGB constants
  static RgbColor RED;
  static RgbColor YEL;
  static RgbColor GRN;
  static RgbColor CYA;
  static RgbColor BLU;
  static RgbColor MAG;

  static std::vector<RgbColor> roygbiv_;
  static std::vector<RgbColor> vibgyor_;
  static std::vector<RgbColor> rmbcgy_;
  static std::vector<RgbColor> rgb_;

  ColorConst(){};
};

#endif
