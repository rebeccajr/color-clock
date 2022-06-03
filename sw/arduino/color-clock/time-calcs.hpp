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
int SEC_IN_MIN    = 60;
int MIN_IN_HR     = 60;
int SEC_IN_HR     = SEC_IN_MIN * MIN_IN_HR;


// variables used to get offset of time in millis
int MILLIS_OFFSET = 0;
int prev_sec      = 0;
//------------------------------------------------------------------------------
// Returns current time in units of hours since midnight
//------------------------------------------------------------------------------
float get_hrs_since_midnight(byte the_hr, byte the_min, byte the_sec) {
  
  set_millis_offset(the_sec);
  
  float ms = (millis() - MILLIS_OFFSET) % 1000;
  
  float  sec_since_midnight   
    = (SEC_IN_MIN * (the_hr * MIN_IN_HR + the_min) + 
       the_sec + ms / 1000);

  float  hours_since_midnight 
    = (sec_since_midnight/(1.0 * SEC_IN_HR));    
  return hours_since_midnight;
}


//--------------------------------------------------------------
// This function calculates the fraction of where a specific time
// falls between two other times.
//
// Assumption:
// time0, time1 and crnt_time are in same units, and crnt_time
// falls between time0 and time1
//
// In the application of ColorClock, time0 and time1 are taken
// from the array of major times.
//--------------------------------------------------------------
float get_time_as_fractional_offset(float time0, 
                                    float time1, 
                                    float crnt_time){
  
  // ensure time1 is greater than time0
  // if not, swap
  if (time0 > time1) {
    
    time0 += time1;
    time1  = time0 - time1;
    time0  = time0 - time1;
    
  }
  
  float fractional_offset    = (crnt_time - time0) / 
                               (time1 - time0);
  
  //print("\nfractional_offset: " + str(fractional_offset));
  
  return fractional_offset;
}

//------------------------------------------------------------------------------
// The function millis() returns the number of milliseconds
// since the beginning of program execution, while the functions
// second(), minute(), and hour() return the current second,
// minute, and hour of the day, respectively.
//
// The functon millis() is not coordinated with the time of day,
// so the following function, set_millis_offset is used to
// align the return value of millis() with the time of day.
//
// Every time a second passes, the millisecond offset between
// when the program started and the start of the last second
// is recalculated.
// 
// This function does not determine the precise millisecond of
// the current time, however, it suits the purposes of this
// program in that milliseconds will increase for the duration
// of a second in time, and then reset.
//------------------------------------------------------------------------------
void set_millis_offset(int the_sec){
  
  // check if beginning of new second
  if (prev_sec != the_sec){    
    MILLIS_OFFSET = millis();
  }
  
    prev_sec = the_sec;  
}

#endif
