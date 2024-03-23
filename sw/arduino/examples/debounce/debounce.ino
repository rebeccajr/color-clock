//______________________________________________________________________________
// DESCRIPTION
// This program tests software debounce.
//
// This is currently broken because some files were deleted.
//______________________________________________________________________________

#include <Arduino.h>
#include "momentary-switch.hpp"


int red_pin = 0;
int grn_pin = 1;
int blu_pin = 2;
int button0 = 3;
int button1 = 4;

MomentarySwitch::InputType last_val = MomentarySwitch::InputType::NONE;
bool print_flag = 1;

bool red_val = LOW;
bool grn_val = LOW;
bool blu_val = LOW;
MomentarySwitch red;

//______________________________________________________________________________
void setup()
{
  pinMode(red_pin, OUTPUT);
  pinMode(grn_pin, OUTPUT);
  pinMode(blu_pin, OUTPUT);
  pinMode(button0, INPUT_PULLDOWN);
  pinMode(button1, INPUT);

  red = MomentarySwitch(red_pin);

}


//______________________________________________________________________________
void loop()
{
  int reading = digitalRead(button0);
  MomentarySwitch::InputType val = red.get_input_type(reading);

    if (int(val))
    {
      /*
      Serial.print("crnt input type: ");
      Serial.println(int(val));
      Serial.print("prev input type: ");
      Serial.println(int(last_val));
      */

      if (print_flag)
      {
        //Serial.println("______________________________________________");
        print_flag = 0;
      }

      if (true)//!int(last_val) && int(val))
      {
      //Serial.println("---");
      //Serial.println("loop:: !last_val && val");
      //Serial.println("---");
      //Serial.print("loop:: last_val: ");
      //Serial.print(int(last_val));
      //Serial.print("   new_val: ");
      //Serial.println(int(val));

      switch (val)
      {
      case MomentarySwitch::InputType::SHORT:
        red_val = !red_val;
        //Serial.println("SHORT");
        break;

      case MomentarySwitch::InputType::DOUBLE:
        grn_val = !grn_val;
        //Serial.println("DOUBLE");
        break;

      case MomentarySwitch::InputType::TRIPLE:
        red_val = 0;
        grn_val = 0;
        blu_val = 0;
        //Serial.println("TRIPLE");
        break;

      case MomentarySwitch::InputType::LONG:
        blu_val = !blu_val;
        //Serial.println("LONG");
        break;

      default:
        //Serial.println("NONE");
        break;
      }


      //Serial.print("loop:: led write value: ");
      //Serial.println(red_val);
      digitalWrite(red_pin, red_val);
      digitalWrite(blu_pin, blu_val);
      print_flag = 1;
      }
    }

  last_val = val;
}

//______________________________________________________________________________