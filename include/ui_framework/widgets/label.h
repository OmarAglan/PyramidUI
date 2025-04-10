/**
 * @file label.h
 * @brief Label widget for the UI Framework
 */

#ifndef UI_FRAMEWORK_LABEL_H
#define UI_FRAMEWORK_LABEL_H

#include "widget.h"

/**
 * @brief Create a new label
 * 
 * @param x X position
 * @param y Y position
 * @param width Width
 * @param height Height
 * @param text Label text
 * @return Widget* Handle to the created label, NULL on failure
 */
Widget* label_create(int x, int y, int width, int height, const char* text);

/**
 * @brief Set the text of a label
 * 
 * @param label Label to set text for
 * @param text Text to set
 */
void label_set_text(Widget* label, const char* text);

/**
 * @brief Get the text of a label
 * 
 * @param label Label to get text from
 * @return const char* Label text
 */
const char* label_get_text(const Widget* label);

/**
 * @brief Set the text color of a label
 * 
 * @param label Label to set color for
 * @param color Color to set
 */
void label_set_text_color(Widget* label, Color color);

/**
 * @brief Set the background color of a label
 * 
 * @param label Label to set color for
 * @param color Color to set
 */
void label_set_background_color(Widget* label, Color color);

/**
 * @brief Set the text alignment of a label
 * 
 * @param label Label to set alignment for
 * @param alignment Alignment to set (0 = left, 1 = center, 2 = right)
 */
void label_set_alignment(Widget* label, int alignment);

#endif /* UI_FRAMEWORK_LABEL_H */
