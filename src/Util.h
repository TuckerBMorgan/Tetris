#pragma once
#include <stdio.h>
#include <stdint.h>

//a catchall single place for color
//Choose uint8_t as that is what the ColorMod function of SDL takes
struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};