#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include "alpha-display.hpp"
#include "classes.hpp"
#include "debug.hpp"
#include "logic.hpp"
#include "time-calcs.hpp"
#include "rtc-clock.hpp"


void setup(){
  Serial.begin(9600);
  AlphaDisplay::the_alpha_display.begin(0x70);
  Wire.begin();
}


void loop(){
  RgbColor color;
  Debug::print_new_line();
  Debug::print_color(color);
  AlphaDisplay::write_flux_to_display();
  delay(1000);
}
