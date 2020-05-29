/***************************************************************
Created by:    Rebecca

Description:   This program maps the time to a color.
***************************************************************/


int r, g, b;
int i;
int raw_time, sec_in_min, min_in_hr, sec_in_hr;
int minor_color, second_color;

int [] interval;
boolean time_interval;

float time, decimal, bin_size, offset;


void setup(){

    // housekeeping
    size(300, 300);
    background(0);
    colorMode(RGB, 255, 255, 255);
    ellipseMode(RADIUS);
    frameRate(50);
    
    // initialize rgb
    i = r = b = g = 0;

    sec_in_min = min_in_hr = 60;
    sec_in_hr = sec_in_min * min_in_hr;
    
    minor_color = 0;
    
    // bin_size: hours between colors:  red     0xFF0000
    //                                  yellow  0xFF0000
    //                                  green   0x00FF00 
    //                                  cyan    0x00FFFF
    //                                  blue    0x0000FF
    //                                  magenta 0xFF00FF
    bin_size = 4;
    
    time = 0;
    
    
    interval = new int[7];

    for (i = 0; i < 7; i++) {
      interval[i] = i * int(bin_size);
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

  // raw_time: number of seconds since midnight
  raw_time = (sec_in_min * (hour() * min_in_hr + minute()) + second());
  
  // normalized time: number of hours since midnight
  time = (raw_time/(1.0 * sec_in_hr));
  
  // this equation is used to determine where red starts <---- ???????
  time = (time + 2) % 24;

  // offset from bin - normalized as a fraction of bin size 
  decimal = (time % bin_size)/bin_size;
  
  // time interval: boolean noting that time is moving in direction of
  //                primary color (red green blue)
  //
  // false => moving towards primary color (red, green, blue)
  // true  => moving towards secondary color (yellow, cyan, magenta)
  time_interval = (int(time) % (bin_size * 2))  < (bin_size);
  
  // interval color 
  // 0        RED   22:00
  // 1        YEL    2:00
  // 2        GRN    6:00
  // 3        CYA   10:00
  // 4        BLU   14:00
  // 5        VIO   18:00
  
  print("int time: ", int(time), "\n");
  
  // offset from bin normalized to 255
  offset = decimal * 255;

  // !time_interval => moving towards R, G, B
  if (!time_interval) {
    second_color = 255 - int(offset);
    if (second_color < minor_color) {
      second_color = minor_color;
    }
  }
  
  // time_interval => moving towards yellow, cyan, magenta
  else {
    second_color = int(offset);
    if (offset < minor_color) second_color = minor_color;
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
  
  if (time >= interval[6]) time = 0;
  
  if (time >= interval[0] && time <= interval[1]) {
    r = 255;
    b = minor_color;
    g = second_color;
    print("red to yellow\n");
  }
  
  if (time >= interval[1] && time <= interval[2]) {
    r = second_color;
    b = minor_color;
    g = 255;
    print("yellow to green\n");
  }
  
  if (time >= interval[2] && time <= interval[3]) {
    g = 255;
    r = minor_color;
    b = second_color;
    print("green to cyan\n");
  }  
 
  if (time >= interval[3] && time <= interval[4]) {
    g = second_color;
    b = 255;
    r = minor_color;
    print("cyan to blue\n");
  }
 
  if (time >= interval[4] && time <= interval[5]) {
    b = 255;
    g = minor_color;
    r = second_color;
    print("blue to magenta\n");
  }
  
  if (time >= interval[5] && time <= interval[6]) {
    b = second_color;
    g = minor_color;
    r = 255;
    print("magenta to red\n");
  }
  
  debug_msg();
  
  set_colors();
  
  fill(r, g, b);
  noStroke();
    
  time = time + .1;
}

// depending on time, sets RGB values
int[] set_colors() {
  int [] rgb;
  rgb = new int[3];
  
  rgb[0] = 1;
  rgb[1] = 2;
  rgb[2] = 3;
  
  print("\n", rgb[0], rgb[1], rgb[2]);
  return rgb;
  
}

// prints values valuable for debugging
void debug_msg() {
  print("hour = ", hour(), "\n");  
  print("time = ", time, ", ", "decimal = ", decimal, ", offset = ", offset, ", ");
  print ("time_interval = ", time_interval, "\n");
  
  print("second_color = ", second_color, "; \n");
  print("r = ", r, ", g = ", g, ", b = ", b, ";\n");
  print("------------------------\n");
}
