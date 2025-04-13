#include "ui_framework/pal/pal_input.h"
#include "ui_framework/pal/pal_window.h" // Need access to PAL_Window internals

#include <SDL.h>
#include <string.h>
#include <stdlib.h> // For malloc/free if needed for text input buffer

// Define PAL_Window struct again to access its internals (friend struct workaround)
// This is slightly hacky; a better way involves passing internal state explicitly
// or having dedicated pal_window_set_should_close function.
struct PAL_Window {
    SDL_Window* sdl_window;
    bool should_close_flag;
};

// --- Internal State --- //

static int mouse_x = 0;
static int mouse_y = 0;
static float mouse_wheel_x = 0.0f;
static float mouse_wheel_y = 0.0f;

static Uint32 mouse_state_current = 0;
static Uint32 mouse_state_prev = 0;

static const Uint8* keyboard_state_current = NULL;
static Uint8* keyboard_state_prev = NULL;
static int num_keys = 0; // Will be set on first poll

#define MAX_TEXT_INPUT_LEN 32
static char text_input_buffer[MAX_TEXT_INPUT_LEN] = {0};

// --- Helper Functions --- //

// Remove unused helper function
// static PAL_MouseButton sdl_button_to_pal(Uint8 sdl_button) {
//     ...
// }

static Uint32 pal_button_to_sdl_mask(PAL_MouseButton pal_button) {
    switch (pal_button) {
        case PAL_MOUSE_BUTTON_LEFT:   return SDL_BUTTON(SDL_BUTTON_LEFT);
        case PAL_MOUSE_BUTTON_MIDDLE: return SDL_BUTTON(SDL_BUTTON_MIDDLE);
        case PAL_MOUSE_BUTTON_RIGHT:  return SDL_BUTTON(SDL_BUTTON_RIGHT);
        default:                      return 0;
    }
}

// --- Event Polling --- //

void pal_input_poll_events(PAL_Window* window) {
    if (!window) return;

    // Update previous states
    mouse_state_prev = mouse_state_current;
    mouse_wheel_x = 0.0f;
    mouse_wheel_y = 0.0f;
    text_input_buffer[0] = '\0'; // Clear text input buffer

    if (keyboard_state_current) {
        if (!keyboard_state_prev) {
            // Allocate buffer for previous state on first run
            keyboard_state_prev = (Uint8*)malloc(num_keys * sizeof(Uint8));
        }
        if (keyboard_state_prev) {
            memcpy(keyboard_state_prev, keyboard_state_current, num_keys * sizeof(Uint8));
        }
    }

    // Update current keyboard state pointer (SDL manages this memory)
    keyboard_state_current = SDL_GetKeyboardState(&num_keys);

    // Update current mouse state
    mouse_state_current = SDL_GetMouseState(&mouse_x, &mouse_y);

    // Process SDL event queue
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                window->should_close_flag = true;
                break;
            case SDL_MOUSEWHEEL:
                mouse_wheel_x = event.wheel.x;
                mouse_wheel_y = event.wheel.y;
                // SDL uses positive for scroll away from user (up/right)
                // Many UIs expect positive for scroll towards user (down/right)
                // Adjust if necessary based on UI framework convention:
                // mouse_wheel_y *= -1.0f; 
                break;
            case SDL_TEXTINPUT:
                // Append text input to buffer (simple concatenation)
                strncat(text_input_buffer, event.text.text, MAX_TEXT_INPUT_LEN - strlen(text_input_buffer) - 1);
                break;
            // Handle other events like window resize, keyboard/mouse button presses/releases
            // These are implicitly handled by querying SDL_Get*State functions below,
            // but specific event handling could be added here if needed.
        }
    }
}

// --- Input State Queries --- //

void pal_input_get_mouse_pos(int* x, int* y) {
    if (x) *x = mouse_x;
    if (y) *y = mouse_y;
}

bool pal_input_is_mouse_button_down(PAL_MouseButton button) {
    Uint32 mask = pal_button_to_sdl_mask(button);
    return (mouse_state_current & mask) != 0;
}

bool pal_input_is_mouse_button_pressed(PAL_MouseButton button) {
    Uint32 mask = pal_button_to_sdl_mask(button);
    return ((mouse_state_current & mask) != 0) && ((mouse_state_prev & mask) == 0);
}

bool pal_input_is_mouse_button_released(PAL_MouseButton button) {
    Uint32 mask = pal_button_to_sdl_mask(button);
    return ((mouse_state_current & mask) == 0) && ((mouse_state_prev & mask) != 0);
}

void pal_input_get_mouse_wheel(float* x_offset, float* y_offset) {
    if (x_offset) *x_offset = mouse_wheel_x;
    if (y_offset) *y_offset = mouse_wheel_y;
}

bool pal_input_is_key_down(PAL_KeyCode key) {
    if (!keyboard_state_current || key <= PAL_KEY_UNKNOWN || key >= PAL_KEY_MAX || key >= num_keys) {
        return false;
    }
    // Assuming PAL_KeyCode maps directly to SDL_SCANCODE_*
    return keyboard_state_current[key] != 0;
}

bool pal_input_is_key_pressed(PAL_KeyCode key) {
    if (!keyboard_state_current || !keyboard_state_prev || key <= PAL_KEY_UNKNOWN || key >= PAL_KEY_MAX || key >= num_keys) {
        return false;
    }
    return (keyboard_state_current[key] != 0) && (keyboard_state_prev[key] == 0);
}

bool pal_input_is_key_released(PAL_KeyCode key) {
    if (!keyboard_state_current || !keyboard_state_prev || key <= PAL_KEY_UNKNOWN || key >= PAL_KEY_MAX || key >= num_keys) {
        return false;
    }
    return (keyboard_state_current[key] == 0) && (keyboard_state_prev[key] != 0);
}

const char* pal_input_get_text_input(void) {
    return text_input_buffer;
}

// TODO: Add function to cleanup keyboard_state_prev buffer on shutdown?
// Currently leaks if poll_events is called at least once. 