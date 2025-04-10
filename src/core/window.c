/**
 * @file window.c
 * @brief Window management implementation
 */

#include "../../include/ui_framework/core/window.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/**
 * @brief Window structure implementation
 */
struct Window {
    char* title;
    int width;
    int height;
    bool resizable;
    bool fullscreen;
    bool should_close;
    
    /* Platform-specific data would go here */
    void* platform_data;
    
    /* Canvas for rendering */
    uint32_t* framebuffer;
};

Window* window_create(const WindowConfig* config) {
    if (!config) {
        return NULL;
    }

    Window* window = (Window*)malloc(sizeof(Window));
    if (!window) {
        return NULL;
    }

    /* Initialize with defaults */
    memset(window, 0, sizeof(Window));
    
    /* Copy configuration */
    window->width = config->width > 0 ? config->width : 800;
    window->height = config->height > 0 ? config->height : 600;
    window->resizable = config->resizable;
    window->fullscreen = config->fullscreen;
    window->should_close = false;
    
    if (config->title) {
        window->title = strdup(config->title);
    } else {
        window->title = strdup("UI Framework Window");
    }
    
    /* Allocate framebuffer */
    window->framebuffer = (uint32_t*)malloc(window->width * window->height * sizeof(uint32_t));
    if (!window->framebuffer) {
        free(window->title);
        free(window);
        return NULL;
    }
    
    /* Clear framebuffer to black */
    memset(window->framebuffer, 0, window->width * window->height * sizeof(uint32_t));
    
    printf("Created window: %s (%dx%d)\n", window->title, window->width, window->height);
    
    return window;
}

void window_destroy(Window* window) {
    if (!window) {
        return;
    }
    
    free(window->title);
    free(window->framebuffer);
    free(window);
}

bool window_should_close(const Window* window) {
    if (!window) {
        return true;
    }
    
    return window->should_close;
}

void window_set_should_close(Window* window, bool should_close) {
    if (!window) {
        return;
    }
    
    window->should_close = should_close;
}

void window_poll_events(Window* window) {
    /* Unused parameter - add (void) to acknowledge it's intentional */
    (void)window;
    
    /* In a real implementation, this would poll for events from the OS */
    /* For now, this is a simple sleep to simulate frame timing */
    #ifdef _WIN32
    Sleep(16);  /* ~60 FPS */
    #else
    usleep(16000);  /* ~60 FPS */
    #endif
}

void window_swap_buffers(Window* window) {
    if (!window) {
        return;
    }
    
    /* In a real implementation, this would swap the front and back buffers */
    /* For now, we'll just print a message */
    printf("Rendered frame\n");
}

int window_get_width(const Window* window) {
    if (!window) {
        return 0;
    }
    
    return window->width;
}

int window_get_height(const Window* window) {
    if (!window) {
        return 0;
    }
    
    return window->height;
}
