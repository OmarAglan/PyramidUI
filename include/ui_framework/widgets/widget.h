/**
 * @file widget.h
 * @brief Base widget for the UI Framework
 */

#ifndef UI_FRAMEWORK_WIDGET_H
#define UI_FRAMEWORK_WIDGET_H

#include "../drawing/canvas.h"
#include "../core/event.h"
#include <stdbool.h>

/**
 * @brief Widget structure
 */
typedef struct Widget Widget;

/**
 * @brief Widget event handler function
 * 
 * @param widget Widget that received the event
 * @param event Event that occurred
 * @return true if the event was handled, false otherwise
 */
typedef bool (*WidgetEventHandler)(Widget* widget, const Event* event);

/**
 * @brief Widget draw function
 * 
 * @param widget Widget to draw
 * @param canvas Canvas to draw on
 */
typedef void (*WidgetDrawFunction)(Widget* widget, Canvas* canvas);

/**
 * @brief Create a new widget
 * 
 * @param x X position
 * @param y Y position
 * @param width Width
 * @param height Height
 * @param user_data User data associated with the widget
 * @param draw_fn Draw function
 * @param event_handler Event handler function
 * @return Widget* Handle to the created widget, NULL on failure
 */
Widget* widget_create(int x, int y, int width, int height, 
                     void* user_data, 
                     WidgetDrawFunction draw_fn, 
                     WidgetEventHandler event_handler);

/**
 * @brief Destroy a widget
 * 
 * @param widget Widget to destroy
 */
void widget_destroy(Widget* widget);

/**
 * @brief Draw a widget
 * 
 * @param widget Widget to draw
 * @param canvas Canvas to draw on
 */
void widget_draw(Widget* widget, Canvas* canvas);

/**
 * @brief Handle an event for a widget
 * 
 * @param widget Widget to handle event for
 * @param event Event to handle
 * @return true if the event was handled, false otherwise
 */
bool widget_handle_event(Widget* widget, const Event* event);

/**
 * @brief Set the position of a widget
 * 
 * @param widget Widget to set position for
 * @param x X position
 * @param y Y position
 */
void widget_set_position(Widget* widget, int x, int y);

/**
 * @brief Set the size of a widget
 * 
 * @param widget Widget to set size for
 * @param width Width
 * @param height Height
 */
void widget_set_size(Widget* widget, int width, int height);

/**
 * @brief Get the X position of a widget
 * 
 * @param widget Widget to get position for
 * @return int X position
 */
int widget_get_x(const Widget* widget);

/**
 * @brief Get the Y position of a widget
 * 
 * @param widget Widget to get position for
 * @return int Y position
 */
int widget_get_y(const Widget* widget);

/**
 * @brief Get the width of a widget
 * 
 * @param widget Widget to get size for
 * @return int Width
 */
int widget_get_width(const Widget* widget);

/**
 * @brief Get the height of a widget
 * 
 * @param widget Widget to get size for
 * @return int Height
 */
int widget_get_height(const Widget* widget);

/**
 * @brief Set the visible state of a widget
 * 
 * @param widget Widget to set visibility for
 * @param visible Whether the widget should be visible
 */
void widget_set_visible(Widget* widget, bool visible);

/**
 * @brief Check if a widget is visible
 * 
 * @param widget Widget to check
 * @return true if the widget is visible, false otherwise
 */
bool widget_is_visible(const Widget* widget);

/**
 * @brief Set the enabled state of a widget
 * 
 * @param widget Widget to set enabled state for
 * @param enabled Whether the widget should be enabled
 */
void widget_set_enabled(Widget* widget, bool enabled);

/**
 * @brief Check if a widget is enabled
 * 
 * @param widget Widget to check
 * @return true if the widget is enabled, false otherwise
 */
bool widget_is_enabled(const Widget* widget);

/**
 * @brief Get user data associated with a widget
 * 
 * @param widget Widget to get data for
 * @return void* User data
 */
void* widget_get_user_data(const Widget* widget);

/**
 * @brief Set user data associated with a widget
 * 
 * @param widget Widget to set data for
 * @param user_data User data
 */
void widget_set_user_data(Widget* widget, void* user_data);

/**
 * @brief Check if a point is inside a widget
 * 
 * @param widget Widget to check
 * @param x X coordinate
 * @param y Y coordinate
 * @return true if the point is inside the widget, false otherwise
 */
bool widget_contains_point(const Widget* widget, int x, int y);

#endif /* UI_FRAMEWORK_WIDGET_H */
