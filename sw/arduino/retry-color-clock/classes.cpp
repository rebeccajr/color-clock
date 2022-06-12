#include "classes.hpp"

HsvColor RgbColor::to_hsv(){
    float red_norm   = this->r/255.0;
    float green_norm = this->g/255.0;
    float blue_norm  = this->b/255.0;
    
    // get max of normalized values
    float cmax = std::max(red_norm,
                 std::max(green_norm,
                          blue_norm));
    
    // get min of normalized values
    float cmin = std::min(red_norm,
                 std::min(green_norm,
                          blue_norm));
                     
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
