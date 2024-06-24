#include <Arduino.h>
#include <CD74HC4067.h>
#include <stdint.h>

#include "flux-macros.hpp"
#include "debug.hpp"
#include "rgb-color.hpp"

uint8_t common_pin = 4;
uint8_t mux_s0 = 0;
uint8_t mux_s1 = 1;
uint8_t mux_s2 = 2;
uint8_t mux_s3 = 3;

RgbColor color;
using Rgb = RgbColor::PriColor;

CD74HC4067 muxxy(mux_s0, mux_s1, mux_s2, mux_s3);

void setup()
{
    pinMode(common_pin, OUTPUT);
    color = RgbColor(0xFF00FF);
}

void loop()
{
    muxxy.channel(0);
    analogWrite(common_pin, color.rgb_[Rgb::RED]);
    //analogWrite(common_pin, 0);
    muxxy.channel(1);
    analogWrite(common_pin, color.rgb_[Rgb::GRN]);
    //analogWrite(common_pin, 0);
    //Debug::print_labeled_int("green val: ", color.rgb_[Rgb::GRN]);
    //muxxy.channel(2);
    //analogWrite(common_pin, color.rgb_[Rgb::BLU]);
}

