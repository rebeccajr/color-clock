//--------------------------------------------------------------
// DESCRIPTION
// This class is for an object that represents a color in RGB
// format.
//
// Assumptions:  0 <= r, g, b < 255
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
