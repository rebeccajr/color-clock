/*
DS3231_test.pde
Eric Ayars
4/11

Test/demo of read routines for a DS3231 RTC.

Turn on the serial monitor after loading this to check if things are
working as they should.

*/

#include <DS3231.h>
#include <Wire.h>

DS3231 clock0;
bool century = false;
bool h12Flag;
bool pmFlag;
byte alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits;
bool alarmDy, alarmH12Flag, alarmPmFlag;

void setup() {
	// Start the I2C interface
	Wire.begin();
 
	// Start the serial interface
	Serial.begin(57600);
}

void loop() {
	
	// Start with the year
	Serial.print("2");
	if (century) {			// Won't need this for 89 years.
		Serial.print("1");
	} else {
		Serial.print("0");
	}
  Serial.print("\n---------------------------");
  Serial.print("\nyear:  ");
	Serial.print(clock0.getYear(), DEC);
	Serial.print(' ');
	
	// then the month
  Serial.print("\nmonth: ");
	Serial.print(clock0.getMonth(century), DEC);
	Serial.print(" ");
  
	// then the date
  Serial.print("\ndate:  ");
	Serial.print(clock0.getDate(), DEC);
	Serial.print(" ");
  
	// and the day of the week
  Serial.print("\nday:   ");
	Serial.print(clock0.getDoW(), DEC);
	Serial.print(" ");
  
	// Finally the hour, minute, and second
  Serial.print("\nhour:  ");
	Serial.print(clock0.getHour(h12Flag, pmFlag), DEC);
	Serial.print(" ");
  Serial.print("\nmin:   ");
	Serial.print(clock0.getMinute(), DEC);
	Serial.print(" ");
  Serial.print("\nsec:   ");
	Serial.print(clock0.getSecond(), DEC);
  Serial.print("");


 /*
	// Add AM/PM indicator
	if (h12Flag) {
		if (pmFlag) {
			Serial.print(" PM ");
		} else {
			Serial.print(" AM ");
		}
	} else {
		Serial.print(" 24h ");
	}
 
	// Display the temperature
	Serial.print("T=");
	Serial.print(clock0.getTemperature(), 2);
  
	// Tell whether the time is (likely to be) valid
	if (clock0.oscillatorCheck()) {
		Serial.print(" O+");
	} else {
		Serial.print(" O-");
	}
 
	// Indicate whether an alarm went off
	if (clock0.checkIfAlarm(1)) {
		//Serial.print(" A1!");
	}
 
	if (clock0.checkIfAlarm(2)) {
		//Serial.print(" A2!");
	}
 
	// New line on display
	Serial.println();
	
	// Display Alarm 1 information
	//Serial.print("Alarm 1: ");
	clock0.getA1Time(alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits, alarmDy, alarmH12Flag, alarmPmFlag);
	//Serial.print(alarmDay, DEC);
	if (alarmDy) {
		//Serial.print(" DoW");
	} else {
		//Serial.print(" Date");
	}
	Serial.print(' ');
	//Serial.print(alarmHour, DEC);
	Serial.print(' ');
	//Serial.print(alarmMinute, DEC);
	Serial.print(' ');
	//Serial.print(alarmSecond, DEC);
	Serial.print(' ');
	if (alarmH12Flag) {
		if (alarmPmFlag) {
			Serial.print("pm ");
		} else {
			Serial.print("am ");
		}
	}
	if (clock0.checkAlarmEnabled(1)) {
		Serial.print("enabled");
	}
	Serial.println();
 
	// Display Alarm 2 information
	Serial.print("Alarm 2: ");
	clock0.getA2Time(alarmDay, alarmHour, alarmMinute, alarmBits, alarmDy, alarmH12Flag, alarmPmFlag);
	Serial.print(alarmDay, DEC);
	if (alarmDy) {
		Serial.print(" DoW");
	} else {
		Serial.print(" Date");
	}
	Serial.print(" ");
	Serial.print(alarmHour, DEC);
	Serial.print(" ");
	Serial.print(alarmMinute, DEC);
	Serial.print(" ");
	if (alarmH12Flag) {
		if (alarmPmFlag) {
			Serial.print("pm");
		} else {
			Serial.print("am");
		}
	}
	if (clock0.checkAlarmEnabled(2)) {
		Serial.print("enabled");
	}
 
	// display alarm bits
  Serial.println();
	Serial.print("Alarm bits: ");
	Serial.println(alarmBits, BIN);

	Serial.println();*/
	delay(1000);
}
