//______________________________________________________________________________
// DESCRIPTION
// This file contains the calculations that involve time for ColorClock.
// 
// The ColorClock is a colored light that maps the current time
// to a color. The clock will cycle through a series of colors over a period
// of time. A viewer can tell the approximate time from the color 
// of the light.
//______________________________________________________________________________

#ifndef TIME_CALCS_HPP
#define TIME_CALCS_HPP


class TimeCalcs {

public:
  //----------------------------------------------------------------------------
  // CONSTANTS
  //----------------------------------------------------------------------------
  static float SEC_IN_MIN;
  static float MIN_IN_HR;
  static float SEC_IN_HR;
  
  // variables used to get offset of time in millis
  static int MILLIS_OFFSET;
  static int prev_sec;
  
  //----------------------------------------------------------------------------
  // FUNCTION PROTOTYPES
  //----------------------------------------------------------------------------
  
  static float get_time_as_fractional_offset(
          float time0, float time1, float crnt_time);

  static float get_hrs_since_midnight(
          float hr, float min, float sec);
  
};

#endif
