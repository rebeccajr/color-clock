## Mind your parens

I was cleaning up my code of magic numbers and added a few `#define` statements for the frequency values. But after uploading the program to the board I didn't understand why the the colors on the light were not changing at the correct rate. So I added a couple serial output debug prints saw that my frequency was not set properly.

---

### Code
```cpp
// Time constants
#define SECONDS_PER_MIN   60.0
#define MINUTES_PER_HOUR  60.0
#define SECONDS_PER_HOUR  SECONDS_PER_MIN * MINUTES_PER_HOUR 

// Cycle time for ColorClock object 0
// Should equal 0.00333____
#define CC0_CYCLE_TIME_HOURS 12.0 / SECONDS_PER_HOUR

//...

Serial.print("SECONDS_PER_HOUR:     ");
Serial.println(SECONDS_PER_HOUR);
Serial.print("CC0_CYCLE_TIME_HOURS: ");
Serial.println(CC0_CYCLE_TIME_HOURS);
```

### Serial Output
I was expecting `CC0_CYCLE_TIME_HOURS` to print as `0.00333` or even `0.00`. Why was it printing 12.00??
```
CC0_CYCLE_TIME_HOURS: 12.00
SECONDS_PER_HOUR:     3600.00
```

I figured out that it had something to do with my `#define` statement. I stared at the code for way too long before deciding to do away with the `SECONDS_PER_HOUR` constant and just hard code the values directly:
```cpp
#define CC0_CYCLE_TIME_HOURS 12.0 / 3600.00
```

And this worked, so whatever. I just figured that the Arduino compiler is weird and doesn't treat preprocessor directives the same as gcc. I started writing this post to complain about the Arduino compiler, so to illustrate my point, I coded up the following simple program to compile on my desktop.

### Code
```cpp
#include <stdio.h>

#define SECONDS_PER_MIN   60.0
#define MINUTES_PER_HOUR  60.0
#define SECONDS_PER_HOUR  SECONDS_PER_MIN * MINUTES_PER_HOUR 

#define CC0_CYCLE_TIME_HOURS 12.0 / SECONDS_PER_HOUR

int main()
{
  printf("\nSECONDS_PER_HOUR:     %f", SECONDS_PER_HOUR);
  printf("\nCC0_CYCLE_TIME_HOURS: %f", CC0_CYCLE_TIME_HOURS);

  return 0;
}
```

But then to my surprise, the console output displayed the same value as the Arduino serial out!

### Console Output
```cpp
SECONDS_PER_HOUR:     3600.000000
CC0_CYCLE_TIME_HOURS: 12.000000
```

I stared at the code again and realized that the lack of parenthesis in the definition for `SECONDS_PER_HOUR` was the source of my problem. The `#define` macro is a simple find and replace, so what the compiler saw was:

```cpp
#define SECONDS_PER_MIN   60.0
#define MINUTES_PER_HOUR  60.0

// The compiler sees:
// #define SECONDS_PER_HOUR  60.0 * 60.0
#define SECONDS_PER_HOUR  SECONDS_PER_MIN * MINUTES_PER_HOUR 

// The compiler sees:
// #define CC0_CYCLE_TIME_HOURS 12.0 / 60.0 * 60.0
#define CC0_CYCLE_TIME_HOURS 12.0 / SECONDS_PER_HOUR
```

The compiler was basically seeing 12 / 60 * 60 instead of 12 / (60 * 60). And because of order of operations, `CC0_CYCLE_TIME_HOURS` was indeed 12, not the 0.003333 that I was hoping for 🤦‍♀️

---

## We did it live!

A couple months ago we decided to schedule a live demo as motivation to get the project finished a few weeks before leaving. The looming date of the demo gave us the motivation to finish with exactly one weekend to spare to get ready 😵‍💫

Last weekend was the demo and it was a success! I started out the event with a presentation where I discussed some of concepts of RGB LEDs, how a level shifter works, and went over the wiring of the circuit board. After scrambling to get it all wired up (which involved an embarrassing number of aligator clips) I threw together the slide deck and was excited to feel like a teacher again.


*Here is the final wiring of the circuit board. Isn't it beautiful?* 🥰

---
## No regrets

For a long time, I regretting getting my bachelor's in electrical rather than computer engineering. Often enough I have questions about software engineering design concepts that might have been answered had I chosen a different major. However, while working on ColorClock I realize that my degree gave me familiarity with electronic components and datasheets that I might not have gotten with a different undergraduate focus. And for the first time since I graduated, I sincerely have no regrets about my choice.

A lot has happened since the last post, including completely resoldering a new circuit board followed by a very sad afternoon where I was ready to give up after burning *another* Arduino board. But Bo came to the rescue and discovered that it was just a grounding problem.

---
# The final touches

This is our last weekend before we deliver and I'm thrilled that we are really just putting on the final touches. Although I learned today that last minute software changes can be quite risky.

[](https://youtu.be/9BzPTI5HZrY)
*I decided to change the initial colors for the the participant controlled central light, but because of the wonky logic for how the buttons interact with the colors, I got less ideal results.*

https://youtu.be/CMCiZth6IXw
*I reverted my software change and now it's working* 🥳



---

This weekend I'm finally at the point that I wanted to be *last* weekend. After spending almost all of last Saturday soldering I learned that powering the Arduino with 12 volts no bueno 😵 But I knew I had some LM7805s (5 volt linear regulators) somewhere. Then a series of unfortunate events ensued...

- Soldered it too close to where the Arduino was supposed to go
- Battled with desoldering, surrendered the part
- Soldered in a new voltage regulator
- Realized I soldered it in backward
- Added new wires to make it work
- Plugged in the wrong Arduino board because it had the same footprint
- Realized level shifter wasn't working
- Battled with desoldering the headers from the component
- Gave up and soldered on longer pins
- Wired everything and found the on board buttons weren't working when the lights were on
- Fried my Arduino board while debugging

```cpp
#define SECONDS_PER_MIN   60.0
#define MINUTES_PER_HOUR  60.0
#define SECONDS_PER_HOUR  SECONDS_PER_MIN * MINUTES_PER_HOUR 
#define CC0_CYCLE_TIME_HOURS 12.0 / SECONDS_PER_HOUR
//...
Serial.print("CC0_CYCLE_TIME_HOURS: ");
Serial.println(CC0_CYCLE_TIME_HOURS);
Serial.print("SECONDS_PER_HOUR:     ");
Serial.println(SECONDS_PER_HOUR);
```
Output
```
CC0_CYCLE_TIME_HOURS: 12.00
SECONDS_PER_HOUR:     3600.00
```
