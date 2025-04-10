/**
 * @file color.c
 * @brief Color utilities implementation
 */

#include "../../include/ui_framework/drawing/color.h"

/* Define common colors */
const Color COLOR_BLACK = {0, 0, 0, 255};
const Color COLOR_WHITE = {255, 255, 255, 255};
const Color COLOR_RED = {255, 0, 0, 255};
const Color COLOR_GREEN = {0, 255, 0, 255};
const Color COLOR_BLUE = {0, 0, 255, 255};
const Color COLOR_YELLOW = {255, 255, 0, 255};
const Color COLOR_CYAN = {0, 255, 255, 255};
const Color COLOR_MAGENTA = {255, 0, 255, 255};
const Color COLOR_TRANSPARENT = {0, 0, 0, 0};

Color color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

Color color_rgb(uint8_t r, uint8_t g, uint8_t b) {
    return color_rgba(r, g, b, 255);
}

uint32_t color_to_uint32(Color color) {
    return (color.a << 24) | (color.b << 16) | (color.g << 8) | color.r;
}

Color color_from_uint32(uint32_t value) {
    Color color;
    color.r = value & 0xFF;
    color.g = (value >> 8) & 0xFF;
    color.b = (value >> 16) & 0xFF;
    color.a = (value >> 24) & 0xFF;
    return color;
}
