/**
 * @file primitives.c
 * @brief Drawing primitives implementation for the UI Framework
 */

#include "../../include/ui_framework/drawing/primitives.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

void draw_pixel(Canvas* canvas, int x, int y, Color color) {
    canvas_set_pixel(canvas, x, y, color);
}

void draw_line(Canvas* canvas, int x1, int y1, int x2, int y2, Color color) {
    // Bresenham's line algorithm
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    
    while (1) {
        canvas_set_pixel(canvas, x1, y1, color);
        
        if (x1 == x2 && y1 == y2) {
            break;
        }
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_rectangle(Canvas* canvas, int x, int y, int width, int height, Color color) {
    // Draw horizontal lines
    for (int i = x; i < x + width; i++) {
        canvas_set_pixel(canvas, i, y, color);
        canvas_set_pixel(canvas, i, y + height - 1, color);
    }
    
    // Draw vertical lines
    for (int i = y; i < y + height; i++) {
        canvas_set_pixel(canvas, x, i, color);
        canvas_set_pixel(canvas, x + width - 1, i, color);
    }
}

void draw_filled_rectangle(Canvas* canvas, int x, int y, int width, int height, Color color) {
    for (int j = y; j < y + height; j++) {
        for (int i = x; i < x + width; i++) {
            canvas_set_pixel(canvas, i, j, color);
        }
    }
}

void draw_circle(Canvas* canvas, int x, int y, int radius, Color color) {
    // Midpoint circle algorithm
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x_pos = 0;
    int y_pos = radius;
    
    canvas_set_pixel(canvas, x, y + radius, color);
    canvas_set_pixel(canvas, x, y - radius, color);
    canvas_set_pixel(canvas, x + radius, y, color);
    canvas_set_pixel(canvas, x - radius, y, color);
    
    while (x_pos < y_pos) {
        if (f >= 0) {
            y_pos--;
            ddF_y += 2;
            f += ddF_y;
        }
        x_pos++;
        ddF_x += 2;
        f += ddF_x + 1;
        
        canvas_set_pixel(canvas, x + x_pos, y + y_pos, color);
        canvas_set_pixel(canvas, x - x_pos, y + y_pos, color);
        canvas_set_pixel(canvas, x + x_pos, y - y_pos, color);
        canvas_set_pixel(canvas, x - x_pos, y - y_pos, color);
        canvas_set_pixel(canvas, x + y_pos, y + x_pos, color);
        canvas_set_pixel(canvas, x - y_pos, y + x_pos, color);
        canvas_set_pixel(canvas, x + y_pos, y - x_pos, color);
        canvas_set_pixel(canvas, x - y_pos, y - x_pos, color);
    }
}

void draw_filled_circle(Canvas* canvas, int x, int y, int radius, Color color) {
    for (int j = -radius; j <= radius; j++) {
        for (int i = -radius; i <= radius; i++) {
            if (i*i + j*j <= radius*radius) {
                canvas_set_pixel(canvas, x + i, y + j, color);
            }
        }
    }
}

void draw_ellipse(Canvas* canvas, int x, int y, int radiusX, int radiusY, Color color) {
    // Simple approximation with points at regular angle intervals
    const int num_segments = 36;
    float theta = 0;
    float step = 2.0f * 3.14159f / num_segments;
    
    for (int i = 0; i < num_segments; i++) {
        int x1 = x + radiusX * cos(theta);
        int y1 = y + radiusY * sin(theta);
        theta += step;
        int x2 = x + radiusX * cos(theta);
        int y2 = y + radiusY * sin(theta);
        
        draw_line(canvas, x1, y1, x2, y2, color);
    }
}

void draw_filled_ellipse(Canvas* canvas, int x, int y, int radiusX, int radiusY, Color color) {
    for (int j = -radiusY; j <= radiusY; j++) {
        for (int i = -radiusX; i <= radiusX; i++) {
            if ((i*i * radiusY*radiusY + j*j * radiusX*radiusX) <= radiusX*radiusX * radiusY*radiusY) {
                canvas_set_pixel(canvas, x + i, y + j, color);
            }
        }
    }
}

void draw_text(Canvas* canvas, const char* text, int x, int y, int size, Color color) {
    if (!canvas || !text) {
        return;
    }
    
    // Simple text rendering (just a placeholder)
    int len = strlen(text);
    int char_width = size / 2;
    
    for (int i = 0; i < len; i++) {
        // Draw a simple rectangle for each character
        int char_x = x + i * char_width;
        draw_rectangle(canvas, char_x, y, char_width - 1, size, color);
        
        // This is just a placeholder. In a real implementation,
        // you would render actual fonts with glyphs
        printf("Rendering character '%c' at (%d, %d)\n", text[i], char_x, y);
    }
}
