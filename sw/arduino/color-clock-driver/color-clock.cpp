//------------------------------------------------------------------------------
// Implementation of ColorClock functions
//------------------------------------------------------------------------------
#include "color-clock.hpp"
#include "classes.hpp"

RgbColor ColorClock::RED = RgbColor(0xFF0000);
RgbColor ColorClock::YEL = RgbColor(0xFFFF00);
RgbColor ColorClock::GRN = RgbColor(0x00FF00);
RgbColor ColorClock::CYA = RgbColor(0x00FFFF);
RgbColor ColorClock::BLU = RgbColor(0xFF00FF);
RgbColor ColorClock::MAG = RgbColor(0xFF00FF);

std::vector<RgbColor> ColorClock::initialize_default_vector(){
  default_color_selection.push_back(RED);
  default_color_selection.push_back(YEL);
  default_color_selection.push_back(GRN);
  default_color_selection.push_back(CYA);
  default_color_selection.push_back(BLU);
  default_color_selection.push_back(MAG);
};

std::vector<RgbColor> ColorClock::default_color_selection =
  ColorClock::initialize_default_vector();


//------------------------------------------------------------------------------
// args: cycle_time_in_hrs_
//       colors - vector of main colors
ColorClock::ColorClock(DS3231* rtc
  , float cycle_time_in_hrs
  , std::vector<RgbColor> colors){

    rtc_ = rtc;

  partition_count_   = colors.size();
  cycle_time_in_hrs = cycle_time_in_hrs_;

  color_selection_ = colors;

  float interval_length = cycle_time_in_hrs_ / partition_count_;

  // populate color_times_
  for (int i = 0; i < partition_count_; i++){
    color_times_.push_back(i * interval_length);
  }
}

ColorClock::ColorClock(){
}


//------------------------------------------------------------------------------
ColorClock::~ColorClock(){
  color_times_.clear();
  color_selection_.clear();
}


//------------------------------------------------------------------------------
// Gets current time from RTC module and maps to an RGB color
RgbColor ColorClock::time_to_color()
{
  // placeholders for getHour function for RTC
  bool foo;
  bool bar;

  float the_hr  = (float) rtc_->getHour(foo, bar);
  float the_min = (float) rtc_->getMinute();
  float the_sec = (float) rtc_->getSecond();

  float hrs_since_midnight =
    TimeCalcs::get_hrs_since_midnight(the_hr, the_min, the_sec);

  float hrs_since_cycle_restart =
    fmod(hrs_since_midnight, cycle_time_in_hrs_);

  // error handling
  if (hrs_since_cycle_restart < 0) hrs_since_cycle_restart = 0;

  determine_color_indices(hrs_since_cycle_restart);

  float fraction =
    TimeCalcs::get_time_as_fractional_offset(color_times_[lo_color_index_]
      , color_times_[hi_color_index]
      , hrs_since_cycle_restart);

  // convert colors from main_colors array to hsv
  // for smoother transitions between colors
  HsvColor hsvcolor0 = color_selection_[lo_color_index_].to_hsv();
  HsvColor hsvcolor1 = color_selection_[hi_color_index].to_hsv();

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
  while (time >= color_times_[i]){

    if (time == color_times_[i]){
      lo_color_index_ = i;
      hi_color_index = i;
    }

    if (i < color_times_.size()- 1)
      i++;
    else
      break;

  lo_color_index_ = i - 1;
  hi_color_index = i;
  }

}


//------------------------------------------------------------------------------
// Updates the alphanumeric display with the time
void ColorClock::update_display_time(){
  bool foo;
  bool bar;

  byte the_hr  = rtc_->getHour(foo, bar);
  byte the_min = rtc_->getMinute();
  byte the_sec = rtc_->getSecond();

  //time_display_.write_disp_time(the_hr, the_min, the_sec);
}
