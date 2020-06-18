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

// set constants
int MAX_VAL    = 255;
int MIN_VAL    = 0;
int SEC_IN_MIN = 60;
int MIN_IN_HR  = 60;
int SEC_IN_HR  = SEC_IN_MIN * MIN_IN_HR;


int []     main_color_times;
RgbColor[] main_colors;

float hours_bet_colors = 4;

void setup(){

    // housekeeping
    size(300, 300);
    background(0);
    colorMode(RGB, MAX_VAL, MAX_VAL, MAX_VAL);
    ellipseMode(RADIUS);
    frameRate(50);
    
    // array of times 
    main_color_times = initialize_color_times(hours_bet_colors);
    main_colors      = initialize_main_colors();

    print("\n------------------------\n");
    
}

void draw(){
  ellipse(150, 150, 100, 50);
  set_clock_color(map_time_to_color(main_color_times, main_colors));
  noStroke();
    
}

RgbColor map_time_to_color(int[] times, RgbColor[] colors){
  RgbColor crnt_color_time;
  
  float hrs_since_midnight = get_hours_since_midnight();
  int[] index              = get_indices_of_colors(times, hrs_since_midnight);
  
  float fraction  = get_time_as_fractional_offset(times[index[0]], times[index[1]], 
                                                  hrs_since_midnight);
                                                  
  crnt_color_time = interpolate_bet_colors(colors[index[0]], 
                                           colors[index[1]], fraction);
  
  return crnt_color_time;

}

// calculates current time as a fraction between two times
float get_time_as_fractional_offset(int time0, int time1, float crnt_time){
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
// color times that the current time falls between
// assumption that color times are in order
//
// arguments: color_times - array of times
int [] get_indices_of_colors (int[] color_times, float hours_since_midnight){
  
  int [] indices = new int[2];
  int i = 0;
  
  while (hours_since_midnight >= color_times[i]){
    
    if (hours_since_midnight == color_times[i]){
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

float get_hours_since_midnight(){
  int    sec_since_midnight   = (SEC_IN_MIN * (hour() * MIN_IN_HR + minute()) + second());
  float  hours_since_midnight = (sec_since_midnight/(1.0 * SEC_IN_HR));
  return hours_since_midnight;
}

// initialize array that stores times of main colors
// times are in hours
int [] initialize_color_times(float hours_between_colors) {

  int [] color_times = new int[7];
  for (int i = 0; i < 7; i++) {
    color_times[i] = i * int(hours_between_colors);
    print("color_times: ", i, "---->", color_times[i], "\n");
  }
  
  return color_times;
}

// initialize array that contains main colors 
// currently hard-coded
RgbColor [] initialize_main_colors(){
  
  RgbColor [] colors = new RgbColor[7];
  
  colors[0] = new RgbColor(0xFF, 0x00, 0x00);  // red
  colors[1] = new RgbColor(0xFF, 0xFF, 0x00);  // yellow
  colors[2] = new RgbColor(0x00, 0xFF, 0x00);  // green
  colors[3] = new RgbColor(0x00, 0xFF, 0xFF);  // cyan
  colors[4] = new RgbColor(0x00, 0x00, 0xFF);  // blue
  colors[5] = new RgbColor(0xFF, 0x00, 0xFF);  // magenta
  colors[6] = new RgbColor(0xFF, 0x00, 0x00);  // red
  
  return colors;
}

// assumption color is in correct range and fraction is between 0 and 1
RgbColor interpolate_bet_colors(RgbColor color1, RgbColor color2, float fraction){

  // difference between color2 and color 1
  int delta;
  
  delta = color2.r - color1.r;
  int newRed   = (int) (fraction * delta) + color1.r;
  
  delta = color2.g - color1.g;
  int newGreen = (int) (fraction * delta) + color1.g;
  
  delta = color2.b - color1.b;
  int newBlue  = (int) (fraction * delta) + color1.b;
  
  return new RgbColor(newRed, newGreen, newBlue);
  
}

// class that holds an rgb color
class RgbColor {
  int r;
  int g; 
  int b;
  RgbColor(){}

  // values normalized to 255
  RgbColor(int red, int green, int blue){
  
    r = red;
    g = green;
    b = blue;
    
  }
  
  // add constructor with values normalized to 1

}

void set_clock_color(RgbColor fill_color){
  fill(fill_color.r, fill_color.g, fill_color.b);
}
