/**
 * @file layout.h
 * @brief Layout management for the UI Framework
 */

#ifndef UI_FRAMEWORK_LAYOUT_H
#define UI_FRAMEWORK_LAYOUT_H

#include "../widgets/container.h"

/**
 * @brief Layout type enumeration
 */
typedef enum {
    LAYOUT_NONE,
    LAYOUT_HORIZONTAL,
    LAYOUT_VERTICAL,
    LAYOUT_GRID
} LayoutType;

/**
 * @brief Set the layout type for a container
 * 
 * @param container Container to set layout for
 * @param type Layout type
 * @return int 0 on success, -1 on failure
 */
int layout_set_type(Widget* container, LayoutType type);

/**
 * @brief Set the padding for a container's layout
 * 
 * @param container Container to set padding for
 * @param padding Padding value in pixels
 * @return int 0 on success, -1 on failure
 */
int layout_set_padding(Widget* container, int padding);

/**
 * @brief Set the spacing between elements in a container's layout
 * 
 * @param container Container to set spacing for
 * @param spacing Spacing value in pixels
 * @return int 0 on success, -1 on failure
 */
int layout_set_spacing(Widget* container, int spacing);

/**
 * @brief Set the number of columns for a grid layout
 * 
 * @param container Container with grid layout
 * @param columns Number of columns
 * @return int 0 on success, -1 on failure
 */
int layout_grid_set_columns(Widget* container, int columns);

/**
 * @brief Set the number of rows for a grid layout
 * 
 * @param container Container with grid layout
 * @param rows Number of rows
 * @return int 0 on success, -1 on failure
 */
int layout_grid_set_rows(Widget* container, int rows);

/**
 * @brief Apply the current layout to a container
 * 
 * @param container Container to apply layout to
 * @return int 0 on success, -1 on failure
 */
int layout_apply(Widget* container);

#endif /* UI_FRAMEWORK_LAYOUT_H */
