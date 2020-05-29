/***************************************************************
Created by:    Rebecca

Description:   This program maps the time to a color.
***************************************************************/


int r, g, b, i, raw_time, sec_in_min, min_in_hr, sec_in_hr, minor_color, second_color;
int [] interval;
boolean time_interval;
float time, decimal, bin_size, c;


void setup(){

    size(300, 300);
    background(0);
    colorMode(RGB, 255, 255, 255);
    ellipseMode(RADIUS);
    frameRate(50);
    
    i = r = b = g = 0;

    sec_in_min = min_in_hr = 60;
    sec_in_hr = sec_in_min * min_in_hr;
    
    minor_color = 0;
    
    // time between colors - red, yellow, green, cyan, blue, magenta
    bin_size = 4;
    
    //bin_size = 1;
    time = 0;
    
    interval = new int[7];
    for (i = 0; i < 7; i++) {
      interval[i] = i * int(bin_size);
      print("interval: ", i, "---->", interval[i], "\n");
    }

    print("------------------------\n");

    
    /*
    interval:  0 ----> 0 
    interval:  1 ----> 4 
    interval:  2 ----> 8 
    interval:  3 ----> 12 
    interval:  4 ----> 16 
    interval:  5 ----> 20 
    interval:  6 ----> 24 
    */
    
}

void draw(){
  ellipse(150, 150, 100, 50);
  
  // second number in day
  raw_time = (sec_in_min * (hour() * min_in_hr + minute()) + second());
  
  // normalized time
  time = (raw_time/(1.0 * sec_in_hr));
  
  // determine where red starts
  time = (time + 2) % 24;

  decimal = (time % bin_size)/bin_size;
  
  // is color moving away from red, green, or blue?
  // 0 => moving towards red, green, blue
  // 1 => moving towards yellow, cyan, magenta
  time_interval = (int(time) % (bin_size * 2))  < (bin_size);

  // 0   RED 22   0
  // 1   YEL 02   4
  // 2   GRN 06   8
  // 3   CYA 10   12
  // 4   BLU 14   16
  // 5   VIO 18   20
  
  print("int time: ", int(time), "\n");
  
  // fraction between major colors
  c = decimal * 255;

  // !time_interval => moving towards R, G, B
  if (!time_interval) {
    second_color = 255 - int(c);
    if (second_color < minor_color) {
      second_color = minor_color;
    }
  }
  
  // time_interval => moving towards yellow, cyan, magenta
  else {
    second_color = int(c);
    if (c < minor_color) second_color = minor_color;
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
  print("time = ", time, ", ", "decimal = ", decimal, ", c = ", c, ", ");
  print ("time_interval = ", time_interval, "\n");
  
  print("second_color = ", second_color, "; \n");
  print("r = ", r, ", g = ", g, ", b = ", b, ";\n");
  print("------------------------\n");
}