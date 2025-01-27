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
// This class contains a clock object that is dependent on the hardware
// platform.
//______________________________________________________________________

#ifndef MOCK_FLUX_CLOCK
#define MOCK_FLUX_CLOCK

#include "flux-macros.hpp"


//______________________________________________________________________
class FluxClock
{
 public:
  struct Mock_Clock
  {
    short yr;
    uint8_t month;
    uint8_t day;
    uint8_t hr;
    uint8_t min;
    uint8_t sec;
  };

 public:
  Mock_Clock clock_;

 public:
  FluxClock(){}
  ~FluxClock(){}

  short    get_yr()   { return clock_.yr;     }
  uint8_t  get_month(){ return clock_.month;  }
  uint8_t  get_day()  { return clock_.day;    }
  uint8_t  get_hr()   { return clock_.hr;     }
  uint8_t  get_min()  { return clock_.min;    }
  uint8_t  get_sec()  { return clock_.sec;    }

  int get_milli(uint8_t crnt_sec) {return 0;}

  void set_yr(short val)      { clock_.yr = val;    }
  void set_month(uint8_t val) { clock_.month = val; }
  void set_day(uint8_t val)   { clock_.day = val;   }
  void set_hr(uint8_t val)    { clock_.hr = val;    }
  void set_min(uint8_t val)   { clock_.min = val;   }
  void set_sec(uint8_t val)   { clock_.sec = val;   }
};

#endif
