//------------------------------------------------------------------------------
// DESCRIPTION
// The ColorClock is an RGB LED art piece that maps the current time
// to a color. The clock will cycle through a series of colors over a period
// of time. A viewer can tell the approximate time from the color 
// of the light.
//------------------------------------------------------------------------------
#include <Wire.h>
#include <DS3231.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "rgb-color.h"
#include "color-logic.h"

void  write_serial_time();
void  write_display_time();
void  write_flux_to_display();
void  get_rtc_time(byte* the_time, DS3231 clk);
float get_hrs_since_midnight(byte the_hr, byte the_min, byte the_sec);
void  set_millis_offset(int the_sec);

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
DS3231 clk;

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------

// constants associated with timing
            
int SEC_IN_MIN = 60;
int MIN_IN_HR  = 60;
int SEC_IN_HR  = SEC_IN_MIN * MIN_IN_HR;

// variables used to get offset of time in millis
int MILLIS_OFFSET = 0;
int prev_sec      = 0;

float hrs_since_midnight = 0;

byte set_hr  = 13;
byte set_min = 54;

bool h12Flag;
bool pmFlag;

// current time variables
byte rtc_hr;
byte rtc_min;
byte rtc_sec;
bool first_run = true;

void setup() {

  Serial.begin(9600);
  alpha4.begin(0x70);
  
  Wire.begin();

  initialize_color_times(main_color_times, HOURS_BET_COLORS);
  initialize_color_selection(color_selection);
  initialize_main_colors(main_colors);
}


//------------------------------------------------------------------------------
// the loop function runs over and over again forever
void loop() {

  // initialize clock
  if (first_run == true) {
    clk.setHour(set_hr);
    clk.setMinute(set_min);
    first_run = false;
  }

  // get clock info
  byte the_time[3];
  get_rtc_time(the_time, clk);
  
  rtc_hr  = the_time[2]; 
  rtc_min = the_time[1];
  rtc_sec = the_time[0];
  hrs_since_midnight = get_hrs_since_midnight(rtc_hr, rtc_min, rtc_sec);
  
  write_serial_time();
  //write_display_time();
  write_flux_to_display();

  delay(1000);
}


//------------------------------------------------------------------------------
// Writes the current time to the LED display
//------------------------------------------------------------------------------
void write_display_time(){

  alpha4.writeDigitAscii(3, 0x30 + rtc_sec % 10);
  alpha4.writeDigitAscii(2, 0x30 + rtc_sec / 10);
  alpha4.writeDigitAscii(1, 0x30 + rtc_min % 10);
  alpha4.writeDigitAscii(0, 0x30 + rtc_min / 10);


  alpha4.writeDigitAscii(0, 0x65);
  alpha4.writeDisplay();

}

void write_flux_to_display(){
  alpha4.writeDigitAscii(0, 'F');
  alpha4.writeDigitAscii(1, 'L');
  alpha4.writeDigitAscii(2, 'U');
  alpha4.writeDigitAscii(3, 'X');
  alpha4.writeDisplay();


}

//-------------------------------------------------------------------------------
// Write time to serial console
//-------------------------------------------------------------------------------
void write_serial_time(){
  Serial.print("\n---------------------------");
  Serial.print("\n---------------------------");
  Serial.print("\n clock stuff");
  Serial.print("\n---------------------------");

  Serial.print("\nhour:  ");
  Serial.print(rtc_hr, DEC);
  Serial.print(" ");
  Serial.print("\nmin:   ");
  Serial.print(rtc_min, DEC);
  Serial.print(" ");
  Serial.print("\nsec:   ");
  Serial.print(rtc_sec, DEC);

  Serial.print("\nhrs since midnight:   ");
  Serial.print(hrs_since_midnight, DEC);
}

//------------------------------------------------------------------------------
// Populates a byte array with the time from a Real Time Clock
//------------------------------------------------------------------------------
void get_rtc_time(byte* the_time, DS3231 clk){
  the_time[2] = clk.getHour(h12Flag, pmFlag);
  the_time[1] = clk.getMinute();
  the_time[0] = clk.getSecond();
}


//------------------------------------------------------------------------------
// Returns current time in units of hours since midnight
//------------------------------------------------------------------------------
float get_hrs_since_midnight(byte the_hr, byte the_min, byte the_sec) {
  
  set_millis_offset(the_sec);
  
  float ms = (millis() - MILLIS_OFFSET) % 1000;
  
  float  sec_since_midnight   
    = (SEC_IN_MIN * (the_hr * MIN_IN_HR + the_min) + 
       the_sec + ms / 1000);

  float  hours_since_midnight 
    = (sec_since_midnight/(1.0 * SEC_IN_HR));    
  return hours_since_midnight;
}


//------------------------------------------------------------------------------
// The function millis() returns the number of milliseconds
// since the beginning of program execution, while the functions
// second(), minute(), and hour() return the current second,
// minute, and hour of the day, respectively.
//
// The functon millis() is not coordinated with the time of day,
// so the following function, set_millis_offset is used to
// align the return value of millis() with the time of day.
//
// Every time a second passes, the millisecond offset between
// when the program started and the start of the last second
// is recalculated.
// 
// This function does not determine the precise millisecond of
// the current time, however, it suits the purposes of this
// program in that milliseconds will increase for the duration
// of a second in time, and then reset.
//------------------------------------------------------------------------------
void set_millis_offset(int the_sec){
  
  // check if beginning of new second
  if (prev_sec != the_sec){    
    MILLIS_OFFSET = millis();
  }
  
    prev_sec = the_sec;  
}
