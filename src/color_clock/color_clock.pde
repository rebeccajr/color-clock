/*------------------------------------------------------------------------------
 
 -
 PROJECT NAME
 Color Clock
 
 -
 DESIGNER
 Rebecca 

 -
 DESCRIPTION   
 
 This program is a software prototype of the Color Clock.
 
 The Color Clock is a colored light that maps the current time
 to a color. The clock will cycle through a series of colors over a period
 of time. A viewer can tell the approximate time from the color 
 of the light.
 
 The user defined presets include:
 1) cycle time -length of time for clock to cycle through all colors
 2) number of colors to cycle through
 3) specific colors to cycle through
 
 -
 CLASSES
 
 This program introduces two object types: RgbColor and HsvColor.
 
 RgbColor contains three member variables:
 r (red)    range: [0, 255] or [0x00, 0xFF]
 g (green)  range: [0, 255] or [0x00, 0xFF]
 b (blue)   range: [0, 255] or [0x00, 0xFF]
 
 RGB colors are used to define the main colors that the clock will cycle
 through.
 
 HsvColor contains three member variables:
 h (hue)        range: [0, 360]
 s (saturation) range: [0, 100]
 v (value)      range: [0, 100]
 
 HsvColor is used for calculations because they provide a smoother transition.
                
------------------------------------------------------------------------------*/

// next tasks:
// port to hardware!!
// modify to allow for cycle time to be in days
// preset color schemes?

//--------------------------------------------------------------
// GLOBAL VARIABLES
//--------------------------------------------------------------

// arrays used for initialization of the clock
float   [] main_color_times;
RgbColor[] main_colors;
RgbColor[] color_selection = initialize_color_selection();

// constants associated with timing
final float CYCLE_TIME_IN_HOURS =   2.0/3600; //<---- change this
final int   CYCLE_PARTITIONS    =   6;
final float HOURS_BET_COLORS 
            = CYCLE_TIME_IN_HOURS / CYCLE_PARTITIONS;

final int SEC_IN_MIN = 60;
final int MIN_IN_HR  = 60;
final int SEC_IN_HR  = SEC_IN_MIN * MIN_IN_HR;

// variables used to get offset of time in millis
int MILLIS_OFFSET = 0;
int prev_sec      = 0;

// max and min rgb values
final int MAX_VAL    = 255;
final int MIN_VAL    = 0;
final int MAX_COLOR_VAL = 0xAA;
final int MIN_COLOR_VAL = 0x11;

//--------------------------------------------------------------
// VISUAL OUTPUT VARIABLES
//--------------------------------------------------------------
final int WINDOW_WIDTH_IN_PX  = 800;
final int WINDOW_HEIGHT_IN_PX = 800;
final int SHAPE_CENTER_X      = WINDOW_WIDTH_IN_PX  / 2;
final int SHAPE_CENTER_Y      = WINDOW_HEIGHT_IN_PX / 2;
final int SHAPE_WIDTH         = int (WINDOW_WIDTH_IN_PX  * 0.8/2);
final int SHAPE_HEIGHT        = int (WINDOW_HEIGHT_IN_PX * 0.8/2);
final int BACKGROUND_COLOR    = 0x111111;
final int FRAME_RATE          = 600;
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------

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

