//______________________________________________________________________________
// This file contains constants as related to colors.
//______________________________________________________________________________
#ifndef COLOR_CONSTANTS
#define COLOR_CONSTANTS

#include <vector>

#include "hsv-color.hpp"
#include "rgb-color.hpp"

class ColorConstants
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

  ColorConstants(){};

};

#endif
