//______________________________________________________________________________
// This class contains a clock object that is dependent on the hardware
// platform.
//______________________________________________________________________________

#ifndef FLUX_CLOCK
#define FLUX_CLOCK
#include "flux-macros.hpp"
#include <stdint.h>

#ifdef USING_DS3231
#include <DS3231.h>
#else
#include <ctime>
#endif


//______________________________________________________________________________
class FluxClock
{
 public:
#ifdef USING_DS3231
  DS3231 rtc_;
#else
  time_t clock_;
#endif

  private:
#ifndef USING_DS3231
  struct tm*  time_;
  int         timezone;
#endif

 public:
  FluxClock(){}
  ~FluxClock(){}

  short get_yr();
  uint8_t  get_month();
  uint8_t  get_day();
  uint8_t  get_hr();
  uint8_t  get_min();
  uint8_t  get_sec();

  int get_milli(uint8_t crnt_sec);

#ifdef USING_DS3231
  void set_yr(short);
  void set_month(uint8_t);
  void set_day(uint8_t);
  void set_hr(uint8_t);
  void set_min(uint8_t);
  void set_sec(uint8_t);
#endif

};

#endif
