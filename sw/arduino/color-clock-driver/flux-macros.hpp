//______________________________________________________________________________
// This file contains the macros used in the ColorClock project
//______________________________________________________________________________

#define ARDUINO_BUILD

#define USING_AW9523
#define USING_DS3231
#define USING_RGB_COLOR
#define USING_HSV_COLOR
#define USING_TIME_CALCS

#define SECONDS_PER_MIN   60.0
#define MINUTES_PER_HOUR  60.0
#define SECONDS_PER_HR    SECONDS_IN_MIN * MINUTES_IN_HOUR 

#define HOURS_PER_DAY      24.0
#define HOURS_PER_MIN     1.0 / MINUTES_PER_HOUR


#include <stdint.h>