# A Beautiful Breadboard

Behold! The first design of the of the fully populated solderless breadboard!

<>

This to-scale-ish design contains all of the modules that will be present on the final circuit board for ColorClock. The user interface controls are not present on this board.

🌈


To streamline the final phase of hardware testing and preempt the challenges of electronic troubleshooting, I found it important to meticulously design the layout of the prototyping breadboard. I started this layout by looking at the datasheets, obtaining the dimensions of each module, and drawing each component to scale. Then I decided it would be actually be more functional if I were using units of breadboard holes (approximately 0.1" between holes) instead of true dimensions. To determine the size represented on the diagram I placed each module on the breadboard and noted how many holes they covered and the positioning of all the pins. The next step is to actually wire this thing up and get to testing with the real LED light display 🙌

# Clock Crafting
And on the topic of the light display, it's just about finished! My partner bought a plunge base and circle jig in order to cut the circle and route out pockets for the LED strips to rest in. I'm very pleased with the results 😀 We are using a reflective metallic finish to maximize the light output, and a sheet of translucent acrylic that will sit on top to diffuse the light.


<>

The final routed wood piece features outer rings designed to house RGB LED strips. Each ring will display colors corresponding to the current time in days, hours, and minutes. The center of the piece will have a flower-like shape of LEDs that will be controllable by participant interaction via user control panel.

<>

The LEDs are glued to the inside of the pockets, and the colored light will be reflected off the metallic finish.

# IO Expander Integration Trials

In my last post, I was working on integrating the [Arduino Nano ESP32](https://store.arduino.cc/products/nano-esp32) into the project. I successfully tested this board with the new [RTC module](https://www.adafruit.com/product/3013) and the new [alphanumeric display](https://www.adafruit.com/product/2158) 🤗 But then... I was in the process of testing the [IO expander](https://www.adafruit.com/product/4886) and ended up messing with my board configuration so much that I was no longer able to upload any code to the board. Thankfully, [ptillisch](https://forum.arduino.cc/u/ptillisch/summary) came to the rescue and resolved [my issue](https://forum.arduino.cc/t/arduino-cli-and-nano-esp32-cant-upload/1261931/5) 🥳

Though I was able to talk to the Nano board, I was unable to include the [library](https://github.com/adafruit/Adafruit_AW9523) to interface with the IO expander 😭 I chased my tail for a couple of weeks before I decided to move in a different direction (see notes).

The good news was that I could interface the IO expander with the [MKR 1000](https://docs.arduino.cc/hardware/mkr-1000-wifi) that I had been testing on before I got the Nano board. Sooooo I ordered two more Arduinos, the [MKR 1010](https://docs.arduino.cc/hardware/mkr-wifi-1010/) (they no longer make the MKR 1000) and decided to move forward.

# Can I Just Get Some Variable Voltage Control??

The plan:
- Use the **IO expander** for analog output (required to create the RGB color mixing)
- Use the **Arduino on-board GPIO** for digital input from user interface

When the new boards came in, I promptly began testing the IO expander. I was able to get the digitalWrite functions to work with ease, but I struggled with the analogWrite function. After days of banging my head against the wall 😖 my new contingency plan was to swap the IO functionality of the on-board Arduino GPIO and the IO expander, i.e. the IO expander for the digital IO and Arduino PWM for the RGB LED control.

ColorClock has four light strips and three variable voltage lines per strip (one for each red, green and blue) so I need exactly 12 PWM pins. According to the [product page](https://store-usa.arduino.cc/products/arduino-mkr-wifi-1010) for the MKR 1010, there are supposed to be 13 PWM pins on the board BUT one of those listed pins would be unusable for variable voltage output on ColorClock because it needed to be used for my I2C SCL required for communication to the various modules.

This PWM output count would leave me NO wiggle room if one of the pins didn't work as expected. My concern grew when I noticed that the [datasheet](https://docs.arduino.cc/resources/datasheets/ABX00023-datasheet.pdf) had conflicting information from the [product website](https://store-usa.arduino.cc/products/arduino-mkr-wifi-1010) on which pins were capable of PWM output (see the notes at the end of this post for more information).

So, to get some clarity, I manually tested each individual pin. I wrote a tiny test program and hooked up a simple circuit with an LED where I varied the output voltage. I observed the LED to see if the light got brighter as the value of the output increased. I discovered a more discrepancies between my empirical testing and the documentation (see notes).

<>

We spent the afternoon at a brewery where I performed my variable output voltage test while my partner played his Steam Deck killing zombies or something.

# Wiring Matters
The inconsistency between my findings and the documentation left me uneasy, so I went back to testing the IO expander with a minimal example. I knew my code was solid, so I double-checked the circuit wiring and sure enough, there was a mistake. After fixing it, I was able to see a variable output voltage on a multimeter using the analogWrite function using the IO expander 🎉 So now I'm back to the original plan of using the IO expander to control the lights, and the on-board GPIO for the digital inputs.

The voltage I measured with the multimeter didn’t quite match up with the input values I expected, so it looks like I’ll need to write some calibration functions so I can programmatically compensate for hardware characteristics.

# Moving Forward

So, next steps will be:
- Wire up the breadboard so beautifully depicted above.
- Characterize the RGB LED strip, so I can programmatically adjust for the non-linear relationship between the IO expander's output voltage and the visible color from the lights.

We've got 2 1/2 months and counting... 😅

---
# Notes

## IO Expander Adafruit AW9523
There have been others that have had issues integrating the Adafruit_AW9523 [library](https://github.com/adafruit/Adafruit_AW9523) with the Arduino Nano ESP32. Though the [GitHub issues page](https://github.com/adafruit/Adafruit_AW9523/issues/6) states that this issue was resolved, I'm not so sure it was...

## Arduino MKR 1010 PWM Pins
According to the MKR 1010 [product website](https://store-usa.arduino.cc/products/arduino-mkr-wifi-1010), the following pins are available for PWM out:
```
0 .. 8, 10, 12, A3, A4
```

According to the MKR 1010 [datasheet](https://docs.arduino.cc/resources/datasheets/ABX00023-datasheet.pdf) the following pins are available for PWM out:
```
0 .. 9
```

According to my empirical testing, the following pins are available for variable voltage output:
```
0 .. 8, 10, A3, A4, A0* **
```

\* I learned that the A0 pin provides a true analog output, not a PWM signal which is why it was listed on neither the website nor the datasheet as a PWM pin. [This page](https://resources.pcb.cadence.com/blog/2021-how-and-why-to-convert-analog-signals-to-pwm-signals) describes the difference between analog and PWM output.

\*\* Pins 9 and 12, as listed on the datasheet and website, respectively, did not produce a variable output voltage in my experiment.

---
LinkedIn post

Reflecting on Adam Grant's "Think Again," I've actively embraced the concept of pivoting in response to unexpected outcomes, as seen in my recent attempts to interface with an IO expander for ColorClock. With 10 weeks until delivery, integration testing for our art installation's MVP begins. Adaptability is crucial for project completion. #colorclockevolution

---
Instagram post

As some of you know, this year my partner and I are finally bringing to fruition a passion project I've been developing for a decade: ColorClock. It's been refreshing to channel my creative energy and technical skills into something personal. I'm thrilled to announce that we will be displaying this interactive art piece at Burning Man 2024 🤗 Creative expression is self-care.

I've been blogging about it at rebeccajr.com/color-clock



