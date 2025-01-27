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

