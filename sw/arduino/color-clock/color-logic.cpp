#include "color-logic.hpp"
#include "color-classes.hpp"

float CYCLE_TIME_IN_HOURS =   12.0/3600; //<---- change this
float HOURS_BET_COLORS = CYCLE_TIME_IN_HOURS / CYCLE_PARTITIONS;

// max and min rgb values
int MAX_VAL       = 60;
int MIN_VAL       = 0;
int MAX_COLOR_VAL = 0xAA;
int MIN_COLOR_VAL = 0x11;

// RGB constants
RgbColor ABS_RGB_RED = RgbColor(0xFF0000);
RgbColor ABS_RGB_YEL = RgbColor(0xFFFF00);
RgbColor ABS_RGB_GRN = RgbColor(0x00FF00);
RgbColor ABS_RGB_CYA = RgbColor(0x00FFFF);
RgbColor ABS_RGB_BLU = RgbColor(0xFF00FF);
RgbColor ABS_RGB_MAG = RgbColor(0xFF00FF);

RgbColor RGB_RED = RgbColor(MAX_COLOR_VAL, MIN_COLOR_VAL, MIN_COLOR_VAL);
RgbColor RGB_YEL = RgbColor(MAX_COLOR_VAL, MAX_COLOR_VAL, MIN_COLOR_VAL);
RgbColor RGB_GRN = RgbColor(MIN_COLOR_VAL, MAX_COLOR_VAL, MIN_COLOR_VAL);
RgbColor RGB_CYA = RgbColor(MIN_COLOR_VAL, MAX_COLOR_VAL, MAX_COLOR_VAL);
RgbColor RGB_BLU = RgbColor(MIN_COLOR_VAL, MIN_COLOR_VAL, MAX_COLOR_VAL);
RgbColor RGB_MAG = RgbColor(MAX_COLOR_VAL, MIN_COLOR_VAL, MAX_COLOR_VAL);
