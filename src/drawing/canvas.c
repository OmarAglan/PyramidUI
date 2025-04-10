/**
 * @file canvas.c
 * @brief Canvas drawing implementation
 */

#include "../../include/ui_framework/drawing/canvas.h"
#include "../../include/ui_framework/core/window.h" /* Include window.h explicitly */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Canvas structure implementation
 */
struct Canvas {
    int width;
    int height;
    uint32_t* pixels;
};

Canvas* canvas_create(int width, int height) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }

    Canvas* canvas = (Canvas*)malloc(sizeof(Canvas));
    if (!canvas) {
        return NULL;
    }

    canvas->width = width;
    canvas->height = height;
    canvas->pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    
    if (!canvas->pixels) {
        free(canvas);
        return NULL;
    }

    // Initialize to transparent
    memset(canvas->pixels, 0, width * height * sizeof(uint32_t));
    
    return canvas;
}

void canvas_destroy(Canvas* canvas) {
    if (!canvas) {
        return;
    }
    
    free(canvas->pixels);
    free(canvas);
}

void canvas_clear(Canvas* canvas, Color color) {
    if (!canvas) {
        return;
    }
    
    uint32_t color_value = color_to_uint32(color);
    
    for (int i = 0; i < canvas->width * canvas->height; i++) {
        canvas->pixels[i] = color_value;
    }
}

void canvas_set_pixel(Canvas* canvas, int x, int y, Color color) {
    if (!canvas || x < 0 || x >= canvas->width || y < 0 || y >= canvas->height) {
        return;
    }
    
    canvas->pixels[y * canvas->width + x] = color_to_uint32(color);
}

Color canvas_get_pixel(const Canvas* canvas, int x, int y) {
    if (!canvas || x < 0 || x >= canvas->width || y < 0 || y >= canvas->height) {
        return COLOR_TRANSPARENT;
    }
    
    return color_from_uint32(canvas->pixels[y * canvas->width + x]);
}

int canvas_get_width(const Canvas* canvas) {
    if (!canvas) {
        return 0;
    }
    
    return canvas->width;
}

int canvas_get_height(const Canvas* canvas) {
    if (!canvas) {
        return 0;
    }
    
    return canvas->height;
}

const uint32_t* canvas_get_data(const Canvas* canvas) {
    if (!canvas) {
        return NULL;
    }
    
    return canvas->pixels;
}

void canvas_render(const Canvas* canvas, struct Window* window) {
    if (!canvas || !window) {
        return;
    }
    
    printf("Rendering canvas (%dx%d) to window\n", canvas->width, canvas->height);
    
    // In a real implementation, this would copy the canvas pixels to the window's framebuffer
    // For now, this is just a placeholder
}
