# Back In Development

I would like to make the ColorClock code base more robust, so I
decided to leverage some of the work I'm doing in my real job and
applying it to ColorClock.

## Google Test

During development of ColorClock Version 1, I did some rudimentary
unit tests and took the form of print statements in simple C++ programs.
I played around with writing makefiles but my unit tests were few and
far between.

In my latest work, I'm implementing a "real" unit testing framework in
using Google Test. Each module has its own test file and I'm using
make to build the unit test executable.

## Testing Limitations

Since ColorClock is designed to work with specific hardware, some of my
code isn’t easily testable using Google Test. However, much (or at least
some) of the hardware-dependent functionality is protected by
preprocessor directives, providing alternate behavior for non-hardware
builds. My goal is to test as much as possible.

## This Is Why We Test

So, I’ve started writing tests for the edge cases in the TimeCalcs
module, and guess what? I found some errors in one of the functions 😅
These didn’t show up in the deployment of ColorClock Version 1 because
of the specific use case, but as I look to expand the project’s
capabilities, they’re definitely issues that need to be addressed 😬

*Google Test Output for TimeCalcs*

```googletest
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from TimeCalcsGroup
[ RUN      ] TimeCalcsGroup.TimeAsFractionalOffset_Nominal
[       OK ] TimeCalcsGroup.TimeAsFractionalOffset_Nominal (0 ms)
[ RUN      ] TimeCalcsGroup.TimeAsFractionalOffset_Nominal_Swapped
[       OK ] TimeCalcsGroup.TimeAsFractionalOffset_Nominal_Swapped (0 ms)
[ RUN      ] TimeCalcsGroup.TimeAsFractionalOffset_Across_Midnight
/home/flux/git/color-clock/sw/test/build-test/../main/test-time-calcs.cpp:69: Failure
Value of: function_output == 0.75
  Actual: false
Expected: true

[  FAILED  ] TimeCalcsGroup.TimeAsFractionalOffset_Across_Midnight (0 ms)
[ RUN      ] TimeCalcsGroup.TimeAsFractionalOffset_Midnight_As_24_End
[       OK ] TimeCalcsGroup.TimeAsFractionalOffset_Midnight_As_24_End (0 ms)
[ RUN      ] TimeCalcsGroup.TimeAsFractionalOffset_Midnight_As_0_End
/home/flux/git/color-clock/sw/test/build-test/../main/test-time-calcs.cpp:95: Failure
Value of: function_output == 0.5
  Actual: false
Expected: true

[  FAILED  ] TimeCalcsGroup.TimeAsFractionalOffset_Midnight_As_0_End (0 ms)
[----------] 5 tests from TimeCalcsGroup (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 3 tests.
[  FAILED  ] 2 tests, listed below:
[  FAILED  ] TimeCalcsGroup.TimeAsFractionalOffset_Across_Midnight
[  FAILED  ] TimeCalcsGroup.TimeAsFractionalOffset_Midnight_As_0_End

 2 FAILED TESTS
```

## Build Flags

I have a file containing all my build flags, which is included in every
module. These macros include directives for enabling hardware-specific
functionality. One of the macros, DEBUG_CPP, is intended for
non-hardware builds. Until now, I’ve had to manually set this flag in
the macros file. To streamline things a bit, I created a simple Python
script that automatically uncommented the line:

```cpp
// #define DEBUG_CPP
```

and converts it to:

```cpp
#define DEBUG_CPP
```

In the Makefile for the unit tests, I create a phony target that runs
the Python script first before building out the unit test executable.

## File Headers

Another improvement I made to give the code a more professional look was
adding a comment header to each file. To make this process more
efficient, I wrote a Python script that automatically populates the
header in each file.

```cpp
//______________________________________________________________________
//______________________________________________________________________
//      _   __   _   _ _   _   _   _         _
// |   |_| | _  | | | V | | | | / |_/ |_| | /
// |__ | | |__| |_| |   | |_| | \ |   | | | \_
//  _  _         _ ___  _       _ ___   _                        / /
// /  | | |\ |  \   |  | / | | /   |   \                        (^^)
// \_ |_| | \| _/   |  | \ |_| \_  |  _/                        (____)o
//______________________________________________________________________
//______________________________________________________________________
//
//----------------------------------------------------------------------
// Copyright 2024, Rebecca Rashkin
// -------------------------------
// This code may be copied, redistributed, transformed, or built upon in
// any format for educational, non-commercial purposes.
//
// Please give me appropriate credit should you choose to use this
// resource. Thank you :)
//----------------------------------------------------------------------
//
//______________________________________________________________________
// //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\
//______________________________________________________________________
```

## Home Display

On a different note, we are also working on installing the light display
for ColorClock Version 1 in our house 😀

I powered it up for the first time since its display at Burning Man
2024, and I was beyond thrilled to see that not only did it work, but
the time was still accurate thanks to the real-time clock module 🎉

I’ll make sure to share more pictures once it’s wall-mounted.

## TODO

So, here are some TODOs that I will continue to pick away at...

- Write unit tests for modules:
  - TimeCalcs
  - RgbColor
  - HsvColor
  - ColorClock
  - TimeController
  - TimeDisplay
  - TopLevel

- Fix code for failures found during unit testing
- Create a pipeline that runs all unit tests
- Organize files
- Clean up non-Arduino code
- Prototype a sma
