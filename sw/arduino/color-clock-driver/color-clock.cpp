//______________________________________________________________________________
// Implementation of ColorClock functions
//______________________________________________________________________________
#include "hsv-color.hpp"
#include "rgb-color.hpp"
#include "color-clock.hpp"

#include "debug.hpp"

#define DEFAULT_CYCLE_TIME_DIVISOR    10.0
#define DEFAULT_MIN_CYCLE_TIME_IN_SEC  6.0
#define DEFAULT_MIN_CYCLE_TIME_IN_HR   1.0
#define DEFAULT_24_CYCLE_TIME_IN_HR    1.0


ColorClock::ColorClock(FluxClock* the_clock 
  , double cycle_time_in_hrs
  , std::vector<RgbColor> colors
  )
  : clock_(the_clock)
  {
    //__________________________________________________________________________
    // color_times_ contains the times associated w/
    // *_color_selection_ elements
    // There is a 1:1 mapping between these two vectors
    //__________________________________________________________________________
    init_color_selection_ = colors;
    //__________________________________________________________________________

    // Add first element of vector to end for interpolation between last
    // color and first
    init_color_selection_.push_back(*init_color_selection_.begin());

    crnt_color_selection_ = init_color_selection_;

    min_cycle_time_ = cycle_time_in_hrs / DEFAULT_CYCLE_TIME_DIVISOR;
    max_cycle_time_ = cycle_time_in_hrs;

    set_cycle_time(cycle_time_in_hrs);
    mod_cycle_amt_ = cycle_time_in_hrs_ / DEFAULT_CYCLE_TIME_DIVISOR;
  }


//______________________________________________________________________________
// Set max and min cycle time.
//
// Input parameters:
// min_cycle - minimum cycle time
// max_cycle - maximum cycle time
//______________________________________________________________________________
void ColorClock::set_min_max_cycle_time(float min_cycle, float max_cycle)
{
  min_cycle_time_ = min_cycle;
  max_cycle_time_ = max_cycle;
}


//______________________________________________________________________________
// Set cycle time modifier.
//
// Input parameters:
// mod_cycle_amt - cycle time modifier
//______________________________________________________________________________
void ColorClock::set_mod_cycle_amt(float mod_cycle_amt)
{
  mod_cycle_amt_ = mod_cycle_amt;
}


//______________________________________________________________________________
// Set cycle time and caclulate color times.
//______________________________________________________________________________
void ColorClock::set_cycle_time(double cycle_time_in_hrs)
{
    cycle_time_in_hrs_ = cycle_time_in_hrs;

    // Error handling
    if (cycle_time_in_hrs < min_cycle_time_)
      cycle_time_in_hrs_ = min_cycle_time_;

    if (cycle_time_in_hrs > max_cycle_time_)
      cycle_time_in_hrs_ = max_cycle_time_;

    color_times_.clear();

    int   partition_count = init_color_selection_.size() - 1;
    float interval_length = cycle_time_in_hrs_ / partition_count;

    for (int i = 0; i <= partition_count; i++)
      color_times_.push_back(i * interval_length);
}

//______________________________________________________________________________
// Prints information about this object.
//______________________________________________________________________________
void ColorClock::print()
{
  print_color_selections();
  Debug::print_new_line();
  Debug::print_string_with_new_line((char*)("_________________"));
  Debug::print_string_with_new_line((char*)(" Interval Times"  ));
  Debug::print_string_with_new_line((char*)("_________________"));
  Debug::print_labeled_float((char*)("cycle time:          ")
    , cycle_time_in_hrs_);
  Debug::print_labeled_float((char*)("min cycle time:      ")
    , min_cycle_time_);
  Debug::print_labeled_float((char*)("max cycle time:      ")
    , max_cycle_time_);
  Debug::print_labeled_float((char*)("cycle time modifier: ")
    , mod_cycle_amt_);
  Debug::print_new_line();
  Debug::print_labeled_int((char*)("size of color times: ")
    , color_times_.size());
  Debug::print_new_line();
  Debug::print_interval_times_in_sec(color_times_);
  Debug::print_new_line();
}


//______________________________________________________________________________
// Prints initial and current color selection arrays.
//______________________________________________________________________________
void ColorClock::print_color_selections()
{
  Debug::print_new_line();
  Debug::print_string_with_new_line((char*)("_________________________"));
  Debug::print_string_with_new_line((char*)(" Initial Color Selection " ));
  Debug::print_string_with_new_line((char*)("_________________________"));
  Debug::print_color_array(init_color_selection_);

  Debug::print_new_line();
  Debug::print_new_line();
  Debug::print_string_with_new_line((char*)("_________________________"));
  Debug::print_string_with_new_line((char*)(" Current Color Selection " ));
  Debug::print_string_with_new_line((char*)("_________________________"));
  Debug::print_color_array(crnt_color_selection_);
  Debug::print_new_line();
}


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
  //float the_milli = 0;

  float hrs_since_midnight =
    TimeCalcs::get_hrs_since_midnight(the_hr, the_min, the_sec, the_milli);

  float hrs_since_cycle_restart =
    fmod(hrs_since_midnight, cycle_time_in_hrs_);

  // error handling
  if (hrs_since_cycle_restart < 0) hrs_since_cycle_restart = 0;

  determine_color_indices(hrs_since_cycle_restart);

  float lo_color_time  = color_times_[lo_color_index_];
  float hi_color_time  = color_times_[hi_color_index_];

  float fraction =
    TimeCalcs::get_time_as_fractional_offset(lo_color_time
      , hi_color_time
      , hrs_since_cycle_restart);

  static float prev_fraction = 0;
  static int count = 0;
 
  // convert colors from main_colors array to hsv
  // for smoother transitions between colors
  HsvColor hsvcolor0 = crnt_color_selection_[lo_color_index_].to_hsv();
  HsvColor hsvcolor1 = crnt_color_selection_[hi_color_index_].to_hsv();

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

//______________________________________________________________________________
// Modifies the elements of crnt_color_selection_.
//
// Input parameters:
// r_g_or_b:  red, green, or blue enum value
// direction: either increase or decrease
//______________________________________________________________________________
void ColorClock::mod_color_selection(Rgb r_g_or_b
  , RgbColor::IncDec direction
)
{
  for(uint8_t i = 0; i < crnt_color_selection_.size(); i++)
  {
    if(init_color_selection_[i].rgb_[r_g_or_b] > 0)
    {
      crnt_color_selection_[i].mod_color(r_g_or_b, direction);

      /*
      Debug::print_new_line();
      Debug::print_string_with_new_line((char*)"__________________________");
      Debug::print_labeled_int((char*)"i: ", i);
      Debug::print_new_line();
      Debug::print_string_with_new_line((char*)"Initial color");
      Debug::print_color(init_color_selection_[i]);
      Debug::print_new_line();
      Debug::print_string_with_new_line((char*)"Current color");
      Debug::print_color(crnt_color_selection_[i]);
      */
    }
  }

}


//______________________________________________________________________________
// Increases or decreases the cycle time by a constant amount.
//
// Input parameters:
// direction: either increase or decrease
//______________________________________________________________________________
void ColorClock::mod_cycle_time(RgbColor::IncDec direction)
{
  if (direction == RgbColor::IncDec::DECREMENT)
    set_cycle_time(cycle_time_in_hrs_ - mod_cycle_amt_);
  else if (direction == RgbColor::IncDec::INC)
    set_cycle_time(cycle_time_in_hrs_ + mod_cycle_amt_);

  Debug::print_interval_times_in_sec(color_times_);
}