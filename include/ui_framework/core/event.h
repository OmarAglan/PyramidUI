/**
 * @file event.h
 * @brief Event handling for the UI Framework
 */

#ifndef UI_FRAMEWORK_EVENT_H
#define UI_FRAMEWORK_EVENT_H

#include <stdint.h>

/**
 * @brief Event types
 */
typedef enum {
    EVENT_NONE,
    
    /* Window events */
    EVENT_WINDOW_CLOSE,
    EVENT_WINDOW_RESIZE,
    EVENT_WINDOW_FOCUS,
    EVENT_WINDOW_UNFOCUS,
    
    /* Mouse events */
    EVENT_MOUSE_MOVE,
    EVENT_MOUSE_BUTTON_PRESS,
    EVENT_MOUSE_BUTTON_RELEASE,
    EVENT_MOUSE_SCROLL,
    
    /* Keyboard events */
    EVENT_KEY_PRESS,
    EVENT_KEY_RELEASE,
    EVENT_CHAR_INPUT,
    
    /* Widget events */
    EVENT_WIDGET_CLICK,
    EVENT_WIDGET_FOCUS,
    EVENT_WIDGET_UNFOCUS,
    
    EVENT_COUNT
} EventType;

/**
 * @brief Mouse button identifiers
 */
typedef enum {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_COUNT
} MouseButton;

/**
 * @brief Event data structure
 */
typedef struct {
    EventType type;
    
    union {
        /* Window resize data */
        struct {
            int width;
            int height;
        } window_resize;
        
        /* Mouse move data */
        struct {
            int x;
            int y;
            int dx;
            int dy;
        } mouse_move;
        
        /* Mouse button data */
        struct {
            int x;
            int y;
            MouseButton button;
        } mouse_button;
        
        /* Mouse scroll data */
        struct {
            int x;
            int y;
            float dx;
            float dy;
        } mouse_scroll;
        
        /* Key data */
        struct {
            int key;
            int scancode;
            int mods;
        } key;
        
        /* Character input data */
        struct {
            unsigned int codepoint;
        } char_input;
        
        /* Widget event data */
        struct {
            void* widget;
            int x;
            int y;
        } widget;
    };
} Event;

/**
 * @brief Event callback function
 */
typedef void (*EventCallback)(const Event* event, void* user_data);

/**
 * @brief Event handler structure
 */
typedef struct EventHandler EventHandler;

/**
 * @brief Create a new event handler
 * 
 * @return EventHandler* The event handler
 */
EventHandler* event_handler_create(void);

/**
 * @brief Destroy an event handler
 * 
 * @param handler Event handler to destroy
 */
void event_handler_destroy(EventHandler* handler);

/**
 * @brief Register an event callback
 * 
 * @param handler Event handler
 * @param type Event type to register for
 * @param callback Callback function
 * @param user_data User data to pass to the callback
 * @return int ID of the registered callback
 */
int event_handler_register(EventHandler* handler, EventType type, 
                           EventCallback callback, void* user_data);

/**
 * @brief Unregister an event callback
 * 
 * @param handler Event handler
 * @param id ID of the callback to unregister
 * @return int 0 on success, -1 on failure
 */
int event_handler_unregister(EventHandler* handler, int id);

/**
 * @brief Dispatch an event
 * 
 * @param handler Event handler
 * @param event Event to dispatch
 */
void event_handler_dispatch(EventHandler* handler, const Event* event);

#endif /* UI_FRAMEWORK_EVENT_H */
