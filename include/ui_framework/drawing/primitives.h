/**
 * @file primitives.h
 * @brief Drawing primitives for the UI Framework
 */

#ifndef UI_FRAMEWORK_PRIMITIVES_H
#define UI_FRAMEWORK_PRIMITIVES_H

#include "canvas.h"
#include "color.h"

/**
 * @brief Draw a pixel on a canvas
 * 
 * @param canvas Canvas to draw on
 * @param x X coordinate
 * @param y Y coordinate
 * @param color Color to draw with
 */
void draw_pixel(Canvas* canvas, int x, int y, Color color);

/**
 * @brief Draw a line on a canvas
 * 
 * @param canvas Canvas to draw on
 * @param x1 X coordinate of start point
 * @param y1 Y coordinate of start point
 * @param x2 X coordinate of end point
 * @param y2 Y coordinate of end point
 * @param color Color to draw with
 */
void draw_line(Canvas* canvas, int x1, int y1, int x2, int y2, Color color);

/**
 * @brief Draw a rectangle on a canvas
 * 
 * @param canvas Canvas to draw on
 * @param x X coordinate of top-left corner
 * @param y Y coordinate of top-left corner
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 * @param color Color to draw with
 */
void draw_rectangle(Canvas* canvas, int x, int y, int width, int height, Color color);

/**
 * @brief Draw a filled rectangle on a canvas
 * 
 * @param canvas Canvas to draw on
 * @param x X coordinate of top-left corner
 * @param y Y coordinate of top-left corner
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 * @param color Color to draw with
 */
void draw_filled_rectangle(Canvas* canvas, int x, int y, int width, int height, Color color);

/**
 * @brief Draw a circle on a canvas
 * 
 * @param canvas Canvas to draw on
 * @param x X coordinate of center
 * @param y Y coordinate of center
 * @param radius Radius of the circle
 * @param color Color to draw with
 */
void draw_circle(Canvas* canvas, int x, int y, int radius, Color color);

/**
 * @brief Draw a filled circle on a canvas
 * 
 * @param canvas Canvas to draw on
 * @param x X coordinate of center
 * @param y Y coordinate of center
 * @param radius Radius of the circle
 * @param color Color to draw with
 */
void draw_filled_circle(Canvas* canvas, int x, int y, int radius, Color color);

/**
 * @brief Draw an ellipse on a canvas
 * 
 * @param canvas Canvas to draw on
 * @param x X coordinate of center
 * @param y Y coordinate of center
 * @param radiusX X radius of the ellipse
 * @param radiusY Y radius of the ellipse
 * @param color Color to draw with
 */
void draw_ellipse(Canvas* canvas, int x, int y, int radiusX, int radiusY, Color color);

/**
 * @brief Draw a filled ellipse on a canvas
 * 
 * @param canvas Canvas to draw on
 * @param x X coordinate of center
 * @param y Y coordinate of center
 * @param radiusX X radius of the ellipse
 * @param radiusY Y radius of the ellipse
 * @param color Color to draw with
 */
void draw_filled_ellipse(Canvas* canvas, int x, int y, int radiusX, int radiusY, Color color);

/**
 * @brief Draw text on a canvas
 * 
 * @param canvas Canvas to draw on
 * @param text Text to draw
 * @param x X coordinate of top-left corner
 * @param y Y coordinate of top-left corner
 * @param size Font size
 * @param color Color to draw with
 */
void draw_text(Canvas* canvas, const char* text, int x, int y, int size, Color color);

#endif /* UI_FRAMEWORK_PRIMITIVES_H */
