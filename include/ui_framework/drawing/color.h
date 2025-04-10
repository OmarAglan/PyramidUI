/**
 * @file color.h
 * @brief Color utilities for the UI Framework
 */

#ifndef UI_FRAMEWORK_COLOR_H
#define UI_FRAMEWORK_COLOR_H

#include <stdint.h>

/**
 * @brief Color structure
 */
typedef struct {
    uint8_t r; /**< Red component (0-255) */
    uint8_t g; /**< Green component (0-255) */
    uint8_t b; /**< Blue component (0-255) */
    uint8_t a; /**< Alpha component (0-255) */
} Color;

/**
 * @brief Create a color from RGBA components
 * 
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @param a Alpha component (0-255)
 * @return Color The resulting color
 */
Color color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Create a color from RGB components (alpha = 255)
 * 
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @return Color The resulting color
 */
Color color_rgb(uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Convert a color to a 32-bit integer (RGBA)
 * 
 * @param color Color to convert
 * @return uint32_t 32-bit integer representation
 */
uint32_t color_to_uint32(Color color);

/**
 * @brief Create a color from a 32-bit integer (RGBA)
 * 
 * @param value 32-bit integer representation
 * @return Color The resulting color
 */
Color color_from_uint32(uint32_t value);

/* Common colors */
extern const Color COLOR_BLACK;
extern const Color COLOR_WHITE;
extern const Color COLOR_RED;
extern const Color COLOR_GREEN;
extern const Color COLOR_BLUE;
extern const Color COLOR_YELLOW;
extern const Color COLOR_CYAN;
extern const Color COLOR_MAGENTA;
extern const Color COLOR_TRANSPARENT;

#endif /* UI_FRAMEWORK_COLOR_H */
