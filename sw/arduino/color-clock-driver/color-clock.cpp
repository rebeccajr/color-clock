//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------
#include "color-clock.hpp"

RgbColor ColorClock::ABS_RGB_RED = RgbColor(0xFF0000);
RgbColor ColorClock::ABS_RGB_YEL = RgbColor(0xFFFF00);
RgbColor ColorClock::ABS_RGB_GRN = RgbColor(0x00FF00);
RgbColor ColorClock::ABS_RGB_CYA = RgbColor(0x00FFFF);
RgbColor ColorClock::ABS_RGB_BLU = RgbColor(0xFF00FF);
RgbColor ColorClock::ABS_RGB_MAG = RgbColor(0xFF00FF);

std::vector<RgbColor> ColorClock::initialize_default_vector(){
  default_color_selection.push_back(ABS_RGB_RED);
  default_color_selection.push_back(ABS_RGB_YEL);
  default_color_selection.push_back(ABS_RGB_GRN);
  default_color_selection.push_back(ABS_RGB_CYA);
  default_color_selection.push_back(ABS_RGB_BLU);
  default_color_selection.push_back(ABS_RGB_MAG);
};

std::vector<RgbColor> ColorClock::default_color_selection =
  ColorClock::initialize_default_vector();


ColorClock::ColorClock(int num_of_partitions){
  this->partition_count = num_of_partitions;

  color_selection = default_color_selection;

  //----------------------------------------------------------------------------
  float interval_length = this->cycle_time_in_hrs / partition_count;

  // populate color_times
  for (int i = 0; i < partition_count; i++){
    ;//this->color_times[i] = i * interval_length;
    //print times
  }
 
}

ColorClock::ColorClock(){
}

//------------------------------------------------------------------------------
ColorClock::~ColorClock(){
  color_times.clear();
  color_selection.clear();
}


//------------------------------------------------------------------------------
void ColorClock::update_display_time(){
  bool foo;
  bool bar;

  byte the_hr  = the_rtc.getHour(foo, bar);
  byte the_min = the_rtc.getMinute();
  byte the_sec = the_rtc.getSecond();
  
  the_alpha_display.write_display_time(the_hr, the_min, the_sec);
}
