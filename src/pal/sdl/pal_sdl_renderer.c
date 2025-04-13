#include "ui_framework/pal/pal_renderer.h"
#include "ui_framework/pal/pal_window.h"

#include <glad/glad.h>
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Define PAL_Window struct again to access SDL_Window and SDL_GLContext
struct PAL_Window {
    SDL_Window* sdl_window;
    SDL_GLContext gl_context;
    bool should_close_flag;
};

// Internal structure for the opaque PAL_Renderer handle
struct PAL_Renderer {
    PAL_Window* pal_window;
    SDL_GLContext gl_context;

    GLuint shader_program;
    GLuint vao;
    GLuint vbo;
    GLuint default_texture; // 1x1 white texture

    // Uniform locations
    GLint proj_matrix_location;
    GLint texture_sampler_location;

    int window_width;
    int window_height;
};

// --- Shader Code --- //
const char* vertex_shader_source = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aColor;

out vec2 TexCoord;
out vec4 FragColor;

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
    FragColor = aColor;
}
)";

const char* fragment_shader_source = R"(
#version 330 core
in vec2 TexCoord;
in vec4 FragColor;

out vec4 color;

uniform sampler2D textureSampler;

void main() {
    color = FragColor * texture(textureSampler, TexCoord);
}
)";

// --- Helper Functions --- //
static GLuint compile_shader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "PAL Renderer Error: Shader compilation failed (%s):\n%s\n", 
                (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"), infoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static GLuint link_program(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        fprintf(stderr, "PAL Renderer Error: Shader program linking failed:\n%s\n", infoLog);
        glDeleteProgram(program);
        return 0;
    }
    // Shaders can be deleted after linking
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}

// --- Renderer Lifecycle --- //

PAL_Renderer* pal_renderer_create(PAL_Window* window) {
    if (!window || !window->sdl_window) {
        fprintf(stderr, "PAL Renderer Error: Invalid PAL_Window provided.\n");
        return NULL;
    }

    // Create OpenGL context using SDL
    window->gl_context = SDL_GL_CreateContext(window->sdl_window);
    if (!window->gl_context) {
        fprintf(stderr, "PAL Renderer Error: Failed to create SDL GL context: %s\n", SDL_GetError());
        return NULL;
    }

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        fprintf(stderr, "PAL Renderer Error: Failed to initialize GLAD\n");
        SDL_GL_DeleteContext(window->gl_context);
        window->gl_context = NULL;
        return NULL;
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));

    // Allocate renderer structure
    PAL_Renderer* renderer = (PAL_Renderer*)calloc(1, sizeof(PAL_Renderer)); // Use calloc for zero-init
    if (!renderer) {
        fprintf(stderr, "PAL Renderer Error: Failed to allocate PAL_Renderer structure\n");
        SDL_GL_DeleteContext(window->gl_context);
        window->gl_context = NULL;
        return NULL;
    }

    renderer->pal_window = window;
    renderer->gl_context = window->gl_context;

    // Initial GL setup (viewport, clear color etc.)
    pal_window_get_size(window, &renderer->window_width, &renderer->window_height);
    glViewport(0, 0, renderer->window_width, renderer->window_height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Default clear color

    // Make the context current
    SDL_GL_MakeCurrent(window->sdl_window, renderer->gl_context);

    // Enable VSync (optional, often desired)
    if (SDL_GL_SetSwapInterval(1) < 0) {
        fprintf(stderr, "Warning: Unable to set VSync: %s\n", SDL_GetError());
    }

    // --- Compile and Link Shaders --- //
    GLuint vert_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
    GLuint frag_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
    if (!vert_shader || !frag_shader) {
        // Error message already printed in compile_shader
        glDeleteShader(vert_shader); // In case one succeeded
        glDeleteShader(frag_shader);
        SDL_GL_DeleteContext(window->gl_context);
        window->gl_context = NULL;
        free(renderer);
        return NULL;
    }

    renderer->shader_program = link_program(vert_shader, frag_shader);
    if (!renderer->shader_program) {
        // Error message already printed in link_program
        SDL_GL_DeleteContext(window->gl_context);
        window->gl_context = NULL;
        free(renderer);
        return NULL;
    }

    // Get uniform locations
    renderer->proj_matrix_location = glGetUniformLocation(renderer->shader_program, "projection");
    renderer->texture_sampler_location = glGetUniformLocation(renderer->shader_program, "textureSampler");

    // --- Create VAO and VBO --- //
    glGenVertexArrays(1, &renderer->vao);
    glGenBuffers(1, &renderer->vbo);

    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);

    // --- Setup Vertex Attributes --- //
    // Position attribute (vec2)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(PAL_Vertex), (void*)offsetof(PAL_Vertex, x));
    glEnableVertexAttribArray(0);
    // Texture coordinate attribute (vec2)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(PAL_Vertex), (void*)offsetof(PAL_Vertex, u));
    glEnableVertexAttribArray(1);
    // Color attribute (vec4 - interpreted from uint32_t ABGR)
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(PAL_Vertex), (void*)offsetof(PAL_Vertex, color)); // GL_TRUE normalizes 0-255 to 0.0-1.0
    glEnableVertexAttribArray(2);

    // Unbind VBO and VAO (good practice)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // --- Create Default Texture (1x1 White Pixel) --- //
    uint32_t white_pixel = 0xFFFFFFFF; // ABGR format (fully opaque white)
    glGenTextures(1, &renderer->default_texture);
    glBindTexture(GL_TEXTURE_2D, renderer->default_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Use GL_BGRA because our white_pixel is ABGR and OpenGL on Windows often expects BGRA upload order
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_BGRA, GL_UNSIGNED_BYTE, &white_pixel);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind

    // --- Set Initial GL State --- //
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    printf("PAL Renderer Initialized Successfully.\n");
    return renderer;
}

