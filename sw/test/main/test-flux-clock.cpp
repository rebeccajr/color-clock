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
// Unit tests for FluxClock
//______________________________________________________________________

#include "gtest/gtest.h"
#include "flux-clock.hpp"
#include <ctime>

//______________________________________________________________________
// This test was written as proof of concept for the Google Test
// Framework. FluxClock.get_hr() uses ctime when not building for a
// DS3231, so this function is testing ctime against itself.
//______________________________________________________________________
TEST(TimeGroup, CrntHr)
{
  time_t      the_clock;
  struct tm*  the_time;
  int         timezone;

  time(&the_clock);
  the_time = localtime(&the_clock);
  uint8_t hr = static_cast<uint8_t>(the_time->tm_hour);

  FluxClock c;
  ASSERT_TRUE(c.get_hr() == hr);
}
