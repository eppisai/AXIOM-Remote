#include "catch2/catch.hpp"
#include <iostream>

uint16_t width = 10, height = 10;
uint16_t* framebuffer = new uint16_t[width * height];
uint16_t* transitionframebuffer = new uint16_t[width * height];