void pal_renderer_destroy(PAL_Renderer* renderer) {
    if (!renderer) return;

    // Delete OpenGL objects
    glDeleteProgram(renderer->shader_program);
    glDeleteVertexArrays(1, &renderer->vao);
    glDeleteBuffers(1, &renderer->vbo);
    glDeleteTextures(1, &renderer->default_texture);
    // TODO: Need a way to track and delete user-created textures

    if(renderer->gl_context) { SDL_GL_DeleteContext(renderer->gl_context); }

    free(renderer);
}

// --- Frame Operations --- //
void pal_renderer_begin_frame(PAL_Renderer* renderer, Color clear_color) {
    if (!renderer) return;
    SDL_GL_MakeCurrent(renderer->pal_window->sdl_window, renderer->gl_context);
    // TODO: Check if window size changed, update viewport if needed
    float r = clear_color.r / 255.0f;
    float g = clear_color.g / 255.0f;
    float b = clear_color.b / 255.0f;
    float a = clear_color.a / 255.0f; // Use alpha too
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
    // Reset scissor for the frame
    pal_renderer_reset_scissor(renderer);
}

void pal_renderer_end_frame(PAL_Renderer* renderer) {
    if (!renderer || !renderer->pal_window || !renderer->pal_window->sdl_window) return;
    // TODO: Flush any batched draw calls here if implementing batching
    SDL_GL_SwapWindow(renderer->pal_window->sdl_window);
}

// --- Texture Management --- //
PAL_TextureHandle pal_renderer_create_texture(PAL_Renderer* renderer, int width, int height, const void* data) {
    if (!renderer || width <= 0 || height <= 0) return NULL;

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Setup texture parameters (common settings)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Upload texture data (assuming 32-bit RGBA input, uploaded as BGRA)
    // Note: The format GL_BGRA is common for SDL surfaces / typical image loading on Windows.
    // If your input 'data' is RGBA, use GL_RGBA here.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind

    // Use casting to store GLuint in the opaque handle
    return (PAL_TextureHandle)(uintptr_t)texture_id;
}

