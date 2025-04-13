#ifndef PAL_INPUT_H
#define PAL_INPUT_H

#include <stdbool.h>
#include "pal_window.h" // Include window for context if needed

// --- Enums for Input --- //

// Represent common keyboard keys. Values should ideally map to a backend-agnostic scheme,
// or be large enough to hold backend-specific codes if necessary.
// (Using SDL ScanCode values might be practical for the first implementation)
typedef enum {
    PAL_KEY_UNKNOWN = 0,
    // Example keys (add more as needed)
    PAL_KEY_A = 4,
    PAL_KEY_B = 5,
    PAL_KEY_C = 6,
    // ... map relevant keys ...
    PAL_KEY_RETURN = 40,
    PAL_KEY_ESCAPE = 41,
    PAL_KEY_BACKSPACE = 42,
    PAL_KEY_LEFT = 80,
    PAL_KEY_RIGHT = 79,
    PAL_KEY_UP = 82,
    PAL_KEY_DOWN = 81,
    // ... map more ...
    PAL_KEY_MAX // Placeholder for array sizing
} PAL_KeyCode;

// Mouse buttons
typedef enum {
    PAL_MOUSE_BUTTON_LEFT = 1,
    PAL_MOUSE_BUTTON_MIDDLE = 2,
    PAL_MOUSE_BUTTON_RIGHT = 3,
    PAL_MOUSE_BUTTON_MAX // Placeholder
} PAL_MouseButton;

// --- Event Polling --- //

/**
 * @brief Processes all pending platform events since the last call.
 *        This should be called once per frame, typically at the beginning.
 *        It updates the internal input state queried by other functions
 *        and importantly, signals the window if a quit event occurs.
 * @param window The window context (needed to signal should_close).
 */
void pal_input_poll_events(PAL_Window* window);

// --- Input State Queries --- //

// Mouse
void pal_input_get_mouse_pos(int* x, int* y);
bool pal_input_is_mouse_button_down(PAL_MouseButton button);
bool pal_input_is_mouse_button_pressed(PAL_MouseButton button); // Pressed this frame
bool pal_input_is_mouse_button_released(PAL_MouseButton button); // Released this frame
void pal_input_get_mouse_wheel(float* x_offset, float* y_offset); // Get scroll offset this frame

// Keyboard
bool pal_input_is_key_down(PAL_KeyCode key);
bool pal_input_is_key_pressed(PAL_KeyCode key);   // Pressed this frame
bool pal_input_is_key_released(PAL_KeyCode key); // Released this frame

/**
 * @brief Gets text input entered this frame.
 *        Useful for text fields.
 * @return A null-terminated UTF-8 string of characters entered, or NULL/empty if none.
 *         The lifetime of the returned pointer is typically until the next call to pal_input_poll_events.
 */
const char* pal_input_get_text_input(void);


#endif // PAL_INPUT_H 