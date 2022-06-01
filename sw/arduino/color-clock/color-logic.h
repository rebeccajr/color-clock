//------------------------------------------------------------------------------
// DESCRIPTION
// This file contains the logic that maps the time to color for the ColorClock.
// 
// The ColorClock is a colored light that maps the current time
// to a color. The clock will cycle through a series of colors over a period
// of time. A viewer can tell the approximate time from the color 
// of the light.
//------------------------------------------------------------------------------
//
// -
// CLASSES
//
// This program introduces two object types: RgbColor and HsvColor.
// 
// RgbColor contains three member variables:
// r (red)    range: [0, 255] or [0x00, 0xFF]
// g (green)  range: [0, 255] or [0x00, 0xFF]
// b (blue)   range: [0, 255] or [0x00, 0xFF]
//
// RGB colors are used to define the main colors that the clock will cycle
// through.
//
// HsvColor contains three member variables:
// h (hue)        range: [0, 360]
// s (saturation) range: [0, 100]
// v (value)      range: [0, 100]
// 
// HsvColor is used for calculations because they provide a smoother transition.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// NICE TO HAVES
//------------------------------------------------------------------------------
// variable cycle time
// preset color schemes?
// config file read
// RTOS implementation

// The user defined presets include:
// 1) cycle time -length of time for clock to cycle through all colors
// 2) number of colors to cycle through
// 3) specific colors to cycle through

//------------------------------------------------------------------------------
// STANDARD LIBRARIES
//------------------------------------------------------------------------------
#include <algorithm>

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

#ifndef CYCLE_PARTITIONS
#define CYCLE_PARTITIONS    6
#endif

// configuration values
float CYCLE_TIME_IN_HOURS =   12.0/3600; //<---- change this
float HOURS_BET_COLORS = CYCLE_TIME_IN_HOURS / CYCLE_PARTITIONS;

// arrays used for initialization of the clock
float    main_color_times[CYCLE_PARTITIONS];
RgbColor main_colors[CYCLE_PARTITIONS + 1];
RgbColor color_selection[CYCLE_PARTITIONS];

// max and min rgb values
int MAX_VAL       = 60;
int MIN_VAL       = 0;
int MAX_COLOR_VAL = 0xAA;
int MIN_COLOR_VAL = 0x11;

// RGB constants
RgbColor ABS_RGB_RED = RgbColor(0xFF0000);
RgbColor ABS_RGB_YEL = RgbColor(0xFFFF00);
RgbColor ABS_RGB_GRN = RgbColor(0x00FF00);
RgbColor ABS_RGB_CYA = RgbColor(0x00FFFF);
RgbColor ABS_RGB_BLU = RgbColor(0xFF00FF);
RgbColor ABS_RGB_MAG = RgbColor(0xFF00FF);

RgbColor RGB_RED = RgbColor(MAX_COLOR_VAL, MIN_COLOR_VAL, MIN_COLOR_VAL);
RgbColor RGB_YEL = RgbColor(MAX_COLOR_VAL, MAX_COLOR_VAL, MIN_COLOR_VAL);
RgbColor RGB_GRN = RgbColor(MIN_COLOR_VAL, MAX_COLOR_VAL, MIN_COLOR_VAL);
RgbColor RGB_CYA = RgbColor(MIN_COLOR_VAL, MAX_COLOR_VAL, MAX_COLOR_VAL);
RgbColor RGB_BLU = RgbColor(MIN_COLOR_VAL, MIN_COLOR_VAL, MAX_COLOR_VAL);
RgbColor RGB_MAG = RgbColor(MAX_COLOR_VAL, MIN_COLOR_VAL, MAX_COLOR_VAL);


//------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
void get_indices_of_colors (int* indices, float* color_times, float the_time);
RgbColor hsv_to_rgb(HsvColor some_hsvcolor);
HsvColor rgb_to_hsv(RgbColor some_color);

