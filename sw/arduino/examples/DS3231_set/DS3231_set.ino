/*
DS3231_set.pde
Eric Ayars
4/11

Test of set-time routines for a DS3231 RTC

*/

#include <DS3231.h>
#include <Wire.h>

DS3231 clock0;

uint8_t year;
uint8_t month;
uint8_t date;
uint8_t dOW;
uint8_t hour;
uint8_t minute;
uint8_t second;

void getDateStuff(uint8_t& year, uint8_t& month, uint8_t& date, uint8_t& dOW,
                  uint8_t& hour, uint8_t& minute, uint8_t& second) {
    // Call this if you notice something coming in on
    // the serial port. The stuff coming in should be in
    // the order YYMMDDwHHMMSS, with an 'x' at the end.
    boolean gotString = false;
    char inChar;
    uint8_t temp1, temp2;
    char inString[20];
    
    uint8_t j=0;
    while (!gotString) {
        if (Serial.available()) {
            inChar = Serial.read();
            inString[j] = inChar;
            j += 1;
            if (inChar == 'x') {
                gotString = true;
            }
        }
    }
    Serial.println(inString);
    // Read year first
    temp1 = (uint8_t)inString[0] -48;
    temp2 = (uint8_t)inString[1] -48;
    year = temp1*10 + temp2;
    // now month
    temp1 = (uint8_t)inString[2] -48;
    temp2 = (uint8_t)inString[3] -48;
    month = temp1*10 + temp2;
    // now date
    temp1 = (uint8_t)inString[4] -48;
    temp2 = (uint8_t)inString[5] -48;
    date = temp1*10 + temp2;
    // now Day of Week
    dOW = (uint8_t)inString[6] - 48;
    // now hour
    temp1 = (uint8_t)inString[7] -48;
    temp2 = (uint8_t)inString[8] -48;
    hour = temp1*10 + temp2;
    // now minute
    temp1 = (uint8_t)inString[9] -48;
    temp2 = (uint8_t)inString[10] -48;
    minute = temp1*10 + temp2;
    // now second
    temp1 = (uint8_t)inString[11] -48;
    temp2 = (uint8_t)inString[12] -48;
    second = temp1*10 + temp2;
}

void setup() {
    // Start the serial port
    Serial.begin(57600);
    
    // Start the I2C interface
    Wire.begin();

    
    
}

uint8_t set_hr  = 13;
uint8_t set_min = 54;

bool h12Flag;
bool pmFlag;

void loop() {
    
    Serial.print("\n---------------------------");
    Serial.print("\n---------------------------");
    Serial.print("\n before setting");
    Serial.print("\n---------------------------");
    Serial.print("\nhour:  ");
    Serial.print(clock0.getHour(h12Flag, pmFlag), DEC);
    Serial.print(" ");
    Serial.print("\nmin:   ");
    Serial.print(clock0.getMinute(), DEC);

    Serial.print("\n---------------------------");
    Serial.print("\n after setting");
    Serial.print("\n---------------------------");
    clock0.setHour(set_hr);
    clock0.setMinute(set_min);
    Serial.print("\nhour:  ");
    Serial.print(clock0.getHour(h12Flag, pmFlag), DEC);
    Serial.print(" ");
    Serial.print("\nmin:   ");
    Serial.print(clock0.getMinute(), DEC);
    Serial.print(" ");
    Serial.print("\nsec:   ");
    Serial.print(clock0.getSecond(), DEC);

    //if (!Serial.available())
      //Serial.print("Serial not available :(");
      
    // If something is coming in on the serial line, it's
    // a time correction so set the clock accordingly.
    if (Serial.available()) {

        Serial.print("serial available!!");
        getDateStuff(year, month, date, dOW, hour, minute, second);
        
        clock0.setClockMode(false);  // set to 24h
        //setClockMode(true); // set to 12h
        
        clock0.setYear(year);
        clock0.setMonth(month);
        clock0.setDate(date);
        clock0.setDoW(dOW);
        clock0.setHour(hour);
        clock0.setMinute(minute);
        clock0.setSecond(second);
        
        // Test of alarm functions
        // set A1 to one minute past the time we just set the clock
        // on current day of week.
        clock0.setA1Time(dOW, hour, minute+1, second, 0x0, true,
                        false, false);
        // set A2 to two minutes past, on current day of month.
        clock0.setA2Time(date, hour, minute+2, 0x0, false, false,
                        false);
        // Turn on both alarms, with external interrupt
        clock0.turnOnAlarm(1);
        clock0.turnOnAlarm(2);
        
    }
    delay(1000);
}
