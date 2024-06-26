//______________________________________________________________________________
// Implementation of TopLevel functions
//______________________________________________________________________________
#include "debug.hpp"
#include "top-level.hpp"
#include "momentary-switch.hpp"

//______________________________________________________________________________
// State machine to run color clocks and set time
//______________________________________________________________________________
void TopLevel::run()
{
  std::map<ColorClock*, pin_map>::iterator it;
  for (it = cc_out_pin_map_.begin(); it != cc_out_pin_map_.end(); it++)
  {
    RgbColor out_color = it->first->time_to_color();
    short r_pin = it->second[RgbColor::PriColor::RED];
    short g_pin = it->second[RgbColor::PriColor::GRN];
    short b_pin = it->second[RgbColor::PriColor::BLU];

    // These LEDs are common anode - boolean here sends the inverted values to
    // analog pins, e.g. full on = 0 instead of 255
    out_color.write_rgb_to_out(r_pin, g_pin, b_pin, true);
    //__________________________________________________________________________
    // Debug
    //__________________________________________________________________________
    static short prev_sec = 0;
    short crnt_sec = it->first->clock_->get_sec();
    if (prev_sec != crnt_sec)
    {
      Debug::print_time(it->first->clock_->rtc_);
      Debug::print_color(out_color);
      prev_sec = crnt_sec;
    }
    //__________________________________________________________________________
 
  }

  switch(state_)
  {
    //__________________________________________________________________________
    case(State::IDLE):
      //________________________________________________________________________
      // DEBUG
      //Debug::print_string_with_new_line("TopLevel::run IDLE");
      //________________________________________________________________________

      time_ctrl_.get_display()->write_disp_str("    ");

      if (enter_btn_.get_input_type() == MomentarySwitch::InputType::LONG)
        state_ = State::SET_TIME;

      break;

    //__________________________________________________________________________
    case(State::SET_TIME):
      //________________________________________________________________________
      // DEBUG
      //Debug::print_string_with_new_line("TopLevel::run SET_TIME");
      //________________________________________________________________________
      time_ctrl_.set_time();
      if (time_ctrl_.get_state() == TimeController::State::DONE)
        state_ = State::IDLE;

      break;

    default:
      break;
  }

  return;
}


//______________________________________________________________________________
// Add ColorClock object and RGB pins to map
//______________________________________________________________________________
void TopLevel::register_color_clock(ColorClock* color_clock
  , short r_pin
  , short g_pin
  , short b_pin)
{

  cc_out_pin_map_.insert({
    color_clock, RgbColor::create_rgb_pin_map(r_pin, g_pin, b_pin)
  });

}
