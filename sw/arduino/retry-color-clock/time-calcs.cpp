#include "time-calcs.hpp"

int TimeCalcs::SEC_IN_MIN    = 60;
int TimeCalcs::MIN_IN_HR     = 60;
int TimeCalcs::SEC_IN_HR     = SEC_IN_MIN * MIN_IN_HR;

// variables used to get offset of time in millis
int TimeCalcs::MILLIS_OFFSET = 0;
int TimeCalcs::prev_sec      = 0;

//------------------------------------------------------------------------------
// This function calculates the fraction of where a specific time
// falls between two other times.
//
// Assumption:
// time0, time1 and crnt_time are in same units, and crnt_time
// falls between time0 and time1
//
// In the application of ColorClock, time0 and time1 are taken
// from the array of major times.
//------------------------------------------------------------------------------
float TimeCalcs::get_time_as_fractional_offset(
        float time0, float time1, float crnt_time){
  
  // ensure time1 is greater than time0
  // if not, swap
  if (time0 > time1) {
    time0 += time1;
    time1  = time0 - time1;
    time0  = time0 - time1;
  }
  
  float fractional_offset = (crnt_time - time0) / 
                            (time1 - time0);
  
  //print("\nfractional_offset: " + str(fractional_offset));
  
  return fractional_offset;
}

