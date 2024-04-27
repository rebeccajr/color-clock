//______________________________________________________________________________
// This file contains constants as related to colors.
//______________________________________________________________________________

#include <vector>

#include "color-const.hpp"

RgbColor ColorConstants::RED = RgbColor(0xFF0000);
RgbColor ColorConstants::YEL = RgbColor(0xFFFF00);
RgbColor ColorConstants::GRN = RgbColor(0x00FF00);
RgbColor ColorConstants::CYA = RgbColor(0x00FFFF);
RgbColor ColorConstants::BLU = RgbColor(0x0000FF);
RgbColor ColorConstants::MAG = RgbColor(0xFF00FF);


std::vector<RgbColor> ColorConstants::roygbiv_ = {RED
  , YEL
  , GRN
  , CYA
  , BLU
  , MAG
  };


std::vector<RgbColor> ColorConstants::vibgyor_ = {MAG
  , BLU
  , CYA
  , GRN
  , YEL
  , RED
  };


std::vector<RgbColor> ColorConstants::rmbcgy_ = {RED
  , MAG
  , BLU
  , CYA
  , GRN
  , YEL
  };

