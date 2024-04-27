Build flags? Please?
Every software hurdle feels like an epic journey. My latest challenge was learning how to set build flags.


Background
I have a class called ColorClock with a member variable, clock_, which is of type DS3231, a real-time clock (RTC) module that keeps time. There's a simple API to interact with this object over I2C. A ColorClock object uses clock_ to get the current time in order to determine which color to display.  E.g.

#include <DS3231.h>  

class ColorClock {
  private:
    DS3231 clock_;

  //...
}

RgbColor ColorClock::time_to_color() {
  //...

  float the_hr  = (float) clock_->get_hr();

  //...
}
Right now the only application for a ColorClock object is in the the context of the physical light installation. However, there might be an application in the future where I want to use the `ColorClock` class in a different project with different hardware, or just for a general purpose computer application. Due to the possibility of using this code with a variety of different hardware configurations, I wanted to make the ColorClock class more modular, and not have the code directly tied to the RTC module mentioned above.


So, I decided to make a wrapper class for the clock, which I'm going to call FluxClock*. The intention of this class would be a general clock object that I can use to get or set the time. I would have build environment variables that tell the compiler to include or exclude certain parts of the code. For example, the FluxClock::get_month() function would look like this:

#if ARDUINO_BUILD
#include <DS3231.h>
#else
#include <ctime>
#endif
//_________________________________________________________________
byte FluxClock::get_month()
{
#if ARDUINO_BUILD //_________________________________________________________________
// The century_bit toggles when there is roll-over to a new
// century, e.g. from year 2099 to 2100. The century_bit will
// likely never be relevant for any use case for this code base.
//_________________________________________________________________
  bool century_bit;
  return rtc_.getMonth(century_bit);
#else
  time(&clock_);
  time_ = localtime(&clock_);
  return time_->tm_mon;
#endif
}
//_________________________________________________________________
My challenge was to figure out how to set these build environment variables so that the compiler would only compile what was necessary for the specific build configuration.


The things that didn't work

Define it in a header file
Initially, I included the macro definition, ARDUINO_BUILD in a separate file called macros.h:

#define ARDUINO_BUILD 1
I included macros in ColorClock.hpp:

#include "macros.h"
A more experienced software engineer, or even just someone who's taken a compiler class (it's on my list of things to do) would probably know immediately why this didn't work. But with my limited time, I was less interested in the why-it-doesn't-work part; I was more in the in the how-do-I-get-it-to-work mindset (though feel free to school me on this topic).


Build properties in arduino.json
For reasons mentioned in a previous post, I (was) using the Microsoft Visual Studio Code Arduino plugin to build and upload my code. The internet told me that I could set build environment variables in the arduino.json file but this didn't work either 😕


(I don't actually remember the syntax I used in arduino.json - maybe something with defines (?)  - otherwise I would have included it here as something not to do...)


Windows Arduino Command Line
So then I decided to ditch the plugin and go back to command line using arduino-cli (on Windows).  I tried using the arduino-cli command in Git Bash, and PowerShell but Windows didn't recognize the command. So I downloaded arduino-cli and stuck the arduino-cli.exe file right in my code directory and Git Bash finally found it when I ran ./arduino-cli. I realize now that I probably just needed to add the location of arduino-cli.exe to my path, but yeah, I was just in a frenzy trying to get something to work. I made a minimal example without any build flags and spent way too much time just figuring out how to set the right serial port so I could upload the code to the board. But I was able to figure that part out.


Now on to the build flags problem... I tried many variations of setting a build flag (FLUX) in the command line argument of arduino-cli compile. But the compiler spit out all sorts of weird errors with every variation. Don't use this command, it doesn't work:

arduino-cli compile --fqbn arduino:samd:mkr1000 --build-properties build.extra_flags=-DFLUX=42

Old tech with a config file
I gave up on Windows and went back to my 10 year old MacBook and started from scratch with my familiar, safe, UNIX command line. I did more internetting (with my friend ChatGPT) and found that I should be able to set build flags in an arduino config file.

build:
  properties:
    FLUX:"42"
I set the config file path in my command line argument...

arduino-cli compile --fqbn arduino:samd:mkr1000 --config-file path/to/arduino_cli.yaml

but nope, this didn't work either. ChatGPT failed me. It then clarified that that the compiler might not actually recognize the flag 😐


And now the thing that worked

Deep in the Arduino installation directory...
Once again, after spending what seemed like ages (but was probably closer to an hour) searching on the internet and more talking to ChatGPT, I learned that I needed to edit the platform.txt file deep inside my install directory: 

Users/rebeccarashkin/Library/Arduino15/packages/arduino/hardware/samd/1.8.13/
and set my build flags in build.extra_flags:

build.extra_flags= -DFLUX=42
But this didn't work either! However, I did see a note just above the build.extra_flags line that said "These can be overridden in platform.local.txt" so I figured build.extra_flags might be getting overridden in the build process. I also read somewhere that I can also edit build flags in boards.txt. So I opened boards.txt in the same directory and found the build.extra_flags variable for my board and appended the variable that corresponded with my Arduino board, the MKR 1000

mkr1000.build.extra_flags= -DFLUX=42
Eureka! 🥳


FINALLY the compiler recognized my build flag.


It worked, but come on.
However, digging that deep into an installation directory just to set a build flag seems a little excessive, so I'd like to learn more about the platform.local.txt file. Buuuut.... for now, I really only have one build flag that I care about and I'm ok hacking my way through setting a build flag if it means I can progress in my development.


Ok, now what was I trying to do again? 😅


* Flux was my beloved rabbit companion for over 10 years and died in 2019. His memory lives on in nearly all of my software engineering endeavors.