void pal_renderer_update_texture(PAL_Renderer* renderer, PAL_TextureHandle texture, int width, int height, const void* data) {
    if (!renderer || !texture || !data || width <= 0 || height <= 0) return;

    GLuint texture_id = (GLuint)(uintptr_t)texture;
    glBindTexture(GL_TEXTURE_2D, texture_id);
    // Assuming the texture format doesn't change, just update sub-region or full texture
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void pal_renderer_destroy_texture(PAL_Renderer* renderer, PAL_TextureHandle texture) {
    if (!renderer || !texture) return;
    GLuint texture_id = (GLuint)(uintptr_t)texture;
    glDeleteTextures(1, &texture_id);
}

// --- Drawing Operations --- //
void pal_renderer_set_scissor(PAL_Renderer* renderer, int x, int y, int width, int height) {
    if (!renderer) return;
    // OpenGL scissor origin is bottom-left, UI coords often top-left.
    // Need window height to convert.
    int window_h = renderer->window_height; 
    glEnable(GL_SCISSOR_TEST);
    glScissor(x, window_h - (y + height), width, height);
}

void pal_renderer_reset_scissor(PAL_Renderer* renderer) {
    if (!renderer) return;
    glDisable(GL_SCISSOR_TEST);
    // Technically redundant if viewport covers window, but good practice
    // glScissor(0, 0, renderer->window_width, renderer->window_height); 
}

void pal_renderer_render_triangles(PAL_Renderer* renderer, PAL_TextureHandle texture, const PAL_Vertex* vertices, size_t vertex_count) {
    if (!renderer || !vertices || vertex_count == 0 || !renderer->shader_program || !renderer->vao || !renderer->vbo) return;

    glUseProgram(renderer->shader_program);
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);

    // Upload vertex data (using GL_DYNAMIC_DRAW for frequent updates)
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(PAL_Vertex), vertices, GL_DYNAMIC_DRAW);

    // Setup orthographic projection matrix
    // Maps rendering coordinates (typically pixel coordinates) to OpenGL clip space (-1 to 1)
    float L = 0.0f;
    float R = (float)renderer->window_width;
    float B = (float)renderer->window_height; // Bottom (adjust if Y-down needed)
    float T = 0.0f;                    // Top
    // If Y should be down (common for UI): B=0, T=height
    // B = 0.0f;
    // T = (float)renderer->window_height;
    const float ortho_projection[4][4] = {
        { 2.0f/(R-L),   0.0f,         0.0f,   0.0f },
        { 0.0f,         2.0f/(T-B),   0.0f,   0.0f },
        { 0.0f,         0.0f,        -1.0f,   0.0f },
        { (R+L)/(L-R),  (T+B)/(B-T),  0.0f,   1.0f },
    };
    glUniformMatrix4fv(renderer->proj_matrix_location, 1, GL_FALSE, &ortho_projection[0][0]);

    // Bind texture
    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
    GLuint texture_id = texture ? (GLuint)(uintptr_t)texture : renderer->default_texture;
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(renderer->texture_sampler_location, 0); // Tell shader to use texture unit 0

    // Draw the triangles
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertex_count);

    // Unbind (good practice)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void pal_renderer_render_textured_quad(PAL_Renderer* renderer, PAL_TextureHandle texture, 
                                     float x, float y, float w, float h, 
                                     float u0, float v0, float u1, float v1, 
                                     Color color) {
    if (!renderer) return;

    // Pack RGBA struct into ABGR uint32_t for vertex color attribute
    uint32_t vert_color = ((uint32_t)color.a << 24) |
                          ((uint32_t)color.b << 16) |
                          ((uint32_t)color.g << 8)  |
                          ((uint32_t)color.r);

    PAL_Vertex vertices[6] = {
        { x,     y,     u0, v0, vert_color },
        { x + w, y,     u1, v0, vert_color },
        { x,     y + h, u0, v1, vert_color },

        { x + w, y,     u1, v0, vert_color },
        { x + w, y + h, u1, v1, vert_color },
        { x,     y + h, u0, v1, vert_color }
    };

    pal_renderer_render_triangles(renderer, texture, vertices, 6);
} 