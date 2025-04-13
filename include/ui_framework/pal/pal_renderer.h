#ifndef PAL_RENDERER_H
#define PAL_RENDERER_H

#include "pal_window.h"
#include "../drawing/color.h" // Include Color type
#include <stddef.h> // For size_t
#include <stdint.h> // For uint32_t

// --- Forward Declarations --- //
typedef struct PAL_Renderer PAL_Renderer;

// --- Vertex Structure --- //
typedef struct {
    float x, y;    // Position
    float u, v;    // Texture Coordinates
    uint32_t color; // Color (e.g., 0xAABBGGRR or 0xAARRGGBB depending on backend needs)
} PAL_Vertex;

// --- Texture Handle --- //
// Opaque handle to a texture managed by the renderer
typedef void* PAL_TextureHandle;

// --- Renderer Lifecycle --- //

/**
 * @brief Creates and initializes the rendering backend for a specific window.
 * @param window The PAL window to associate the renderer with.
 * @return An opaque handle to the renderer, or NULL on failure.
 */
PAL_Renderer* pal_renderer_create(PAL_Window* window);

/**
 * @brief Destroys the renderer and releases graphics resources.
 * @param renderer The renderer handle.
 */
void pal_renderer_destroy(PAL_Renderer* renderer);

// --- Frame Operations --- //

/**
 * @brief Prepares the renderer for a new frame.
 * @param renderer The renderer handle.
 * @param clear_color The color to clear the background with.
 */
void pal_renderer_begin_frame(PAL_Renderer* renderer, Color clear_color);

/**
 * @brief Presents the completed frame to the window.
 * @param renderer The renderer handle.
 */
void pal_renderer_end_frame(PAL_Renderer* renderer);

// --- Texture Management --- //

/**
 * @brief Creates a texture from raw pixel data (e.g., RGBA).
 * @param renderer The renderer handle.
 * @param width Texture width.
 * @param height Texture height.
 * @param data Pointer to pixel data (e.g., 32-bit RGBA).
 * @return An opaque texture handle, or NULL on failure.
 */
PAL_TextureHandle pal_renderer_create_texture(PAL_Renderer* renderer, int width, int height, const void* data);

/**
 * @brief Updates an existing texture with new pixel data.
 * @param renderer The renderer handle.
 * @param texture The texture handle to update.
 * @param width Texture width.
 * @param height Texture height.
 * @param data Pointer to new pixel data.
 */
void pal_renderer_update_texture(PAL_Renderer* renderer, PAL_TextureHandle texture, int width, int height, const void* data);

/**
 * @brief Destroys a texture and releases its resources.
 * @param renderer The renderer handle.
 * @param texture The texture handle to destroy.
 */
void pal_renderer_destroy_texture(PAL_Renderer* renderer, PAL_TextureHandle texture);

// --- Drawing Operations --- //

/**
 * @brief Sets the active scissor rectangle for clipping.
 *        Draw calls will be clipped to this rectangle.
 * @param renderer The renderer handle.
 * @param x Scissor rectangle X coordinate.
 * @param y Scissor rectangle Y coordinate.
 * @param width Scissor rectangle width.
 * @param height Scissor rectangle height.
 */
void pal_renderer_set_scissor(PAL_Renderer* renderer, int x, int y, int width, int height);

/**
 * @brief Resets the scissor rectangle to the full window/viewport size.
 * @param renderer The renderer handle.
 */
void pal_renderer_reset_scissor(PAL_Renderer* renderer);

/**
 * @brief Submits a list of vertices to be rendered as triangles.
 *        Assumes vertices are grouped into triangles (3 vertices per triangle).
 *        Uses the specified texture.
 * @param renderer The renderer handle.
 * @param texture The texture handle to use (can be NULL for untextured colored triangles).
 * @param vertices Pointer to the vertex data.
 * @param vertex_count The number of vertices.
 */
void pal_renderer_render_triangles(PAL_Renderer* renderer, PAL_TextureHandle texture, const PAL_Vertex* vertices, size_t vertex_count);

/**
 * @brief Helper to render a simple textured quad (composed of two triangles).
 * @param renderer The renderer handle.
 * @param texture The texture handle.
 * @param x Top-left X.
 * @param y Top-left Y.
 * @param w Width.
 * @param h Height.
 * @param u0 Top-left U coord.
 * @param v0 Top-left V coord.
 * @param u1 Bottom-right U coord.
 * @param v1 Bottom-right V coord.
 * @param color Tint color modulation (multiplied with texture color).
 */
void pal_renderer_render_textured_quad(PAL_Renderer* renderer, PAL_TextureHandle texture, 
                                     float x, float y, float w, float h, 
                                     float u0, float v0, float u1, float v1, 
                                     Color color);


#endif // PAL_RENDERER_H 