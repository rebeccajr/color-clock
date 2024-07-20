#include <unistd.h>
#include <vector>

#include "flux-macros.hpp"
#include "color-clock.hpp"
#include "debug.hpp"
#include "color-const.hpp"

int main()
{
  FluxClock clocky = FluxClock();
  std::vector<RgbColor> color_selection = {ColorConst::RED, ColorConst::GRN, ColorConst::BLU};

  ColorClock cc = ColorClock(&clocky, 12.0/3600.0);

  cc.print();

  uint8_t sec = 0;
  clocky.set_yr   (2024);
  clocky.set_month(1);
  clocky.set_day  (1);
  clocky.set_hr   (0);
  clocky.set_min  (30);
  clocky.set_sec  (sec);

  cc.print_color_selections();
  Debug::print_string_with_new_line((char*)"!!!");
  cc.mod_color_selection(RgbColor::PriColor::RED, RgbColor::IncDec::INC);
  Debug::print_new_line();
  Debug::print_string_with_new_line((char*)"____________________");
  Debug::print_string_with_new_line((char*)"crnt_color_selection");
  Debug::print_color_array(cc.crnt_color_selection_);
/*
  cc.mod_color_selection(RgbColor::PriColor::RED, RgbColor::IncDec::DECREMENT);
  Debug::print_string_with_new_line((char*)"____________________");
  Debug::print_string_with_new_line((char*)"crnt_color_selection");
  Debug::print_color_array(cc.crnt_color_selection_);
  cc.mod_color_selection(RgbColor::PriColor::RED, RgbColor::IncDec::DECREMENT);
  Debug::print_string_with_new_line((char*)"____________________");
  Debug::print_string_with_new_line((char*)"crnt_color_selection");
  Debug::print_color_array(cc.crnt_color_selection_);
  cc.mod_color_selection(RgbColor::PriColor::RED, RgbColor::IncDec::DECREMENT);
  Debug::print_color_array(cc.crnt_color_selection_);
  cc.mod_color_selection(RgbColor::PriColor::RED, RgbColor::IncDec::DECREMENT);
  Debug::print_string_with_new_line((char*)"____________________");
  Debug::print_string_with_new_line((char*)"crnt_color_selection");
  Debug::print_color_array(cc.crnt_color_selection_);
  cc.mod_color_selection(RgbColor::PriColor::RED, RgbColor::IncDec::DECREMENT);
  Debug::print_color_array(cc.crnt_color_selection_);
  cc.mod_color_selection(RgbColor::PriColor::RED, RgbColor::IncDec::DECREMENT);
  Debug::print_color_array(cc.crnt_color_selection_);
  cc.mod_color_selection(RgbColor::PriColor::RED, RgbColor::IncDec::DECREMENT);
  Debug::print_color_array(cc.crnt_color_selection_);
  cc.mod_color_selection(RgbColor::PriColor::RED, RgbColor::IncDec::DECREMENT);
  Debug::print_color_array(cc.crnt_color_selection_);
  cc.mod_color_selection(RgbColor::PriColor::RED, RgbColor::IncDec::DECREMENT);
  Debug::print_color_array(cc.crnt_color_selection_);
  cc.mod_color_selection(RgbColor::PriColor::RED, RgbColor::IncDec::DECREMENT);
  Debug::print_color_array(cc.crnt_color_selection_);
  cc.reset_color_selection();
  Debug::print_new_line();
  */

  for (uint8_t i = 0; i <= 3; i++)
  {
    clocky.set_sec(sec++);
    Debug::print_labeled_int((char*)"sec ", clocky.get_sec());
    Debug::print_new_line();
    RgbColor color = cc.time_to_color();
    Debug::print_color(color);
    Debug::print_new_line();
    //sleep for 1 sec
    //usleep(1000000);
    
  }


  return 0;
}
