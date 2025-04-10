/**
 * @file widget.c
 * @brief Base widget implementation for the UI Framework
 */

#include "../../include/ui_framework/widgets/widget.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Widget structure implementation
 */
struct Widget {
    int x;
    int y;
    int width;
    int height;
    bool visible;
    bool enabled;
    void* user_data;
    WidgetDrawFunction draw_fn;
    WidgetEventHandler event_handler;
};

Widget* widget_create(int x, int y, int width, int height, 
                     void* user_data, 
                     WidgetDrawFunction draw_fn, 
                     WidgetEventHandler event_handler) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }

    Widget* widget = (Widget*)malloc(sizeof(Widget));
    if (!widget) {
        return NULL;
    }

    widget->x = x;
    widget->y = y;
    widget->width = width;
    widget->height = height;
    widget->visible = true;
    widget->enabled = true;
    widget->user_data = user_data;
    widget->draw_fn = draw_fn;
    widget->event_handler = event_handler;

    return widget;
}

void widget_destroy(Widget* widget) {
    if (!widget) {
        return;
    }

    free(widget);
}

void widget_draw(Widget* widget, Canvas* canvas) {
    if (!widget || !canvas || !widget->visible || !widget->draw_fn) {
        return;
    }

    widget->draw_fn(widget, canvas);
}

bool widget_handle_event(Widget* widget, const Event* event) {
    if (!widget || !event || !widget->enabled || !widget->event_handler) {
        return false;
    }

    return widget->event_handler(widget, event);
}

void widget_set_position(Widget* widget, int x, int y) {
    if (!widget) {
        return;
    }

    widget->x = x;
    widget->y = y;
}

void widget_set_size(Widget* widget, int width, int height) {
    if (!widget || width <= 0 || height <= 0) {
        return;
    }

    widget->width = width;
    widget->height = height;
}

int widget_get_x(const Widget* widget) {
    if (!widget) {
        return 0;
    }
    
    return widget->x;
}

int widget_get_y(const Widget* widget) {
    if (!widget) {
        return 0;
    }
    
    return widget->y;
}

int widget_get_width(const Widget* widget) {
    if (!widget) {
        return 0;
    }
    
    return widget->width;
}

int widget_get_height(const Widget* widget) {
    if (!widget) {
        return 0;
    }
    
    return widget->height;
}

void widget_set_visible(Widget* widget, bool visible) {
    if (!widget) {
        return;
    }
    
    widget->visible = visible;
}

bool widget_is_visible(const Widget* widget) {
    if (!widget) {
        return false;
    }
    
    return widget->visible;
}

void widget_set_enabled(Widget* widget, bool enabled) {
    if (!widget) {
        return;
    }
    
    widget->enabled = enabled;
}

bool widget_is_enabled(const Widget* widget) {
    if (!widget) {
        return false;
    }
    
    return widget->enabled;
}

void* widget_get_user_data(const Widget* widget) {
    if (!widget) {
        return NULL;
    }
    
    return widget->user_data;
}

void widget_set_user_data(Widget* widget, void* user_data) {
    if (!widget) {
        return;
    }
    
    widget->user_data = user_data;
}

bool widget_contains_point(const Widget* widget, int x, int y) {
    if (!widget) {
        return false;
    }
    
    return (x >= widget->x && x < widget->x + widget->width &&
            y >= widget->y && y < widget->y + widget->height);
}
