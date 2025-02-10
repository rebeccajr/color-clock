#_______________________________________________________________________
#_______________________________________________________________________
#       _   __   _   _ _   _   _   _         _
#  |   |_| | _  | | | V | | | | / |_/ |_| | /
#  |__ | | |__| |_| |   | |_| | \ |   | | | \_
#   _  _         _ ___  _       _ ___   _                        / /
#  /  | | |\ |  \   |  | / | | /   |   \                        (^^)
#  \_ |_| | \| _/   |  | \ |_| \_  |  _/                        (____)o
#_______________________________________________________________________
#_______________________________________________________________________
#
#-----------------------------------------------------------------------
#  Copyright 2024, Rebecca Rashkin
#  -------------------------------
#  This code may be copied, redistributed, transformed, or built upon in
#  any format for educational, non-commercial purposes.
#
#  Please give me appropriate credit should you choose to use this
#  resource. Thank you :)
#-----------------------------------------------------------------------
#
#_______________________________________________________________________
#  //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\
#_______________________________________________________________________

#_______________________________________________________________________
# DESCRIPTION
# Makefile for ColorClock unit tests
#_______________________________________________________________________

#_______________________________________________________________________
# COMPILER OPTIONS
#_______________________________________________________________________
# Compiler and flags
CXX       = g++
CXXFLAGS  = -std=c++14

#_______________________________________________________________________
# GOOGLE TEST
#_______________________________________________________________________

# Google Test library flags
GTEST_DIR        = $(COLOR_CLOCK_TEST)/googletest
GTEST_INCLUDE    = $(GTEST_DIR)/include

GTEST_LIB        = -L$(GTEST_DIR)/lib
GTEST_LIBS       = -lgtest -pthread

#_______________________________________________________________________
# DIRECTORIES
#_______________________________________________________________________

# Directories for source, headers, and object files
COLOR_CLOCK_TEST = $(PWD)/..
TEST_SRC_DIR     = $(COLOR_CLOCK_TEST)/main

# Directory for object files and executable
OBJ_DIR = .

# Source code directory
COLOR_CLOCK_REPO = /home/flux/git/color-clock
COLOR_CLOCK_SRC  = $(COLOR_CLOCK_REPO)/sw/arduino/color-clock-driver

#_______________________________________________________________________
# SOURCE AND OBJECT FILES
#_______________________________________________________________________

# FluxClock files
FLUX_CLOCK     = $(COLOR_CLOCK_SRC)/flux-clock
FLUX_CLOCK_CPP = $(FLUX_CLOCK).cpp
FLUX_CLOCK_HPP = $(FLUX_CLOCK).hpp
FLUX_CLOCK_OBJ = $(OBJ_DIR)/test-flux-clock.o \
                 $(OBJ_DIR)/flux-clock.o

# RgbColor files
RGB     = $(COLOR_CLOCK_SRC)/rgb-color
RGB_CPP = $(RGB).cpp
RGB_HPP = $(RGB).hpp
RGB_OBJ = $(OBJ_DIR)/rgb-color.o \
          $(OBJ_DIR)/test-rgb-color.o

# HsvColor files
HSV     = $(COLOR_CLOCK_SRC)/hsv-color
HSV_CPP = $(HSV).cpp
HSV_HPP = $(HSV).hpp
HSV_OBJ = $(OBJ_DIR)/hsv-color.o \
          $(OBJ_DIR)/test-hsv-color.o

# TimeCalcs files
TIME_CALCS     = $(COLOR_CLOCK_SRC)/time-calcs
TIME_CALCS_CPP = $(TIME_CALCS).cpp
TIME_CALCS_HPP = $(TIME_CALCS).hpp
TIME_CALCS_OBJ = $(OBJ_DIR)/time-calcs.o \
                 $(OBJ_DIR)/test-time-calcs.o
#_______________________________________________________________________

# All include directories
# Not all are necessary everytime this variable is used
INCLUDES = -I$(COLOR_CLOCK_SRC) -I$(TEST_SRC_DIR) -I$(GTEST_INCLUDE)

# All objects
ALL_OBJ =               \
      $(FLUX_CLOCK_OBJ) \
      $(TIME_CALCS_OBJ) \
      $(RGB_OBJ)        \
      $(HSV_OBJ)        \
      $(EXE_OBJ)

SRC = $(TEST_SRC_DIR)/test-flux-clock.cpp $(SRC_DIR)/test-exe.cpp

EXE      = $(OBJ_DIR)/test-exe
EXE_OBJ  = $(EXE).o

# Default target
all: prebuild $(EXE)

prebuild:
	python3 add-debug-macros.py

#_______________________________________________________________________
# TARGET BUILDS
#_______________________________________________________________________
rgb-color.o: $(RGB_CPP) $(RGB_HPP)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(RGB_CPP)

test-rgb-color.o: $(TEST_SRC_DIR)/test-rgb-color.cpp $(RGB_HPP)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(TEST_SRC_DIR)/test-rgb-color.cpp

#_______________________________________________________________________
hsv-color.o: $(HSV_CPP) $(HSV_HPP)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(HSV_CPP)

test-hsv-color.o: $(TEST_SRC_DIR)/test-hsv-color.cpp $(HSV_HPP)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(TEST_SRC_DIR)/test-hsv-color.cpp

#_______________________________________________________________________
time-calcs.o: $(TIME_CALCS_CPP) $(TIME_CALCS_HPP)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(TIME_CALCS_CPP)

test-time-calcs.o: $(TEST_SRC_DIR)/test-time-calcs.cpp $(TIME_CALCS_HPP)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(TEST_SRC_DIR)/test-time-calcs.cpp

#_______________________________________________________________________
flux-clock.o: $(FLUX_CLOCK_CPP) $(FLUX_CLOCK_HPP)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(FLUX_CLOCK_CPP)

test-flux-clock.o: $(TEST_SRC_DIR)/test-flux-clock.cpp $(FLUX_CLOCK_HPP)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(TEST_SRC_DIR)/test-flux-clock.cpp

#_______________________________________________________________________
# Main target
#_______________________________________________________________________
test-exe.o: $(TEST_SRC_DIR)/test-exe.cpp $(FLUX_CLOCK_HPP)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(TEST_SRC_DIR)/test-exe.cpp

# Link everything into the final executable
$(EXE): $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) $(ALL_OBJ) -o $(EXE) $(GTEST_LIB) $(GTEST_LIBS)

# Clean up generated files
clean:
	rm -f $(OBJ_DIR)/*.o $(EXE)
#_______________________________________________________________________
