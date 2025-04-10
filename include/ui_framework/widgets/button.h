/**
 * @file button.h
 * @brief Button widget for the UI Framework
 */

#ifndef UI_FRAMEWORK_BUTTON_H
#define UI_FRAMEWORK_BUTTON_H

#include "widget.h"

/**
 * @brief Button click callback
 * 
 * @param button Button that was clicked
 * @param user_data User data associated with the callback
 */
typedef void (*ButtonClickCallback)(Widget* button, void* user_data);

/**
 * @brief Create a new button
 * 
 * @param x X position
 * @param y Y position
 * @param width Width
 * @param height Height
 * @param text Button text
 * @return Widget* Handle to the created button, NULL on failure
 */
Widget* button_create(int x, int y, int width, int height, const char* text);

/**
 * @brief Set the text of a button
 * 
 * @param button Button to set text for
 * @param text Text to set
 */
void button_set_text(Widget* button, const char* text);

/**
 * @brief Get the text of a button
 * 
 * @param button Button to get text from
 * @return const char* Button text
 */
const char* button_get_text(const Widget* button);

/**
 * @brief Set the click callback for a button
 * 
 * @param button Button to set callback for
 * @param callback Callback function
 * @param user_data User data to pass to the callback
 */
void button_set_click_callback(Widget* button, ButtonClickCallback callback, void* user_data);

/**
 * @brief Set the background color of a button
 * 
 * @param button Button to set color for
 * @param color Color to set
 */
void button_set_background_color(Widget* button, Color color);

/**
 * @brief Set the text color of a button
 * 
 * @param button Button to set color for
 * @param color Color to set
 */
void button_set_text_color(Widget* button, Color color);

#endif /* UI_FRAMEWORK_BUTTON_H */
