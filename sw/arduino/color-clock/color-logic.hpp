//------------------------------------------------------------------------------
// NICE TO HAVES
//------------------------------------------------------------------------------
// variable cycle time
// preset color schemes?
// config file read
// linked list for color
// RTOS implementation

// The user defined presets include:
// 1) cycle time -length of time for clock to cycle through all colors
// 2) number of colors to cycle through
// 3) specific colors to cycle through


//------------------------------------------------------------------------------
// INCLUDE LIBRARIES
//------------------------------------------------------------------------------
#include <algorithm>
#include <vector>

#include "color-classes.hpp"
#include "time-calcs.hpp"



/*
void draw(){
  ellipse(SHAPE_CENTER_X, SHAPE_CENTER_Y, SHAPE_WIDTH, SHAPE_HEIGHT);
  print("\n\n-----");
  
  RgbColor crnt_rgb = map_time_to_color(main_color_times, main_colors);
  set_clock_color(crnt_rgb);
  noStroke();
  
  // debug code
  HsvColor crnt_hsv = rgb_to_hsv(crnt_rgb);
  
  print("\n\n");
  crnt_rgb.print_me();
  
  print("\n");
  crnt_hsv.print_me();
}
*/

//--------------------------------------------------------------
// This function is the "main" part of the program that
// determines the RgbColor associated with the current time
// based on the program presets.
//
// Arguments:
// times  - array of times that correspond with main colors
// colors - array of main colors
//--------------------------------------------------------------
RgbColor map_time_to_color(
  float  hrs_since_cycle_restart,
  float* times, RgbColor* colors){
  
  //print("\nhours since cycle restart: ", hrs_since_cycle_restart);
  
  // modifies the indices of the colors from the main_colors array
  // in which the current time falls between
  int index[2];
  get_indices_of_colors(index, times, hrs_since_cycle_restart);
  
  //print("\n\nindices of boundary colors: " + str(index[0]) + ", " 
                                           //+ str(index[1]));
  
  // convert colors from main_colors array to hsv
  // for smoother transitions between colors
  HsvColor hsvcolor0 = rgb_to_hsv(colors[index[0]]);
  HsvColor hsvcolor1 = rgb_to_hsv(colors[index[1]]);
  
  float fraction  = get_time_as_fractional_offset(times[index[0]],
                                                  times[index[1]], 
                                                  hrs_since_cycle_restart); 
  
  HsvColor crnt_hsvcolor_time 
    = interpolate_bet_hsvcolors(hsvcolor0, hsvcolor1, fraction);                                          
  
  // convert hsv to rgb in order to display properly
  RgbColor crnt_rgbcolor_time = hsv_to_rgb(crnt_hsvcolor_time);
  
  return crnt_rgbcolor_time;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
// TIME CALCULATIONS
//
// This section of code includes functions used to
// determine time variables as they will be used to determine
// the current color.
//--------------------------------------------------------------


//--------------------------------------------------------------
// END OF TIME CALCULATION SECTION
//--------------------------------------------------------------
//--------------------------------------------------------------

//--------------------------------------------------------------
// Returns an array with two elements - the indices of the main
// color times that time_in_hrs falls between
//
// Assumption:
// Color times are in order.
//
// Arguments:
// color_times - array of times in same units as time 
// time        - time for which to determine indices
//--------------------------------------------------------------
void get_indices_of_colors (int* ret_indices,
        float* color_times, float the_time){
  
  //print("time: " + time);
  
  int i = 0;
  
  while (the_time >= color_times[i]){
    
    if (the_time == color_times[i]){
      ret_indices[0] = i;
      ret_indices[1] = i;
      return;
    }
    
    if (i < CYCLE_PARTITIONS){
      i++;
    }
    else {
      break;
    }
  }
  
  ret_indices[0] = i - 1;
  ret_indices[1] = i;
  return;
}


//--------------------------------------------------------------
//--------------------------------------------------------------
// COLOR INTERPOLATION FUNCTIONS
//
// The following section of code includes functions that
// convert color objects to different types of color objects,
// e.g. RgbColor to HsvColor and vice versa
//--------------------------------------------------------------

//--------------------------------------------------------------
// This function returns a new RgbColor object that falls
// between two RgbColors based on a fraction that represents
// the percentage distance from one color to another.
//
// Note that this function is not currently used.
//
// assumption:
// color is in correct range and fraction is between 0 and 1
//--------------------------------------------------------------
RgbColor interpolate_bet_rgbcolors(RgbColor color1, 
                                   RgbColor color2, 
                                   float    fraction){
  
  // difference between color2 and color1
  int delta;
  
  delta = color2.r - color1.r;
  int new_red   = (int) (fraction * delta) + color1.r;
  
  delta = color2.g - color1.g;
  int new_green = (int) (fraction * delta) + color1.g;
  
  delta = color2.b - color1.b;
  int new_blue  = (int) (fraction * delta) + color1.b; 
  
  return RgbColor(new_red, new_green, new_blue);
  
}

//--------------------------------------------------------------
// This function returns a new HsvColor object that falls
// between two HsvColors based on a fraction that represents
// the percentage distance from one color to another.
//
// assumption:
// color is in correct range and fraction is between 0 and 1
//--------------------------------------------------------------
/*HsvColor interpolate_bet_hsvcolors(HsvColor color1, 
                                   HsvColor color2, 
                                   float    fraction){
  /*                                 
  float delta;
  
  delta = color2.h - color1.h;
  delta = (delta + 360.0) % 360.0;
  float new_hue = (fraction * delta) + color1.h;
  
  delta = color2.s - color1.s;
  float new_sat = (fraction * delta) + color1.s;
  
  delta = color2.v - color1.v;
  float new_val  = (fraction * delta) + color1.v; 
  
  return new HsvColor(new_hue, new_sat, new_val);                          
}*/
//--------------------------------------------------------------
// END OF COLOR INTERPOLATION SECTION
//--------------------------------------------------------------
//--------------------------------------------------------------


//--------------------------------------------------------------
