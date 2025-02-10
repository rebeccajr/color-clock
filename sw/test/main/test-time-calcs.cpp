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
// Unit tests for TimeCalcs
//______________________________________________________________________

#include "gtest/gtest.h"
#include "time-calcs.hpp"


//______________________________________________________________________
TEST(TimeCalcsGroup, TimeAsFractionalOffset_Nominal)
{
  float function_output = TimeCalcs::get_time_as_fractional_offset(
    12, 16, 15
  );

  ASSERT_TRUE(function_output == 0.75);
}


//______________________________________________________________________
// Inputs are swapped
//______________________________________________________________________
TEST(TimeCalcsGroup, TimeAsFractionalOffset_Nominal_Swapped)
{
  float function_output = TimeCalcs::get_time_as_fractional_offset(
    16, 12, 15
  );

  ASSERT_TRUE(function_output == 0.75);
}


//______________________________________________________________________
// Index times have one before and one after midnight.
// TODO: Fix function, this test currently fails.
//______________________________________________________________________
TEST(TimeCalcsGroup, TimeAsFractionalOffset_Across_Midnight)
{
  float function_output = TimeCalcs::get_time_as_fractional_offset(
    1, 23, 0.5
  );

  ASSERT_TRUE(function_output == 0.75);
}


//______________________________________________________________________
// Last index time is midnight, marked as hour 24.
//______________________________________________________________________
TEST(TimeCalcsGroup, TimeAsFractionalOffset_Midnight_As_24_End)
{
  float function_output = TimeCalcs::get_time_as_fractional_offset(
    23, 24, 23.5
  );

    ASSERT_TRUE(function_output == 0.5);
}

//______________________________________________________________________
// Last index time is midnight, marked as hour 0.
// TODO: Fix function, this test currently fails.
//______________________________________________________________________
TEST(TimeCalcsGroup, TimeAsFractionalOffset_Midnight_As_0_End)
{
  float function_output = TimeCalcs::get_time_as_fractional_offset(
    23, 0, 23.5
  );

    ASSERT_TRUE(function_output == 0.5);
}

//  static float get_hrs_since_midnight(
//          float hr, float min, float sec, float milli = 0);
