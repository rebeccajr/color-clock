//______________________________________________________________________________
// Implementation of ColorClock functions
//______________________________________________________________________________
#include "color-classes.hpp"
#include "color-clock.hpp"

#include "debug.hpp"

ColorClock::ColorClock(FluxClock* the_clock 
  , double cycle_time_in_hrs
  , std::vector<RgbColor> colors
  )
  : clock_(the_clock)
  {
    // color_times_ contains the times associated w/ color_selection_ elements
    // There is a 1:1 mapping between these two vectors
    color_selection_ = colors;
    color_selection_.push_back(*color_selection_.begin());
    set_cycle_time(cycle_time_in_hrs);
  }


//______________________________________________________________________________
// Set cycle time and caclulate color times.
//______________________________________________________________________________
void ColorClock::set_cycle_time(double cycle_time_in_hrs)
{
    cycle_time_in_hrs_ = cycle_time_in_hrs;

    color_times_.clear();

    int   partition_count = color_selection_.size() - 1;
    float interval_length = cycle_time_in_hrs_ / partition_count;

    for (int i = 0; i <= partition_count; i++)
      color_times_.push_back(i * interval_length);
}

//______________________________________________________________________________
void ColorClock::print()
{
  Debug::print_string_with_new_line("_________________");
  Debug::print_string_with_new_line(" Color Selection");
  Debug::print_string_with_new_line("_________________");
  Debug::print_color_array(color_selection_);
  Debug::print_new_line();
  Debug::print_string_with_new_line("_________________");
  Debug::print_string_with_new_line(" Interval Times");
  Debug::print_string_with_new_line("_________________");
  Debug::print_labeled_int("size of color times: ", color_times_.size());
  Debug::print_interval_times_in_sec(color_times_);
}
//______________________________________________________________________________


//______________________________________________________________________________
// Gets current time from RTC module and maps to an RGB color
//______________________________________________________________________________
RgbColor ColorClock::time_to_color()
{
  // TODO Modify so that cycle time can be longer than one day
  float the_hr    = (float) clock_->get_hr();
  float the_min   = (float) clock_->get_min();
  float the_sec   = (float) clock_->get_sec();
  float the_milli = (float) clock_->get_milli(the_sec);

  float hrs_since_midnight =
    TimeCalcs::get_hrs_since_midnight(the_hr, the_min, the_sec, the_milli);

  float hrs_since_cycle_restart =
    fmod(hrs_since_midnight, cycle_time_in_hrs_);

  // error handling
  if (hrs_since_cycle_restart < 0) hrs_since_cycle_restart = 0;

  determine_color_indices(hrs_since_cycle_restart);

  float fraction =
    TimeCalcs::get_time_as_fractional_offset(color_times_[lo_color_index_]
      , color_times_[hi_color_index_]
      , hrs_since_cycle_restart);

  static float prev_fraction = 0;
  static int count = 0;
 
  // convert colors from main_colors array to hsv
  // for smoother transitions between colors
  HsvColor hsvcolor0 = color_selection_[lo_color_index_].to_hsv();
  HsvColor hsvcolor1 = color_selection_[hi_color_index_].to_hsv();

  HsvColor crnt_hsvcolor_time =
    HsvColor::interpolate_bet_hsvcolors(hsvcolor0, hsvcolor1, fraction);

  prev_fraction = fraction;

  //____________________________________________________________________________
  // Debug
  //____________________________________________________________________________
  //Debug::print_color(crnt_hsvcolor_time);
  //Debug::print_color(crnt_hsvcolor_time.to_rgb());
  //____________________________________________________________________________

  // convert hsv to rgb in order to display properly

  /*
  //____________________________________________________________________________
  // Debug
  //____________________________________________________________________________
  RgbColor out_color = crnt_hsvcolor_time.to_rgb();

  static short prev_red_val;
  static short prev_grn_val;
  static short prev_blu_val;
  if ( prev_red_val != out_color.r 
    || prev_grn_val != out_color.g
    || prev_blu_val != out_color.b
  )
  {
    Debug::print_new_line();
    Debug::print_color(out_color);
    Debug::print_new_line();
  }

  prev_red_val = out_color.r;
  prev_grn_val = out_color.g;
  prev_blu_val = out_color.b;
  //____________________________________________________________________________
  */

  return crnt_hsvcolor_time.to_rgb();
}


//______________________________________________________________________________
// Determines the indices of the color times that the current
// time falls between.
//
// assumption:
// color times are in order
//______________________________________________________________________________
void ColorClock::determine_color_indices(float time)
{

  int i = 0;
  while (time >= color_times_[i]){

    if (time == color_times_[i]){
      lo_color_index_ = i;
      hi_color_index_ = i;
    }

    if (i < color_times_.size()- 1)
      i++;
    else
      break;

  lo_color_index_ = i - 1;
  hi_color_index_ = i;
  }

}
