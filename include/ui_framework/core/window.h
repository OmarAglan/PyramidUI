/**
 * @file window.h
 * @brief Window management for the UI Framework
 */

#ifndef UI_FRAMEWORK_WINDOW_H
#define UI_FRAMEWORK_WINDOW_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Window configuration structure
 */
typedef struct {
    const char* title;      /**< Window title */
    int width;              /**< Window width */
    int height;             /**< Window height */
    bool resizable;         /**< Whether the window is resizable */
    bool fullscreen;        /**< Whether the window is fullscreen */
} WindowConfig;

/**
 * @brief Window handle
 */
typedef struct Window Window;

/**
 * @brief Create a new window
 * 
 * @param config Window configuration
 * @return Window* Handle to the created window, NULL on failure
 */
Window* window_create(const WindowConfig* config);

/**
 * @brief Destroy a window
 * 
 * @param window Window to destroy
 */
void window_destroy(Window* window);

/**
 * @brief Check if the window should close
 * 
 * @param window Window to check
 * @return true if the window should close, false otherwise
 */
bool window_should_close(const Window* window);

/**
 * @brief Set window should close state
 * 
 * @param window Window to set state for
 * @param should_close Whether the window should close
 */
void window_set_should_close(Window* window, bool should_close);

/**
 * @brief Poll window events
 * 
 * @param window Window to poll events for
 */
void window_poll_events(Window* window);

/**
 * @brief Swap window buffers (update display)
 * 
 * @param window Window to swap buffers for
 */
void window_swap_buffers(Window* window);

/**
 * @brief Get window width
 * 
 * @param window Window to get width of
 * @return int Window width
 */
int window_get_width(const Window* window);

/**
 * @brief Get window height
 * 
 * @param window Window to get height of
 * @return int Window height
 */
int window_get_height(const Window* window);

#endif /* UI_FRAMEWORK_WINDOW_H */
