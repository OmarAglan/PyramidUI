/**
 * @file input.h
 * @brief Input handling for the UI Framework
 */

#ifndef UI_FRAMEWORK_INPUT_H
#define UI_FRAMEWORK_INPUT_H

#include <stdbool.h>

/**
 * @brief Key codes for keyboard input
 */
typedef enum {
    KEY_UNKNOWN = -1,
    KEY_SPACE = 32,
    KEY_APOSTROPHE = 39,
    KEY_COMMA = 44,
    KEY_MINUS = 45,
    KEY_PERIOD = 46,
    KEY_SLASH = 47,
    KEY_0 = 48,
    KEY_1 = 49,
    KEY_2 = 50,
    KEY_3 = 51,
    KEY_4 = 52,
    KEY_5 = 53,
    KEY_6 = 54,
    KEY_7 = 55,
    KEY_8 = 56,
    KEY_9 = 57,
    KEY_SEMICOLON = 59,
    KEY_EQUAL = 61,
    KEY_A = 65,
    KEY_B = 66,
    KEY_C = 67,
    KEY_D = 68,
    KEY_E = 69,
    KEY_F = 70,
    KEY_G = 71,
    KEY_H = 72,
    KEY_I = 73,
    KEY_J = 74,
    KEY_K = 75,
    KEY_L = 76,
    KEY_M = 77,
    KEY_N = 78,
    KEY_O = 79,
    KEY_P = 80,
    KEY_Q = 81,
    KEY_R = 82,
    KEY_S = 83,
    KEY_T = 84,
    KEY_U = 85,
    KEY_V = 86,
    KEY_W = 87,
    KEY_X = 88,
    KEY_Y = 89,
    KEY_Z = 90,
    KEY_ESCAPE = 256,
    KEY_ENTER = 257,
    KEY_TAB = 258,
    KEY_BACKSPACE = 259,
    KEY_DELETE = 261,
    KEY_RIGHT = 262,
    KEY_LEFT = 263,
    KEY_DOWN = 264,
    KEY_UP = 265,
    KEY_F1 = 290,
    KEY_F2 = 291,
    KEY_F3 = 292,
    KEY_F4 = 293,
    KEY_F5 = 294,
    KEY_F6 = 295,
    KEY_F7 = 296,
    KEY_F8 = 297,
    KEY_F9 = 298,
    KEY_F10 = 299,
    KEY_F11 = 300,
    KEY_F12 = 301,
    KEY_LAST
} KeyCode;

/**
 * @brief Modifier key flags
 */
typedef enum {
    MOD_SHIFT = 0x01,
    MOD_CONTROL = 0x02,
    MOD_ALT = 0x04,
    MOD_SUPER = 0x08
} KeyMod;

/**
 * @brief Check if a key is currently pressed
 * 
 * @param window Window to check input for
 * @param key Key to check
 * @return true if the key is pressed, false otherwise
 */
bool input_key_pressed(struct Window* window, KeyCode key);

/**
 * @brief Check if a key was pressed this frame
 * 
 * @param window Window to check input for
 * @param key Key to check
 * @return true if the key was just pressed, false otherwise
 */
bool input_key_just_pressed(struct Window* window, KeyCode key);

/**
 * @brief Check if a key was released this frame
 * 
 * @param window Window to check input for
 * @param key Key to check
 * @return true if the key was just released, false otherwise
 */
bool input_key_just_released(struct Window* window, KeyCode key);

/**
 * @brief Get mouse position
 * 
 * @param window Window to get mouse position for
 * @param x Pointer to store X coordinate (can be NULL)
 * @param y Pointer to store Y coordinate (can be NULL)
 */
void input_get_mouse_position(struct Window* window, int* x, int* y);

/**
 * @brief Check if a mouse button is pressed
 * 
 * @param window Window to check input for
 * @param button Button to check
 * @return true if the button is pressed, false otherwise
 */
bool input_mouse_button_pressed(struct Window* window, int button);

/**
 * @brief Check if a mouse button was just pressed
 * 
 * @param window Window to check input for
 * @param button Button to check
 * @return true if the button was just pressed, false otherwise
 */
bool input_mouse_button_just_pressed(struct Window* window, int button);

/**
 * @brief Check if a mouse button was just released
 * 
 * @param window Window to check input for
 * @param button Button to check
 * @return true if the button was just released, false otherwise
 */
bool input_mouse_button_just_released(struct Window* window, int button);

#endif /* UI_FRAMEWORK_INPUT_H */
