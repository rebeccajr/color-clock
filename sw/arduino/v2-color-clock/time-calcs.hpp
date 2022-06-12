//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains the calculations that involve time for ColorClock.
// 
// The ColorClock is a colored light that maps the current time
// to a color. The clock will cycle through a series of colors over a period
// of time. A viewer can tell the approximate time from the color 
// of the light.
//------------------------------------------------------------------------------

#define  TIMECALCS
#ifndef  TIMECALCS

//------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
float get_hrs_since_midnight(byte the_hr, byte the_min, byte the_sec);
float get_time_as_fractional_offset(float time0, float time1, float crnt_time);
void  set_millis_offset(int the_sec);

//------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------
extern int SEC_IN_MIN;
extern int MIN_IN_HR;
extern int SEC_IN_HR;

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------
// variables used to get offset of time in millis
extern int MILLIS_OFFSET;
extern int prev_sec;

#endif
