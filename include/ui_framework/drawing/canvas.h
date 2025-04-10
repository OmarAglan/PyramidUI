/**
 * @file canvas.h
 * @brief Canvas drawing for the UI Framework
 */

#ifndef UI_FRAMEWORK_CANVAS_H
#define UI_FRAMEWORK_CANVAS_H

#include "color.h"
#include <stdint.h>

/* Forward declaration of Window structure */
struct Window;

/**
 * @brief Canvas structure
 */
typedef struct Canvas Canvas;

/**
 * @brief Create a new canvas
 * 
 * @param width Canvas width
 * @param height Canvas height
 * @return Canvas* Handle to the created canvas, NULL on failure
 */
Canvas* canvas_create(int width, int height);

/**
 * @brief Destroy a canvas
 * 
 * @param canvas Canvas to destroy
 */
void canvas_destroy(Canvas* canvas);

/**
 * @brief Clear the canvas with a color
 * 
 * @param canvas Canvas to clear
 * @param color Color to clear with
 */
void canvas_clear(Canvas* canvas, Color color);

/**
 * @brief Set a pixel on the canvas
 * 
 * @param canvas Canvas to set pixel on
 * @param x X coordinate
 * @param y Y coordinate
 * @param color Color to set
 */
void canvas_set_pixel(Canvas* canvas, int x, int y, Color color);

/**
 * @brief Get a pixel from the canvas
 * 
 * @param canvas Canvas to get pixel from
 * @param x X coordinate
 * @param y Y coordinate
 * @return Color Pixel color
 */
Color canvas_get_pixel(const Canvas* canvas, int x, int y);

/**
 * @brief Get canvas width
 * 
 * @param canvas Canvas to get width of
 * @return int Canvas width
 */
int canvas_get_width(const Canvas* canvas);

/**
 * @brief Get canvas height
 * 
 * @param canvas Canvas to get height of
 * @return int Canvas height
 */
int canvas_get_height(const Canvas* canvas);

/**
 * @brief Get canvas pixel data
 * 
 * @param canvas Canvas to get data from
 * @return const uint32_t* Canvas pixel data
 */
const uint32_t* canvas_get_data(const Canvas* canvas);

/**
 * @brief Render the canvas to a window
 * 
 * @param canvas Canvas to render
 * @param window Window to render to
 */
void canvas_render(const Canvas* canvas, struct Window* window);

#endif /* UI_FRAMEWORK_CANVAS_H */
