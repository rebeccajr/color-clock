#ifndef RGB_COLOR
#define RGB_COLOR

#include <algorithm>
#include <cmath>
#include <map>
#include <stdint.h>
#include <vector>

#include <stdio.h>

#include "flux-macros.hpp"

#define MAX_RGB_VAL 0xFF
#define MIN_RGB_VAL 0
#define DEFAULT_MOD_AMT 0x20

#ifdef USING_HSV_COLOR
class HsvColor;
#endif

class RgbColor
{
public:
  enum class PriColor
  { RED
    , GRN
    , BLU
  };

  enum class IncDec 
  { DECREMENT
    , INC
  };

  static std::map <PriColor, short> create_rgb_pin_map(short, short, short);

  std::map <PriColor, int> rgb_; 

  uint8_t max_red_;
  uint8_t max_grn_;
  uint8_t max_blu_;
  uint8_t min_red_;
  uint8_t min_grn_;
  uint8_t min_blu_;

  uint8_t mod_amt_;
  
  RgbColor(){}

  // values normalized to 255
  RgbColor(int red, int green, int blue){
  
    set_min_max(MIN_RGB_VAL, MAX_RGB_VAL);

    mod_amt_ = DEFAULT_MOD_AMT;
    
    rgb_.insert({PriColor::RED, red});
    rgb_.insert({PriColor::GRN, green});
    rgb_.insert({PriColor::BLU, blue});
  }

  // TODO reduce duplication
  RgbColor(int rgb_hex
  )
  {
    int r = (rgb_hex & 0xFF0000) >> 16;
    int g = (rgb_hex & 0x00FF00) >> 8;
    int b = (rgb_hex & 0x0000FF);

    rgb_.insert({PriColor::RED, r});
    rgb_.insert({PriColor::GRN, g});
    rgb_.insert({PriColor::BLU, b});

    mod_amt_ = DEFAULT_MOD_AMT;
  }



  void set_min_max(int max_red
    , uint8_t max_grn
    , uint8_t max_blu
    , uint8_t min_red
    , uint8_t min_grn
    , uint8_t min_blu
  );

  void set_min_max(int min_val, int max_val);

  void bounds_check();

#ifdef USING_HSV_COLOR
  HsvColor to_hsv();
#endif

  void mod_color(PriColor, IncDec); 

  void write_rgb_to_out(int, int, int, bool = false);
};


#endif

