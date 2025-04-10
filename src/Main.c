/**
 * @file Main.c
 * @brief Example application using the UI Framework
 */

#include "../include/ui_framework/ui_framework.h"
#include <stdio.h>
#include <stdlib.h>

/* Button click callback */
void on_button_click(Widget* button, void* user_data) {
    /* Unused parameter - add (void) to acknowledge it's intentional */
    (void)user_data;
    
    printf("Button clicked: %s\n", button_get_text(button));
}

int main(void) {
    /* Create a window */
    WindowConfig config = {
        .title = "UI Framework Demo",
        .width = 800,
        .height = 600,
        .resizable = true,
        .fullscreen = false
    };
    
    Window* window = window_create(&config);
    if (!window) {
        fprintf(stderr, "Failed to create window\n");
        return 1;
    }
    
    /* Create a canvas for drawing */
    Canvas* canvas = canvas_create(window_get_width(window), window_get_height(window));
    if (!canvas) {
        fprintf(stderr, "Failed to create canvas\n");
        window_destroy(window);
        return 1;
    }
    
    /* Create a button */
    Widget* button = button_create(350, 250, 100, 50, "Click Me");
    if (!button) {
        fprintf(stderr, "Failed to create button\n");
        canvas_destroy(canvas);
        window_destroy(window);
        return 1;
    }
    
    /* Set button colors and callback */
    button_set_background_color(button, COLOR_BLUE);
    button_set_text_color(button, COLOR_WHITE);
    button_set_click_callback(button, on_button_click, NULL);
    
    /* Main loop */
    while (!window_should_close(window)) {
        /* Clear canvas with a dark gray color */
        canvas_clear(canvas, color_rgb(50, 50, 50));
        
        /* Draw widgets */
        widget_draw(button, canvas);
        
        /* Render canvas to window */
        canvas_render(canvas, window);
        
        /* Swap buffers and poll events */
        window_swap_buffers(window);
        window_poll_events(window);
    }
    
    /* Cleanup */
    widget_destroy(button);
    canvas_destroy(canvas);
    window_destroy(window);
    
    return 0;
}

