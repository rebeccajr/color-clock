//--------------------------------------------------------------
// DESCRIPTION
// This file contains classes that represent an RGB and HSV
// color object.
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
//--------------------------------------------------------------
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
  
  // enables user to enter RGB values using a 6 digit hex int
  RgbColor(int rgb_hex){
    
    r = (rgb_hex & 0xFF0000) >> 16;
    g = (rgb_hex & 0x00FF00) >> 8;
    b = (rgb_hex & 0x0000FF);
     
  }
  
  // converts RgbColor to string
  String to_string(){
  
  return "red: "   + String(this->r, 3) +
         "; grn: " + String(this->g, 3) + 
         "; blu: " + String(this->b, 3);
  
  }

};
