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
// This file contains the calculations that involve time for ColorClock.
//
// The ColorClock is a colored light that maps the current time
// to a color. The clock will cycle through a series of colors over a
// period of time. A viewer can tell the approximate time from the color
// of the light.
//______________________________________________________________________

#ifndef TIME_CALCS_HPP
#define TIME_CALCS_HPP


class TimeCalcs {

public:
  //____________________________________________________________________
  // CONSTANTS
  //____________________________________________________________________
  static float SEC_IN_MIN;
  static float MIN_IN_HR;
  static float SEC_IN_HR;
  static float MILLI_IN_HR;

  // variables used to get offset of time in millis
  static int MILLIS_OFFSET;
  static int prev_sec;

  //____________________________________________________________________
  // FUNCTION PROTOTYPES
  //____________________________________________________________________
  static float get_time_as_fractional_offset(
          float time0, float time1, float crnt_time);

  static float get_hrs_since_midnight(
          float hr, float min, float sec, float milli = 0);

};

#endif