//--------------------------------------------------------------
// This function is the "main" part of the program that
// determines the RgbColor associated with the current time
// based on the program presets.
//
// arguments:
// times  - array of times that correspond with main colors
// colors - array of main colors
//--------------------------------------------------------------
RgbColor map_time_to_color(float[] times, RgbColor[] colors){
  
  float hrs_since_midnight = get_hours_since_midnight();
  
  // figure out offset from beginning of cycle
  float hrs_since_cycle_restart = hrs_since_midnight % CYCLE_TIME_IN_HOURS;
  
  // error handling
  if (hrs_since_cycle_restart < 0) hrs_since_cycle_restart = 0;
  
  print("\nhours since cycle restart: ", hrs_since_cycle_restart);
  
  // returns the indices of the colors from the main_colors array
  // in which the current time falls between
  int[] index = get_indices_of_colors(times, hrs_since_cycle_restart);
  
  print("\n\nindices of boundary colors: " + str(index[0]) + ", " + str(index[1]));
  
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
// This funtion calculates the fraction of where a specific time
// falls between two other times.
//
// assumption:
// time0, time1 and crnt_time are in same units, and crnt_time
// falls between time0 and time1
//--------------------------------------------------------------
float get_time_as_fractional_offset(float time0, float time1, float crnt_time){
  
  // ensure time1 is greater than time0
  // if not, swap
  if (time0 > time1) {
    
    time0 += time1;
    time1  = time0 - time1;
    time0  = time0 - time1;
    
  }
  
  float fractional_offset    = (crnt_time - time0) / (time1 - time0);
  
  print("\nfractional_offset: " + str(fractional_offset));
  
  return fractional_offset;
}


//--------------------------------------------------------------
// returns current time in units of hours since midnight
//--------------------------------------------------------------
float get_hours_since_midnight(){

  int crnt_hr  = hour();
  int crnt_min = minute();
  int crnt_sec = second();
  
  set_millis_offset(crnt_sec);
  
  float millis = (millis() - MILLIS_OFFSET) % 1000;
  
  float  sec_since_midnight   
    = (SEC_IN_MIN * (crnt_hr * MIN_IN_HR + crnt_min) + crnt_sec + millis / 1000);
  float  hours_since_midnight = (sec_since_midnight/(1.0 * SEC_IN_HR));  
  
  print("\ncurrent hour:         ", crnt_hr);
  print("\ncurrent minute:       ", crnt_min);
  print("\ncurrent second:       ", crnt_sec);
  print("\ncurrent millis:       ", millis);
  print("\n\nhours since midnight: ", hours_since_midnight);
  
  return hours_since_midnight;
}

//--------------------------------------------------------------
// The function millis() returns the number of milliseconds
// since the beginning of program execution, while the functions
// second(), minute(), and hour() return the current second,
// minute, and hour of the day, respectively.
//
// The functon millis() is not coordinated with the time of day,
// so the following function, set_millis_offset is used to
// align the return value of millis() with the time of day.
//
// Every time a second passes, the millisecond offset between
// when the program started and the start of the last second
// is recalculated.
// 
// This function does not determine the precise millisecond of
// the current time, however, it suits the purposes of this
// program in that milliseconds will increase for the duration
// of a second in time, and then reset.
//--------------------------------------------------------------
void set_millis_offset(int crnt_sec){
  
  // check if beginning of new second
  if (prev_sec != crnt_sec){    
    MILLIS_OFFSET = millis();
    print("\nmillis offset set!!: " + MILLIS_OFFSET + "\n");
    print("\n");
  }
  
    prev_sec = crnt_sec;  
}
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
int [] get_indices_of_colors (float[] color_times, float time){
  
  //print("time: " + time);
  
  int [] indices = new int[2];
  int i = 0;
  
  while (time >= color_times[i]){
    
    if (time == color_times[i]){
      indices[0] = i;
      indices[1] = i;
      return indices;
    }
    
    if (i < color_times.length - 1){
      i++;
    }
    else {
      break;
    }
  }
  
  indices[0] = i - 1;
  indices[1] = i;

  return indices;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
// ARRAY INITIALIZATION FUNCTIONS
//
// The following section of code includes functions to
// initialize arrays used for color and time.
//
// (This description needs improvement)
//--------------------------------------------------------------

//--------------------------------------------------------------
// initialize array that stores times of main colors
//
// assumption:
// times are in hours
//--------------------------------------------------------------
float [] initialize_color_times(float hours_between_colors) {

  float [] color_times = new float[CYCLE_PARTITIONS + 1];
  for (int i = 0; i < (CYCLE_PARTITIONS + 1); i++) {
    color_times[i] = i * (hours_between_colors);
    print("\ncolor_times index ", i, "----> hour ", color_times[i]);
  }
  
  return color_times;
}

//--------------------------------------------------------------
// initialize array that contains main colors
//--------------------------------------------------------------
RgbColor [] initialize_main_colors(){
  
  int len = CYCLE_PARTITIONS + 1;
  RgbColor [] colors = new RgbColor[len];
  
  for(int i = 0; i < CYCLE_PARTITIONS; i++){
    colors[i] = color_selection[i];
  }
  
  colors[CYCLE_PARTITIONS] = colors[0];
  
  return colors;
}

//--------------------------------------------------------------
// initialize array that contains main colors 
// currently hard-coded
//--------------------------------------------------------------
RgbColor [] initialize_color_selection(){
  
  RgbColor [] colors = new RgbColor[6];
  
  colors[0] = new RgbColor(MAX_COLOR_VAL, MIN_COLOR_VAL, MIN_COLOR_VAL);  // red
  colors[1] = new RgbColor(MAX_COLOR_VAL, MAX_COLOR_VAL, MIN_COLOR_VAL);  // yellow
  colors[2] = new RgbColor(MIN_COLOR_VAL, MAX_COLOR_VAL, MIN_COLOR_VAL);  // green
  colors[3] = new RgbColor(MIN_COLOR_VAL, MAX_COLOR_VAL, MAX_COLOR_VAL);  // cyan
  colors[4] = new RgbColor(MIN_COLOR_VAL, MIN_COLOR_VAL, MAX_COLOR_VAL);  // blue
  colors[5] = new RgbColor(MAX_COLOR_VAL, MIN_COLOR_VAL, MAX_COLOR_VAL);  // magenta
  
  return colors;
}
//--------------------------------------------------------------
// END OF ARRAY INITIALIZATION SECTION
//--------------------------------------------------------------
//--------------------------------------------------------------


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
  
  return new RgbColor(new_red, new_green, new_blue);
  
}

//--------------------------------------------------------------
// This function returns a new HsvColor object that falls
// between two HsvColors based on a fraction that represents
// the percentage distance from one color to another.
//
// assumption:
// color is in correct range and fraction is between 0 and 1
//--------------------------------------------------------------
HsvColor interpolate_bet_hsvcolors(HsvColor color1, 
                                   HsvColor color2, 
                                   float    fraction){
                                   
  float delta;
  
  delta = color2.h - color1.h;
  delta = (delta + 360.0) % 360.0;
  float new_hue = (fraction * delta) + color1.h;
  
  delta = color2.s - color1.s;
  float new_sat = (fraction * delta) + color1.s;
  
  delta = color2.v - color1.v;
  float new_val  = (fraction * delta) + color1.v; 
  
  return new HsvColor(new_hue, new_sat, new_val);                                  
}
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
// This code was heavily inspired by a program posted
// by Geeks For Geeks "Program to Change RGB color model
// to HSV color model" found:
// https://www.geeksforgeeks.org/program-change-rgb-color-model-hsv-color-model/
//
// and the algorithm posted here
// https://www.rapidtables.com/convert/color/rgb-to-hsv.html
HsvColor rgb_to_hsv(RgbColor some_color){

  float red_norm   = some_color.r/255.0;
  float green_norm = some_color.g/255.0;
  float blue_norm  = some_color.b/255.0;
  
  // get max of normalized values
  float cmax = max(red_norm,
                   green_norm,
                   blue_norm);
  
  // get min of normalized values
  float cmin = min(red_norm,
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
    hue = (60.0 * (green_norm - blue_norm) / diff + 360) % 360;
  
  else if (cmax == green_norm)
    hue = 60.0 * (((blue_norm - red_norm)   / diff) + 2);
  
  else if (cmax == blue_norm)
    hue = 60.0 * (((red_norm - green_norm)  / diff) + 4);
 
  hue = (hue + 360) % 360;
 
  // sat calculation
  float sat = -1;
  
  if (cmax == 0) sat = 0;
  else           sat = (diff / cmax) * 100;
    
  // value computations
  float value = cmax * 100;

  return new HsvColor(hue, sat, value);
   
}
//--------------------------------------------------------------
// This code is implementing the algorithm posted here:
// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
RgbColor hsv_to_rgb(HsvColor some_hsvcolor){
  
  float hue = some_hsvcolor.h;
  float sat = some_hsvcolor.s / 100;
  float val = some_hsvcolor.v / 100;
  
  float c = val * sat;
  float x = c * (1 - abs((hue / 60) % 2 - 1));
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

  return new RgbColor(r, g, b);
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
// object that holds an RGB color
// assumptions:  0 <= r, g, b < 255
//--------------------------------------------------------------
class RgbColor {
  int r;      // red
  int g;      // green
  int b;      // blue
  
  RgbColor(){}

  // values normalized to 255
  RgbColor(int red, int green, int blue){
  
    r = red;
    g = green;
    b = blue;
    
  }
  
  // enables user to enter RGB values using a 6 digit hex int
  RgbColor(int rgb_hex){
    
    r = (rgb_hex & 0xFF0000) >> 16;
    g = (rgb_hex & 0x00FF00) >> 8;
    b = (rgb_hex & 0x0000FF);
     
  }
  
  // converts RgbColor to string
  String to_string(){
  
  return "red: "   + nf(this.r, 3, 3) +
         "; grn: " + nf(this.g, 3, 3) + 
         "; blu: " + nf(this.b, 3, 3);
  
  }
  
  // prints RgbColor string to screen
  void print_me(){
    print(this.to_string());
  }

}

//--------------------------------------------------------------
// object that holds an HSV color
// assumptions:  0 <= hue < 360
//               0 <= sat < 100
//               0 <= val < 100
//--------------------------------------------------------------
class HsvColor {
  float h;
  float s; 
  float v;
  HsvColor(){}

  HsvColor(float hue, float sat, float value){
  
    h = hue;
    s = sat;
    v = value;
 
  }
  
  String to_string(){
  
  return "hue: "   + nf(this.h, 3, 3) +
         "; sat: " + nf(this.s, 3, 3) + 
         "; val: " + nf(this.v, 3, 3);
  
  }
  
  void print_me(){
    print(this.to_string());
  }
}

//--------------------------------------------------------------
// END OF COLOR CLASSES SECTION
//--------------------------------------------------------------
//--------------------------------------------------------------

//--------------------------------------------------------------
//--------------------------------------------------------------

void print_debug_value(String variable_name, double value,
                       boolean skip_extra_line){

          
                         
}
