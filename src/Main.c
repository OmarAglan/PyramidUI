/**
 * @file Main.c
 * @brief Example application using the UI Framework
 */

#include "../include/ui_framework/ui_framework.h"
#include "../include/ui_framework/pal/pal_window.h"
#include "../include/ui_framework/pal/pal_input.h"
#include "../include/ui_framework/pal/pal_renderer.h"
#include <stdio.h>
#include <stdlib.h>

/* Button click callback */
void on_button_click(Widget* button, void* user_data) {
    /* Unused parameter - add (void) to acknowledge it's intentional */
    (void)user_data;
    
    printf("Button clicked: %s\n", button_get_text(button));
}

int main(int argc, char *argv[]) {
    /* Mark arguments as unused (for now) */
    (void)argc;
    (void)argv;

    /* Create a window using PAL */
    PAL_WindowConfig config = {
        .title = "UI Framework Demo (PAL/SDL)",
        .width = 800,
        .height = 600,
        .resizable = true
    };
    
    PAL_Window* window = pal_window_create(&config);
    if (!window) {
        fprintf(stderr, "Failed to create PAL window\n");
        return 1;
    }
    
    /* Get window size from PAL */
    int window_width, window_height;
    pal_window_get_size(window, &window_width, &window_height);

    /* Create a PAL Renderer */
    PAL_Renderer* renderer = pal_renderer_create(window);
    if (!renderer) {
        fprintf(stderr, "Failed to create PAL renderer\n");
        pal_window_destroy(window);
        return 1;
    }

    /* Create a button - Drawing needs update for PAL */
    Widget* button = button_create(350, 250, 100, 50, "Click Me");
    if (!button) {
        fprintf(stderr, "Failed to create button\n");
        pal_renderer_destroy(renderer);
        pal_window_destroy(window);
        return 1;
    }
    
    /* Set button colors and callback */
    button_set_background_color(button, COLOR_BLUE);
    button_set_text_color(button, COLOR_WHITE);
    button_set_click_callback(button, on_button_click, NULL);
    
    /* Main loop */
    while (!pal_window_should_close(window)) {
        /* Process Input (Using PAL Input) */
        pal_input_poll_events(window); 

        // --- Example: Check for Escape key to close window --- //
        if (pal_input_is_key_pressed(PAL_KEY_ESCAPE)) {
            // We need a way to tell the window to close from here.
            // Let's assume a function pal_window_set_should_close exists (needs adding to PAL API)
            // pal_window_set_should_close(window, true); 
            // For now, we'll just break the loop directly as a placeholder
            printf("Escape pressed - closing (placeholder action)\n");
            break; 
        }

        // --- Example: Check for mouse click --- //
        if (pal_input_is_mouse_button_pressed(PAL_MOUSE_BUTTON_LEFT)) {
            int mouse_x, mouse_y;
            pal_input_get_mouse_pos(&mouse_x, &mouse_y);
            printf("Mouse Left Button Pressed at: (%d, %d)\n", mouse_x, mouse_y);
            // TODO: Check if click is inside button and trigger callback
            // This requires widget_handle_event logic integrated with PAL input
        }

        /* Begin Renderer Frame */
        pal_renderer_begin_frame(renderer, color_rgb(50, 50, 50));

        /* Clear canvas with a dark gray color - Handled by begin_frame */
        // canvas_clear(canvas, color_rgb(50, 50, 50));
        
        /* Draw widgets - NEEDS REFACTORING */
        // widget_draw(button, canvas); // Old drawing function
        // TODO: Need a new drawing approach using pal_renderer functions
        // e.g., button->draw(button, renderer); which calls pal_renderer_render_textured_quad etc.
        // For now, draw a placeholder quad:
        pal_renderer_render_textured_quad(renderer, NULL, 350, 250, 100, 50, 0, 0, 1, 1, COLOR_BLUE);

        /* Render canvas to window - Handled by end_frame */
        // ...
        
        /* End Renderer Frame (swaps buffers) */
        pal_renderer_end_frame(renderer);
        
        /* Temporary replacement - NO LONGER NEEDED */
        // SDL_Delay(16); 
    }
    
    /* Cleanup */
    widget_destroy(button);
    // canvas_destroy(canvas); // Obsolete
    pal_renderer_destroy(renderer);
    pal_window_destroy(window);
    
    return 0;
}

