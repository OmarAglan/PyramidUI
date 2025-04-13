#include "ui_framework/pal/pal_window.h"

#include <SDL.h> // SDL main header
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Internal structure for the opaque PAL_Window handle
struct PAL_Window {
    SDL_Window* sdl_window;
    SDL_GLContext gl_context; // Added for renderer association
    bool should_close_flag; // Flag set by input polling on SDL_QUIT
    // We might add SDL_GLContext here later if needed for rendering
};

// Helper to manage SDL subsystem initialization count
static int sdl_init_count = 0;

// --- Lifecycle Implementation ---

PAL_Window* pal_window_create(const PAL_WindowConfig* config) {
    if (!config) {
        fprintf(stderr, "PAL Error: Window config is NULL\n");
        return NULL;
    }

    // Initialize SDL video subsystem if this is the first window
    if (sdl_init_count == 0) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            fprintf(stderr, "PAL Error: Failed to initialize SDL video: %s\n", SDL_GetError());
            return NULL;
        }
    }
    sdl_init_count++;

    // Determine window flags
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL; // Added SDL_WINDOW_OPENGL
    if (config->resizable) {
        flags |= SDL_WINDOW_RESIZABLE;
    }
    
    // Set OpenGL context attributes BEFORE creating window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_Window* sdl_win = SDL_CreateWindow(
        config->title ? config->title : "PAL Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config->width > 0 ? config->width : 800,
        config->height > 0 ? config->height : 600,
        flags
    );

    if (!sdl_win) {
        fprintf(stderr, "PAL Error: Failed to create SDL window: %s\n", SDL_GetError());
        // Decrement count if window creation fails after init
        sdl_init_count--;
        if (sdl_init_count == 0) {
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
        }
        return NULL;
    }

    // Allocate our PAL_Window structure
    PAL_Window* pal_win = (PAL_Window*)malloc(sizeof(PAL_Window));
    if (!pal_win) {
        fprintf(stderr, "PAL Error: Failed to allocate PAL_Window structure\n");
        SDL_DestroyWindow(sdl_win);
        sdl_init_count--;
        if (sdl_init_count == 0) {
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
        }
        return NULL;
    }

    // Initialize the structure
    pal_win->sdl_window = sdl_win;
    pal_win->should_close_flag = false; // Input system must set this on SDL_QUIT
    pal_win->gl_context = NULL; // Renderer will create and assign this

    return pal_win;
}

void pal_window_destroy(PAL_Window* window) {
    if (!window) {
        return;
    }

    if (window->sdl_window) {
        SDL_DestroyWindow(window->sdl_window);
    }

    free(window);

    // Decrement SDL init count and quit subsystem if it reaches zero
    sdl_init_count--;
    if (sdl_init_count == 0) {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_Quit(); // Quit SDL entirely when last subsystem is down
    }
}

// --- State & Interaction Implementation ---

bool pal_window_should_close(PAL_Window* window) {
    if (!window) {
        return true; // Treat NULL window as implicitly closed
    }
    // This flag needs to be updated by the input polling system
    // when an SDL_QUIT event is detected.
    return window->should_close_flag;
}

void pal_window_get_size(PAL_Window* window, int* width, int* height) {
    if (!window || !window->sdl_window || !width || !height) {
        if (width) *width = 0;
        if (height) *height = 0;
        return;
    }
    SDL_GetWindowSize(window->sdl_window, width, height);
}

void pal_window_set_title(PAL_Window* window, const char* title) {
    if (!window || !window->sdl_window || !title) {
        return;
    }
    SDL_SetWindowTitle(window->sdl_window, title);
}

void* pal_window_get_native_handle(PAL_Window* window) {
    if (!window) {
        return NULL;
    }
    // For SDL, the native handle *is* the SDL_Window itself for most purposes
    // unless needing OS-specific handles (which requires SDL_GetWindowWMInfo)
    return (void*)window->sdl_window;
} 