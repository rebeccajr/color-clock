/***************************************************************
 Created by:    Rebecca

 Description:   This program maps the current time to a color.
 
                Time is displayed as a colored ellipse.
                color will cycle through red, yellow, green,
                cyan, blue, and magenta with the following RGB
                values:
                
                red     0xFF0000
                yellow  0xFF0000
                green   0x00FF00 
                cyan    0x00FFFF
                blue    0x0000FF
                magenta 0xFF00FF
                
***************************************************************/


   


int r, g, b;
int sec_since_midnight;

int minor_color, second_color;

// set constants
int MAX_VAL    = 255;
int SEC_IN_MIN = 60;
int MIN_IN_HR  = 60;
int SEC_IN_HR  = SEC_IN_MIN * MIN_IN_HR;


int [] interval;
boolean time_interval;

float hours_since_midnight, fractional_offset_from_color, hours_bet_colors;
int normalized_offset;


void setup(){

    // housekeeping
    size(300, 300);
    background(0);
    colorMode(RGB, MAX_VAL, MAX_VAL, MAX_VAL);
    ellipseMode(RADIUS);
    frameRate(50);
    
    // initialize rgb
    r = b = g = 0;
    
    minor_color = 0;
    
    // hours_bet_colors: hours between each of 6 colors
    hours_bet_colors = 1;
    
    interval = new int[7];

    for (int i = 0; i < 7; i++) {
      interval[i] = i * int(hours_bet_colors);
      print("interval: ", i, "---->", interval[i], "\n");
    }

    print("------------------------\n");

    
    /* 
    interval corresponds with hour number
    
    interval:  0 ----> hour  0:00
    interval:  1 ----> hour  4:00
    interval:  2 ----> hour  8:00
    interval:  3 ----> hour 12:00
    interval:  4 ----> hour 16:00
    interval:  5 ----> hour 20:00
    interval:  6 ----> hour 24:00
    */
    
}

void draw(){
  ellipse(150, 150, 100, 50);

  // returns current time as an offset from the last major color
  get_time_as_normalized_offset(hours_bet_colors);
  
  // time interval: boolean noting that time is moving in direction of
  //                primary color (red green blue)
  //
  // false => moving towards primary color (red, green, blue)
  // true  => moving towards secondary color (yellow, cyan, magenta)
  time_interval = (int(hours_since_midnight) % (hours_bet_colors * 2))  < (hours_bet_colors);
  
  // interval color 
  // 0        RED   22:00
  // 1        YEL    2:00
  // 2        GRN    6:00
  // 3        CYA   10:00
  // 4        BLU   14:00
  // 5        VIO   18:00
  
  print("int hours_since_midnight: ", int(hours_since_midnight), "\n");
 

  // !time_interval => moving towards R, G, B
  if (!time_interval) {
    second_color = MAX_VAL - normalized_offset;
    if (second_color < minor_color) {
      second_color = minor_color;
    }
  }
  
  // time_interval => moving towards yellow, cyan, magenta
  else {
    second_color = normalized_offset;
    if (normalized_offset < minor_color) second_color = minor_color;
  }
  
    /*
    interval:  0 ----> 0    red 
    interval:  1 ----> 4    yel
    interval:  2 ----> 8    grn
    interval:  3 ----> 12   cya
    interval:  4 ----> 16   blu
    interval:  5 ----> 20   vio
    interval:  6 ----> 24   red
    */
  
  if (hours_since_midnight >= interval[6]) hours_since_midnight = 0;
  
  if (hours_since_midnight >= interval[0] && hours_since_midnight <= interval[1]) {
    r = MAX_VAL;
    b = minor_color;
    g = second_color;
    print("red to yellow\n");
  }
  
  if (hours_since_midnight >= interval[1] && hours_since_midnight <= interval[2]) {
    r = second_color;
    b = minor_color;
    g = MAX_VAL;
    print("yellow to green\n");
  }
  
  if (hours_since_midnight >= interval[2] && hours_since_midnight <= interval[3]) {
    g = MAX_VAL;
    r = minor_color;
    b = second_color;
    print("green to cyan\n");
  }  
 
  if (hours_since_midnight >= interval[3] && hours_since_midnight <= interval[4]) {
    g = second_color;
    b = MAX_VAL;
    r = minor_color;
    print("cyan to blue\n");
  }
 
  if (hours_since_midnight >= interval[4] && hours_since_midnight <= interval[5]) {
    b = MAX_VAL;
    g = minor_color;
    r = second_color;
    print("blue to magenta\n");
  }
  
  if (hours_since_midnight >= interval[5] && hours_since_midnight <= interval[6]) {
    b = second_color;
    g = minor_color;
    r = MAX_VAL;
    print("magenta to red\n");
  }
  
  debug_msg();
  
  set_colors();
  
  fill(r, g, b);
  noStroke();
    
  hours_since_midnight = hours_since_midnight + 1;
}

// depending on time, sets RGB values
int[] set_colors() {
  int [] rgb;
  rgb = new int[3];
  
  rgb[0] = 1;
  rgb[1] = 2;
  rgb[2] = 3;
  
  //print("\n", rgb[0], rgb[1], rgb[2]);
  return rgb;
  
}


// returns offset from last main color, normalized to 255
int get_time_as_normalized_offset(float hours_bet_colors) {

  sec_since_midnight   = (SEC_IN_MIN * (hour() * MIN_IN_HR + minute()) + second());
  hours_since_midnight = (sec_since_midnight/(1.0 * SEC_IN_HR));
  
  // this equation is used to determine where red starts <---- ???????
  hours_since_midnight = (hours_since_midnight + 2) % 24;

  // offset from bin - normalized as a fraction of bin size (hours between colors)
  fractional_offset_from_color = (hours_since_midnight % hours_bet_colors)/hours_bet_colors;
  
  // offset from bin normalized to MAX_VAL
  normalized_offset = int(fractional_offset_from_color * MAX_VAL);
  
  return normalized_offset;

}

// prints values valuable for debugging
void debug_msg() {
  print("hour = ", hour(), "\n");  
  print("hours_since_midnight = ", hours_since_midnight, ", ", "fractional_offset_from_color = ", fractional_offset_from_color, ", normalized_offset = ", normalized_offset, ", ");
  print ("time_interval = ", time_interval, "\n");
  
  print("second_color = ", second_color, "; \n");
  print("r = ", r, ", g = ", g, ", b = ", b, ";\n");
  print("------------------------\n");
}
