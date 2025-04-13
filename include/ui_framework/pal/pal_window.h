#ifndef PAL_WINDOW_H
#define PAL_WINDOW_H

#include <stdbool.h>

// --- Configuration ---

typedef struct {
    const char* title;
    int width;
    int height;
    bool resizable;
    // Add other options as needed (e.g., fullscreen, vsync)
} PAL_WindowConfig;

// --- Opaque Window Handle ---

// Users of the PAL only interact with this opaque pointer.
// The actual implementation (e.g., SDL_Window*) is hidden.
typedef struct PAL_Window PAL_Window;

// --- Lifecycle ---

/**
 * @brief Creates a new platform window.
 * @param config Window configuration settings.
 * @return An opaque handle to the window, or NULL on failure.
 */
PAL_Window* pal_window_create(const PAL_WindowConfig* config);

/**
 * @brief Destroys a platform window and releases associated resources.
 * @param window The window handle to destroy.
 */
void pal_window_destroy(PAL_Window* window);

// --- State & Interaction ---

/**
 * @brief Checks if the user has requested to close the window.
 * @param window The window handle.
 * @return True if a close request has been detected, false otherwise.
 */
bool pal_window_should_close(PAL_Window* window);

/**
 * @brief Gets the current drawable size of the window's client area.
 *        This might differ from the initial config size if resized.
 * @param window The window handle.
 * @param width Pointer to store the width.
 * @param height Pointer to store the height.
 */
void pal_window_get_size(PAL_Window* window, int* width, int* height);

/**
 * @brief Sets the title of the window.
 * @param window The window handle.
 * @param title The new title string.
 */
void pal_window_set_title(PAL_Window* window, const char* title);

/**
 * @brief Gets the underlying native window handle (e.g., HWND, NSWindow*, SDL_Window*).
 *        Use with caution - primarily for renderer initialization if needed.
 * @param window The window handle.
 * @return A pointer to the native handle, or NULL. Type depends on backend.
 */
void* pal_window_get_native_handle(PAL_Window* window); // Optional but often useful

#endif // PAL_WINDOW_H 