//------------------------------------------------------------------------------
// ARRAY INITIALIZATION FUNCTIONS
//
// The following section of code includes functions to
// initialize arrays used for color and time.
//
// (This description needs improvement)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Initializes array that stores times associated with main colors
//
// Assumption:
// times are in hours
//------------------------------------------------------------------------------
void initialize_color_times(float* color_times, float hours_between_colors) {

  for (int i = 0; i < (CYCLE_PARTITIONS + 1); i++)
    color_times[i] = i * (hours_between_colors);
}


//--------------------------------------------------------------
// Initialize array that contains main colors. Usese
//--------------------------------------------------------------
void initialize_main_colors(RgbColor* colors){
  
  for(int i = 0; i < CYCLE_PARTITIONS; i++)
    colors[i] = color_selection[i];
  
  colors[CYCLE_PARTITIONS] = colors[0];
}


//--------------------------------------------------------------
// Initialize selection of colors. Currently hard-coded, will
// read from config file or user input eventually
//--------------------------------------------------------------
void initialize_color_selection(RgbColor* colors){  
  colors[0] = RGB_RED;
  colors[1] = RGB_YEL;
  colors[2] = RGB_GRN;
  colors[3] = RGB_CYA;
  colors[4] = RGB_BLU;
  colors[5] = RGB_MAG;
}

//--------------------------------------------------------------
// END OF ARRAY INITIALIZATION SECTION
//--------------------------------------------------------------
//--------------------------------------------------------------


/*
void setup(){
  
    print("hours between colors: ", HOURS_BET_COLORS);
    // housekeeping
    size(800, 800);       //width, height
    background(BACKGROUND_COLOR);
    colorMode(RGB, MAX_VAL, MAX_VAL, MAX_VAL);
    
    ellipseMode(RADIUS);
    frameRate(FRAME_RATE);
    
    // array of times and colors
    // indices of these two arrays correspond to one another
    main_color_times = initialize_color_times(HOURS_BET_COLORS);
    main_colors      = initialize_main_colors();

    print("\n------------------------\n");
    
}

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


//--------------------------------------------------------------
// function that fills ellipse with color
//
// argument:
// fill_color - color to fill object with
//--------------------------------------------------------------
void set_clock_color(RgbColor fill_color){
  fill(fill_color.r, fill_color.g, fill_color.b);
}
*/

//--------------------------------------------------------------
// This function is the "main" part of the program that
// determines the RgbColor associated with the current time
// based on the program presets.
//
// arguments:
// times  - array of times that correspond with main colors
// colors - array of main colors
//--------------------------------------------------------------
RgbColor map_time_to_color(
  float  hrs_since_midnight,
  float  fractional_offset,
  float* times,
  RgbColor* colors){
  
  /*// figure out offset from beginning of cycle
  float hrs_since_cycle_restart =
    hrs_since_midnight / CYCLE_TIME_IN_HOURS;

  hrs_since_cycle_restart = hrs_since_midnight - hrs_since_cycle_restart;
  
  // error handling
  if (hrs_since_cycle_restart < 0) hrs_since_cycle_restart = 0;
  
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
  
  return crnt_rgbcolor_time;*/

  return RgbColor();

}

/*
//--------------------------------------------------------------
//--------------------------------------------------------------
// TIME CALCULATIONS
//
// This section of code includes functions used to
// determine time variables as they will be used to determine
// the current color.
//--------------------------------------------------------------

//--------------------------------------------------------------
// This function calculates the fraction of where a specific time
// falls between two other times.
//
// assumption:
// time0, time1 and crnt_time are in same units, and crnt_time
// falls between time0 and time1
//--------------------------------------------------------------
float get_time_as_fractional_offset(float time0, 
                                    float time1, 
                                    float crnt_time){
  
  // ensure time1 is greater than time0
  // if not, swap
  if (time0 > time1) {
    
    time0 += time1;
    time1  = time0 - time1;
    time0  = time0 - time1;
    
  }
  
  float fractional_offset    = (crnt_time - time0) / 
                               (time1 - time0);
  
  //print("\nfractional_offset: " + str(fractional_offset));
  
  return fractional_offset;
}*/



