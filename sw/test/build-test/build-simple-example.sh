#_______________________________________________________________________
# This script contains the commands to build and run the simple example
#_______________________________________________________________________

export GTEST_LIB=../googletest/
export GTEST_H=../googletest/include/
export FLUX_CLOCK_INCLUDE=../../arduino/color-clock-driver/
export FLUX_CLOCK=../../arduino/color-clock-driver/flux-clock.cpp
#_______________________________________________________________________
# Compile Step
#_______________________________________________________________________
# $GTEST_H is the location of gtest/gtest.h as indicated in code
# The version of Google Test used here requires C++14 or later
#_______________________________________________________________________
g++ \
  -std=c++14 -c           \
  -I$GTEST_H              \
  -I$FLUX_CLOCK_INCLUDE   \
  ../main/test-exe.cpp    \
  $FLUX_CLOCK

#_______________________________________________________________________
# Link Step
#_______________________________________________________________________
# $GTEST_LIB is the location of libgtest.a
#_______________________________________________________________________
g++ \
  test-exe.o    \
  flux-clock.o  \
  -L$GTEST_LIB  \
  -lgtest       \
  -pthread      \
  -o test.out


