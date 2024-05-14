//______________________________________________________________________________
// This class contains a clock object that is dependent on the hardware
// platform.
//______________________________________________________________________________

#ifndef FLUX_CLOCK
#define FLUX_CLOCK

#ifdef ARDUINO_BUILD
#include <DS3231.h>
#else
#include <ctime>
#endif

using byte = unsigned char;


class FluxClock
{
 public:
#ifdef ARDUINO_BUILD
  DS3231 rtc_;
#else
  time_t      clock_;
#endif

  private:
#ifndef ARDUINO_BUILD
  struct tm*  time_;
  int         timezone;
#endif

 public:
  FluxClock(){}
  ~FluxClock(){}

  short get_yr();
  byte  get_month();
  byte  get_day();
  byte  get_hr();
  byte  get_min();
  byte  get_sec();

#ifdef ARDUINO_BUILD
  void set_yr(short);
  void set_month(byte);
  void set_day(byte);
  void set_hr(byte);
  void set_min(byte);
  void set_sec(byte);
#endif

};

#endif
