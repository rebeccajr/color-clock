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
#include "time-calcs.hpp"
#include "debug.hpp"
#include <stdio.h>

//______________________________________________________________________
// set static variables
//______________________________________________________________________
float TimeCalcs::SEC_IN_MIN    = 60;
float TimeCalcs::MIN_IN_HR     = 60;
float TimeCalcs::SEC_IN_HR     = SEC_IN_MIN * MIN_IN_HR;
float TimeCalcs::MILLI_IN_HR   = SEC_IN_HR * 1000;

// variables used to get offset of time in millis
int TimeCalcs::MILLIS_OFFSET = 0;
int TimeCalcs::prev_sec      = 0;

//______________________________________________________________________
// This function calculates the fraction of where a specific time
// falls between two other times.
//
// Assumption:
// time0, time1 and crnt_time are in same units, and crnt_time
// falls between time0 and time1
//
// In the application of ColorClock, time0 and time1 are taken
// from the array of major times.
//______________________________________________________________________
float TimeCalcs::get_time_as_fractional_offset(
        float time0, float time1, float crnt_time){

  if (time0 == time1)
    return 0;

  // ensure time1 is greater than time0
  // if not, swap
  if (time0 > time1) {
    time0 += time1;
    time1  = time0 - time1;
    time0  = time0 - time1;
  }

  float fractional_offset = static_cast<float>(
    (crnt_time - time0) /
    (time1 - time0)
  );

  return fractional_offset;
}

//______________________________________________________________________
float TimeCalcs::get_hrs_since_midnight(
          float hr, float min, float sec, float milli){

  return hr + min/MIN_IN_HR + sec/SEC_IN_HR + milli/MILLI_IN_HR;
}
