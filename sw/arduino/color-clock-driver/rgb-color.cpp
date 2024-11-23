#include "rgb-color.hpp"

#ifdef ARDUINO_BUILD
# include <Arduino.h>
#endif

#ifdef USING_HSV_COLOR
# include "hsv-color.hpp"
#endif

#include <stdio.h>

using Rgb = RgbColor::PriColor;

//______________________________________________________________________________
// Convert an Rgb color object to an Hsv color object
//
// This code was heavily inspired by a program posted by Geeks For Geeks
// "Program to Change RGB color model to HSV color model" found:
// https://www.geeksforgeeks.org/
//  program-change-rgb-color-model-hsv-color-model/
//
// and the algorithm posted here
// https://www.rapidtables.com/convert/color/rgb-to-hsv.html
//______________________________________________________________________________
#ifdef USING_HSV_COLOR
HsvColor RgbColor::to_hsv(){

  float red_norm   = this->rgb_[Rgb::RED]/255.0;
  float green_norm = this->rgb_[Rgb::GRN]/255.0;
  float blue_norm  = this->rgb_[Rgb::BLU]/255.0;

  // get max of normalized values
  float cmax = std::max(red_norm,
               std::max(green_norm,
                        blue_norm));

  // get min of normalized values
  float cmin = std::min(red_norm,
               std::min(green_norm,
                        blue_norm));

  float diff = cmax - cmin;

  // hue calculation
  float hue = -1;

  // if r, g, and b are equal, then the color is grey
  // i.e. the hue doesn't matter
  // this if condition lets us avoid a div by 0 error
  if (diff == 0)
    hue = 0;
  else if (cmax == red_norm)
    hue = fmod((60.0 * (green_norm - blue_norm) / diff + 360) , 360);

  else if (cmax == green_norm)
    hue = 60.0 * (((blue_norm - red_norm)   / diff) + 2);

  else if (cmax == blue_norm)
    hue = 60.0 * (((red_norm - green_norm)  / diff) + 4);

  hue = fmod((hue + 360), 360);

  // sat calculation
  float sat = -1;

  if (cmax == 0) sat = 0;
  else           sat = (diff / cmax) * 100;

  // value computations
  float value = cmax * 100;

  return HsvColor(hue, sat, value);
}
#endif


//______________________________________________________________________________
// Sets the minimum and maximum values for red, green, and blue values.
//______________________________________________________________________________
void RgbColor::set_min_max(int max_red
    , uint8_t max_grn
    , uint8_t max_blu
    , uint8_t min_red
    , uint8_t min_grn
    , uint8_t min_blu
)
{
  max_red_ = max_red;
  max_grn_ = max_grn;
  max_blu_ = max_blu;
  min_red_ = min_red;
  min_grn_ = min_grn;
  min_blu_ = min_blu;
}


//______________________________________________________________________________
// Set the minimum and maximum values for red, green, and blue where all
// primary colors have the same minimum and maximum values.
//______________________________________________________________________________
void RgbColor::set_min_max(int min_val, int max_val)
{
  set_min_max(min_val
    , min_val
    , min_val
    , max_val
    , max_val
    , max_val);
}


//______________________________________________________________________________
// Writes RGB values to output
// If this is a build to the Arduino, writes the ouput pins
//______________________________________________________________________________
void RgbColor::write_rgb_to_out(int red_out
  , int grn_out
  , int blu_out
  , bool flip
)
{
#ifdef ARDUINO_BUILD
if (flip)
{
  rgb_[Rgb::RED] = 0xFF - rgb_[Rgb::RED];
  rgb_[Rgb::GRN] = 0xFF - rgb_[Rgb::GRN];
  rgb_[Rgb::BLU] = 0xFF - rgb_[Rgb::BLU];
}

  analogWrite(red_out, rgb_[Rgb::RED]);
  analogWrite(grn_out, rgb_[Rgb::GRN]);
  analogWrite(blu_out, rgb_[Rgb::BLU]);
#endif
}


//______________________________________________________________________________
// Corrects over flow and underflow of red green and blue.
//______________________________________________________________________________
void RgbColor::bounds_check()
{
  for(auto it = rgb_.begin(); it != rgb_.end(); it++)
  {
    if (it->second > MAX_RGB_VAL)
      it->second = MAX_RGB_VAL;

    if (it->second < MIN_RGB_VAL)
      it->second = MIN_RGB_VAL;
  }

}


//______________________________________________________________________________
// Modifies the color by increasing or decreasing the intensity of one of the
// primary colors.
//
// To increase the intensity of one of the primary colors, the two other
// primary colors are decreased. To decrease the intensity of a primary
// color, the other two are increased, which decreases the saturation of that
// color.
//
// Input parameters:
// color:     red, green, or blue selection
// direction: increase or decrease.
//______________________________________________________________________________
void RgbColor::mod_color(Rgb color, IncDec direction)
{
  for(auto it = rgb_.begin(); it != rgb_.end(); it++)
  {
    if (it->first != color)
    {
      if (direction == IncDec::DECREMENT)
        it->second += mod_amt_;
      else
      {
        it->second -= mod_amt_;
        int flux = 0;
      }
    }
  }

  bounds_check();
}


//______________________________________________________________________________
// Create map of pin assignments as related to red, green, and blue.
//______________________________________________________________________________
std::map <Rgb, short> RgbColor::create_rgb_pin_map(short r_pin
  , short g_pin
  , short b_pin
)
{
  std::map <Rgb, short> mappy;
  mappy.insert({Rgb::RED, r_pin});
  mappy.insert({Rgb::GRN, g_pin});
  mappy.insert({Rgb::BLU, b_pin});

  return mappy;
}