//--------------------------------------------------------------
// END OF TIME CALCULATION SECTION
//--------------------------------------------------------------
//--------------------------------------------------------------

//--------------------------------------------------------------
// returns an array with two elements - the indices of the main
// color times that time_in_hrs falls between
//
// assumption:
// color times are in order
//
// arguments:
// color_times - array of times in same units as time                                  
// time        - time for which to determine indices
//--------------------------------------------------------------
void get_indices_of_colors (int* indices, float* color_times, float the_time){
  
  //print("time: " + time);
  
  int i = 0;
  
  while (the_time >= color_times[i]){
    
    if (the_time == color_times[i]){
      indices[0] = i;
      indices[1] = i;
      return;
    }
    
    if (i < CYCLE_PARTITIONS){
      i++;
    }
    else {
      break;
    }
  }
  
  indices[0] = i - 1;
  indices[1] = i;
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
//--------------------------------------------------------------
// COLOR TYPE CONVERSIONS
//
// The following section of code includes functions that
// convert color objects to different types of color objects,
// e.g. RgbColor to HsvColor and vice versa
//--------------------------------------------------------------

//--------------------------------------------------------------
// convert an Rgb color object to an Hsv color object
// 
// This code was heavily inspired by a program posted
// by Geeks For Geeks "Program to Change RGB color model
// to HSV color model" found:
// https://www.geeksforgeeks.org/
//         program-change-rgb-color-model-hsv-color-model/
//
// and the algorithm posted here
// https://www.rapidtables.com/convert/color/rgb-to-hsv.html
//--------------------------------------------------------------
HsvColor rgb_to_hsv(RgbColor some_color){

  float red_norm   = some_color.r/255.0;
  float green_norm = some_color.g/255.0;
  float blue_norm  = some_color.b/255.0;
  
  // get max of normalized values
  float cmax = std::max(red_norm,
                        green_norm,
                        blue_norm);
  
  // get min of normalized values
  float cmin = std::min(red_norm,
                        green_norm,
                        blue_norm);
                   
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

//--------------------------------------------------------------
// convert an Hsv color object to an Rgb color object
// 
// This code is implementing the algorithm posted here:
// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
//--------------------------------------------------------------
RgbColor hsv_to_rgb(HsvColor some_hsvcolor){
  
  float hue = some_hsvcolor.h;
  float sat = some_hsvcolor.s / 100;
  float val = some_hsvcolor.v / 100;
  
  float c = val * sat;
  float x = c * (1 - abs(fmod((hue / 60), 2) - 1));
  float m = val - c;
  
  float r_prime = 0;
  float g_prime = 0;
  float b_prime = 0;
  
  if (0 <= hue && hue < 60) {
    r_prime = c;
    g_prime = x;
    b_prime = 0;
  }
  else if ( 60 <= hue && hue < 120) {
    r_prime = x;
    g_prime = c;
    b_prime = 0;
  }
  else if (120 <= hue && hue < 180) {
    r_prime = 0;
    g_prime = c;
    b_prime = x;
  }
  else if (180 <= hue && hue < 240) {
    r_prime = 0;
    g_prime = x;
    b_prime = c;
  }
  else if (240 <= hue && hue < 300) {
    r_prime = x;
    g_prime = 0;
    b_prime = c;
  }
  else if (300 <= hue && hue < 360) {
    r_prime = c;
    g_prime = 0;
    b_prime = x;
  }

  int r = round((r_prime + m) * 255);
  int g = round((g_prime + m) * 255);
  int b = round((b_prime + m) * 255);

  return RgbColor(r, g, b);
}
//--------------------------------------------------------------
// END OF COLOR CONVERSIONS SECTION
//--------------------------------------------------------------
//--------------------------------------------------------------


//--------------------------------------------------------------
//--------------------------------------------------------------
// COLOR CLASSES
//
// The following section of code includes the classes to hold
// color objects.
//--------------------------------------------------------------



//--------------------------------------------------------------
// END OF COLOR CLASSES SECTION
//--------------------------------------------------------------
//--------------------------------------------------------------

//--------------------------------------------------------------
//--------------------------------------------------------------
