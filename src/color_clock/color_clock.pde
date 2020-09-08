/***************************************************************
 Created by:    Rebecca

 Description:   This program maps the current time to a color.
 
                Time is displayed as a colored ellipse.
                color will cycle through "main colors" i.e.
                red, yellow, green, cyan, blue, and magenta
                with the following RGB values:
                
                red     0xFF0000
                yellow  0xFF0000
                green   0x00FF00 
                cyan    0x00FFFF
                blue    0x0000FF
                magenta 0xFF00FF
                
***************************************************************/

// next tasks:
// convert hsv to rgb
// make transitions smoother - use intervals less than 1 sec
// preset color schemes?


//--------------------------------------------------------------
// set constants
//--------------------------------------------------------------
final int MAX_VAL    = 255;
final int MIN_VAL    = 0;
final int SEC_IN_MIN = 60;
final int MIN_IN_HR  = 60;
final int SEC_IN_HR  = SEC_IN_MIN * MIN_IN_HR;


float   [] main_color_times;
RgbColor[] main_colors;
RgbColor[] color_selection = initialize_color_selection();



final float cycle_time_in_hours =   .005; //<---- change this
final int   cycle_partitions    =   6;
final float hours_bet_colors 
            = cycle_time_in_hours / cycle_partitions;

//--------------------------------------------------------------
void setup(){
  
    print("hours between colors: ", hours_bet_colors);

    // housekeeping
    size(300, 300);
    background(0);
    colorMode(RGB, MAX_VAL, MAX_VAL, MAX_VAL);
    ellipseMode(RADIUS);
    frameRate(100);
    
    // array of times  and colors
    // indices of these two arrays correspond to one another
    main_color_times = initialize_color_times(hours_bet_colors);
    main_colors      = initialize_main_colors();

    print("\n------------------------\n");
    
}

void draw(){
  ellipse(150, 150, 100, 50);
  
  RgbColor crnt_rgb = map_time_to_color(main_color_times, main_colors);
  HsvColor crnt_hsv = rgb_to_hsv(crnt_rgb);
  RgbColor check = hsv_to_rgb(crnt_hsv);
  
  print("\n\n");
  crnt_rgb.print_me();
  
  print("\n");
  crnt_hsv.print_me();
  
  print("\n");
  check.print_me();
  
  set_clock_color(crnt_rgb);
  noStroke();
    
}

//--------------------------------------------------------------
// assigns current time to color as specified by arrays
// times and colors
//
// arguments:
// times  - array of times that correspond with main colors
// colors - array of main colors
//--------------------------------------------------------------
RgbColor map_time_to_color(float[] times, RgbColor[] colors){
  
  float hrs_since_midnight = get_hours_since_midnight();
  
  // figure out offset from beginning of cycle
  float multiple = hrs_since_midnight / cycle_time_in_hours;
  
  // 
  float temp =(int) multiple * cycle_time_in_hours;
  
  float hrs_since_cycle_restart = hrs_since_midnight - temp;
  
  if (hrs_since_cycle_restart < 0) hrs_since_cycle_restart = 0;
  
  print("\nhours since cycle restart: ", hrs_since_cycle_restart);
  
  int[] index              = get_indices_of_colors(times, hrs_since_cycle_restart);
  
  float fraction  = get_time_as_fractional_offset(times[index[0]],
                                                  times[index[1]], 
                                                  hrs_since_cycle_restart);
                                                  
  RgbColor crnt_color_time = interpolate_bet_colors(colors[index[0]], 
                                           colors[index[1]], fraction);
  
  return crnt_color_time;

}

//--------------------------------------------------------------
// calculates current time as a fraction between two times
//
// assumption:
// time0, time1 and crnt_time are in same units
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
  
  return fractional_offset;
}

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
// returns current time in units of hours since midnight
//--------------------------------------------------------------
float get_hours_since_midnight(){
  int    sec_since_midnight   = (SEC_IN_MIN * (hour() * MIN_IN_HR + minute()) + second());
  float  hours_since_midnight = (sec_since_midnight/(1.0 * SEC_IN_HR));
  
  print("\n-------");
  print("\nhours since midnight: ", hours_since_midnight);
  
  return hours_since_midnight;
}

//--------------------------------------------------------------
// initialize array that stores times of main colors
//
// assumption:
// times are in hours
//--------------------------------------------------------------
float [] initialize_color_times(float hours_between_colors) {

  float [] color_times = new float[cycle_partitions + 1];
  for (int i = 0; i < (cycle_partitions + 1); i++) {
    color_times[i] = i * (hours_between_colors);
    print("\ncolor_times index ", i, "----> hour ", color_times[i]);
  }
  
  return color_times;
}

//--------------------------------------------------------------
// initialize array that contains main colors
//--------------------------------------------------------------
RgbColor [] initialize_main_colors(){
  
  int len = cycle_partitions + 1;
  RgbColor [] colors = new RgbColor[len];
  
  for(int i = 0; i < cycle_partitions; i++){
    colors[i] = color_selection[i];
  }
  
  colors[cycle_partitions] = colors[0];
  
  return colors;
}

//--------------------------------------------------------------
// initialize array that contains main colors 
// currently hard-coded
//--------------------------------------------------------------
RgbColor [] initialize_color_selection(){
  
  RgbColor [] colors = new RgbColor[6];
  
  /*
  colors[0] = new RgbColor(0xFF, 0x00, 0x00);  // red
  colors[1] = new RgbColor(0xFF, 0xFF, 0x00);  // yellow
  colors[2] = new RgbColor(0x00, 0xFF, 0x00);  // green
  colors[3] = new RgbColor(0x00, 0xFF, 0xFF);  // cyan
  colors[4] = new RgbColor(0x00, 0x00, 0xFF);  // blue
  colors[5] = new RgbColor(0xFF, 0x00, 0xFF);  // magenta
  */
  
  
  colors[0] = new RgbColor(0xAA, 0x00, 0x00);  // red
  colors[1] = new RgbColor(0xAA, 0xAA, 0x00);  // yellow
  colors[2] = new RgbColor(0x00, 0xAA, 0x00);  // green
  colors[3] = new RgbColor(0x00, 0xAA, 0xAA);  // cyan
  colors[4] = new RgbColor(0x00, 0x00, 0xAA);  // blue
  colors[5] = new RgbColor(0xAA, 0x00, 0xAA);  // magenta
  
  return colors;
}

// figure out brightness using HSB or HLS the convert back to RGB
//--------------------------------------------------------------
// returns new RgbColor object that falls between two colors 
//
// assumption:
// color is in correct range and fraction is between 0 and 1
//--------------------------------------------------------------
RgbColor interpolate_bet_colors(RgbColor color1, 
                                RgbColor color2, 
                                float    fraction){
  
  // difference between color2 and color1
  int delta;
  
  delta = color2.r - color1.r;
  int newRed   = (int) (fraction * delta) + color1.r;
  
  delta = color2.g - color1.g;
  int newGreen = (int) (fraction * delta) + color1.g;
  
  delta = color2.b - color1.b;
  int newBlue  = (int) (fraction * delta) + color1.b; 
  
  return new RgbColor(newRed, newGreen, newBlue);
  
}
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
    hue = 60.0 * (((green_norm - blue_norm) / diff) + 360);
  
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
// function that fills ellipse with color
//
// argument:
// fill_color - color to fill object with
//--------------------------------------------------------------
void set_clock_color(RgbColor fill_color){
  fill(fill_color.r, fill_color.g, fill_color.b);
}
