/**
 * @file button.c
 * @brief Button widget implementation for the UI Framework
 */

#include "../../include/ui_framework/widgets/button.h"
#include "../../include/ui_framework/drawing/primitives.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Platform-specific string duplication
#ifdef _WIN32
#define PLATFORM_STRDUP _strdup
#else
#define PLATFORM_STRDUP strdup
#endif

/**
 * @brief Button data structure
 */
typedef struct {
    char* text;
    Color background_color;
    Color text_color;
    ButtonClickCallback click_callback;
    void* callback_user_data;
    bool pressed;
} ButtonData;

/**
 * @brief Button draw function
 */
static void button_draw_function(Widget* button, Canvas* canvas) {
    if (!button || !canvas) {
        return;
    }

    ButtonData* data = (ButtonData*)widget_get_user_data(button);
    if (!data) {
        return;
    }

    // Get button dimensions
    int x = widget_get_x(button);
    int y = widget_get_y(button);
    int width = widget_get_width(button);
    int height = widget_get_height(button);
    
    // Draw button background
    draw_filled_rectangle(canvas, x, y, width, height, data->background_color);
    
    // Draw button border
    draw_rectangle(canvas, x, y, width, height, COLOR_BLACK);
    
    // Draw button text
    if (data->text) {
        // Simple centering of text (approximate)
        int text_x = x + width / 2 - strlen(data->text) * 4; // Approximate width of a character
        int text_y = y + height / 2 - 6; // Approximate height of text
        draw_text(canvas, data->text, text_x, text_y, 12, data->text_color);
    }
}

/**
 * @brief Button event handler
 */
static bool button_event_handler(Widget* button, const Event* event) {
    if (!button || !event) {
        return false;
    }
    
    ButtonData* data = (ButtonData*)widget_get_user_data(button);
    if (!data) {
        return false;
    }
    
    // Handle mouse events
    if (event->type == EVENT_MOUSE_BUTTON_PRESS) {
        if (widget_contains_point(button, event->mouse_button.x, event->mouse_button.y)) {
            data->pressed = true;
            return true;
        }
    } else if (event->type == EVENT_MOUSE_BUTTON_RELEASE) {
        if (data->pressed && widget_contains_point(button, event->mouse_button.x, event->mouse_button.y)) {
            data->pressed = false;
            
            // Call the click callback if set
            if (data->click_callback) {
                data->click_callback(button, data->callback_user_data);
            }
            
            return true;
        }
        data->pressed = false;
    }
    
    return false;
}

Widget* button_create(int x, int y, int width, int height, const char* text) {
    // Allocate button data
    ButtonData* data = (ButtonData*)malloc(sizeof(ButtonData));
    if (!data) {
        return NULL;
    }
    
    // Initialize button data
    memset(data, 0, sizeof(ButtonData));
    data->background_color = COLOR_WHITE;
    data->text_color = COLOR_BLACK;
    data->pressed = false;
    
    // Copy button text
    if (text) {
        data->text = PLATFORM_STRDUP(text);
        if (!data->text) {
            free(data);
            return NULL;
        }
    }
    
    // Create the button widget
    Widget* button = widget_create(x, y, width, height, data, button_draw_function, button_event_handler);
    if (!button) {
        free(data->text);
        free(data);
        return NULL;
    }
    
    return button;
}

void button_set_text(Widget* button, const char* text) {
    if (!button || !text) {
        return;
    }
    
    ButtonData* data = (ButtonData*)widget_get_user_data(button);
    if (!data) {
        return;
    }
    
    // Free old text
    if (data->text) {
        free(data->text);
    }
    
    // Copy new text
    data->text = PLATFORM_STRDUP(text);
}

const char* button_get_text(const Widget* button) {
    if (!button) {
        return NULL;
    }
    
    ButtonData* data = (ButtonData*)widget_get_user_data(button);
    if (!data) {
        return NULL;
    }
    
    return data->text;
}

void button_set_click_callback(Widget* button, ButtonClickCallback callback, void* user_data) {
    if (!button) {
        return;
    }
    
    ButtonData* data = (ButtonData*)widget_get_user_data(button);
    if (!data) {
        return;
    }
    
    data->click_callback = callback;
    data->callback_user_data = user_data;
}

void button_set_background_color(Widget* button, Color color) {
    if (!button) {
        return;
    }
    
    ButtonData* data = (ButtonData*)widget_get_user_data(button);
    if (!data) {
        return;
    }
    
    data->background_color = color;
}

void button_set_text_color(Widget* button, Color color) {
    if (!button) {
        return;
    }
    
    ButtonData* data = (ButtonData*)widget_get_user_data(button);
    if (!data) {
        return;
    }
    
    data->text_color = color;
}
