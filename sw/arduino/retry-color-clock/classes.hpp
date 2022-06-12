#include <algorithm>
#include <cmath>

class RgbColor {

public:

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

  RgbColor(int rgb_hex){
    this->r = (rgb_hex & 0xFF0000) >> 16;
    this->g = (rgb_hex & 0x00FF00) >> 8;
    this->b = (rgb_hex & 0x0000FF);
  }

}; 


//--------------------------------------------------------------
// object that holds an HSV color
// assumptions:  0 <= hue < 360
//               0 <= sat < 100
//               0 <= val < 100
//--------------------------------------------------------------
class HsvColor {

public:
  float h;
  float s; 
  float v;

  HsvColor(){}

  HsvColor(float hue, float sat, float value){
  
    h = hue;
    s = sat;
    v = value;
 
  }
};


