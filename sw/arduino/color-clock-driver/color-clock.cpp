//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#include "color-clock.hpp"
#include "classes.hpp"

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


//------------------------------------------------------------------------------
// args: cycle_time_in_hrs
//       colors - vector of main colors
ColorClock::ColorClock(
  float cycle_time_in_hrs,
  std::vector<RgbColor> colors){

  this->partition_count   = colors.size();
  this->cycle_time_in_hrs = cycle_time_in_hrs;

  this->color_selection = colors;

  float interval_length = this->cycle_time_in_hrs / this->partition_count;

  // populate color_times
  for (int i = 0; i < this->partition_count; i++){
    this->color_times.push_back(i * interval_length);
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
// Gets current time from RTC module and maps to an RGB color
RgbColor ColorClock::time_to_color()
{
  // placeholders for getHour function for RTC
  bool foo;
  bool bar;

  float the_hr  = (float) the_rtc.getHour(foo, bar);
  float the_min = (float) the_rtc.getMinute();
  float the_sec = (float) the_rtc.getSecond();

  float hrs_since_midnight =
    TimeCalcs::get_hrs_since_midnight(the_hr, the_min, the_sec);

  float hrs_since_cycle_restart =
    fmod(hrs_since_midnight, cycle_time_in_hrs);

  // error handling
  if (hrs_since_cycle_restart < 0) hrs_since_cycle_restart = 0;

  determine_color_indices(hrs_since_cycle_restart);

  float fraction =
    TimeCalcs::get_time_as_fractional_offset(color_times[lo_color_index],
                                  color_times[hi_color_index],
                                  hrs_since_cycle_restart);

  // convert colors from main_colors array to hsv
  // for smoother transitions between colors
  HsvColor hsvcolor0 = color_selection[lo_color_index].to_hsv();
  HsvColor hsvcolor1 = color_selection[hi_color_index].to_hsv();

  HsvColor crnt_hsvcolor_time =
    HsvColor::interpolate_bet_hsvcolors(hsvcolor0, hsvcolor1, fraction);

  Debug::print_color(crnt_hsvcolor_time);
  Debug::print_color(crnt_hsvcolor_time.to_rgb());

  // convert hsv to rgb in order to display properly
  return crnt_hsvcolor_time.to_rgb();
}


//------------------------------------------------------------------------------
// Determines the indices of the color times that the current
// time falls between.
//
// assumption:
// color times are in order
//------------------------------------------------------------------------------
void ColorClock::determine_color_indices(float time)
{

  int i = 0;
  while (time >= color_times[i]){

    if (time == color_times[i]){
      lo_color_index = i;
      hi_color_index = i;
    }

    if (i < color_times.size()- 1)
      i++;
    else
      break;

  lo_color_index = i - 1;
  hi_color_index = i;
  }

}


//------------------------------------------------------------------------------
// Updates the alphanumeric display with the time
void ColorClock::update_display_time(){
  bool foo;
  bool bar;

  byte the_hr  = the_rtc.getHour(foo, bar);
  byte the_min = the_rtc.getMinute();
  byte the_sec = the_rtc.getSecond();

  //the_alpha_display.write_disp_time(the_hr, the_min, the_sec);
}
