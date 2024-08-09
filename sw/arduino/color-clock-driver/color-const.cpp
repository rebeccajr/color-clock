//______________________________________________________________________________
// This file contains constants as related to colors.
//______________________________________________________________________________

#include <vector>

#include "color-const.hpp"

RgbColor ColorConst::RED = RgbColor(0xFF0000);
RgbColor ColorConst::YEL = RgbColor(0xFFFF00);
RgbColor ColorConst::GRN = RgbColor(0x00FF00);
RgbColor ColorConst::CYA = RgbColor(0x00FFFF);
RgbColor ColorConst::BLU = RgbColor(0x0000FF);
RgbColor ColorConst::MAG = RgbColor(0xFF00FF);


std::vector<RgbColor> ColorConst::rgb_ = {RED
  , GRN
  , BLU
  };

std::vector<RgbColor> ColorConst::roygbiv_ = {RED
  , YEL
  , GRN
  , CYA
  , BLU
  , MAG
  };


std::vector<RgbColor> ColorConst::vibgyor_ = {MAG
  , BLU
  , CYA
  , GRN
  , YEL
  , RED
  };


std::vector<RgbColor> ColorConst::rmbcgy_ = {RED
  , MAG
  , BLU
  , CYA
  , GRN
  , YEL
  };

