//______________________________________________________________________
//      _   __   _   _ _   _   _   _         _
// |   |_| | _  | | | V | | | | / |_/ |_| | /
// |__ | | |__| |_| |   | |_| | \ |   | | | \_
//  _  _         _ ___  _       _ ___   _                        / /
// /  | | |\ |  \   |  | / | | /   |   \                        (**)
// \_ |_| | \| _/   |  | \ |_| \_  |  _/                        (____)o
//______________________________________________________________________
// This file contains the macros used in the ColorClock project
//______________________________________________________________________

//______________________________________________________________________
// TODO need a better way
//______________________________________________________________________
// Used for cpp debug
//______________________________________________________________________
//#define DEBUG_CPP
//#define USING_RGB_COLOR
//#define USING_HSV_COLOR
//______________________________________________________________________


#ifndef DEBUG_CPP
#define ARDUINO_BUILD

#define USING_AW9523
#define USING_DS3231
#define USING_RGB_COLOR
#define USING_HSV_COLOR
#define USING_TIME_CALCS

#define SECONDS_PER_MIN   60.0
#define MINUTES_PER_HOUR  60.0
#define SECONDS_PER_HOUR  (SECONDS_PER_MIN * MINUTES_PER_HOUR )

#define HOURS_PER_DAY     24.0
#define HOURS_PER_MIN     (1.0 / MINUTES_PER_HOUR)

#define IO_EXPANDER_ADDR  0x58
#define LED_BACKPACK_ADDR 0x70
#endif


#include <stdint.h>