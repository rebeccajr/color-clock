#include "time-calcs.hpp"
#include "debug.hpp"
#include <stdio.h>

//______________________________________________________________________________
// set static variables
//______________________________________________________________________________
float TimeCalcs::SEC_IN_MIN    = 60;
float TimeCalcs::MIN_IN_HR     = 60;
float TimeCalcs::SEC_IN_HR     = SEC_IN_MIN * MIN_IN_HR;
float TimeCalcs::MILLI_IN_HR   = SEC_IN_HR * 1000;

// variables used to get offset of time in millis
int TimeCalcs::MILLIS_OFFSET = 0;
int TimeCalcs::prev_sec      = 0;

//______________________________________________________________________________
// This function calculates the fraction of where a specific time
// falls between two other times.
//
// Assumption:
// time0, time1 and crnt_time are in same units, and crnt_time
// falls between time0 and time1
//
// In the application of ColorClock, time0 and time1 are taken
// from the array of major times.
//______________________________________________________________________________
float TimeCalcs::get_time_as_fractional_offset(
        float time0, float time1, float crnt_time){

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

//______________________________________________________________________________
float TimeCalcs::get_hrs_since_midnight(
          float hr, float min, float sec, float milli){

  return hr + min/MIN_IN_HR + sec/SEC_IN_HR + milli/MILLI_IN_HR;
}
//______________________________________________________________________________
