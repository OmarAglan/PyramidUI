/**
 * @file container.h
 * @brief Container widget for the UI Framework
 */

#ifndef UI_FRAMEWORK_CONTAINER_H
#define UI_FRAMEWORK_CONTAINER_H

#include "widget.h"

/**
 * @brief Create a new container
 * 
 * @param x X position
 * @param y Y position
 * @param width Width
 * @param height Height
 * @return Widget* Handle to the created container, NULL on failure
 */
Widget* container_create(int x, int y, int width, int height);

/**
 * @brief Add a child widget to a container
 * 
 * @param container Container to add child to
 * @param child Child widget to add
 * @return int 0 on success, -1 on failure
 */
int container_add_child(Widget* container, Widget* child);

/**
 * @brief Remove a child widget from a container
 * 
 * @param container Container to remove child from
 * @param child Child widget to remove
 * @return int 0 on success, -1 on failure
 */
int container_remove_child(Widget* container, Widget* child);

/**
 * @brief Get the number of children in a container
 * 
 * @param container Container to get child count for
 * @return int Number of children
 */
int container_get_child_count(const Widget* container);

/**
 * @brief Get a child widget from a container by index
 * 
 * @param container Container to get child from
 * @param index Index of the child to get
 * @return Widget* Child widget, NULL if index is out of bounds
 */
Widget* container_get_child(const Widget* container, int index);

/**
 * @brief Set the background color of a container
 * 
 * @param container Container to set color for
 * @param color Color to set
 */
void container_set_background_color(Widget* container, Color color);

#endif /* UI_FRAMEWORK_CONTAINER_H */
