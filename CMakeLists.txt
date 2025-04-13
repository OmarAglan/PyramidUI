cmake_minimum_required(VERSION 3.10)
project(UI-Framework C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find required libraries
find_package(SDL2 REQUIRED)
find_package(glad CONFIG REQUIRED) # Find glad via vcpkg config
find_package(OpenGL REQUIRED) # Find the system OpenGL library

# Add compiler flags
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # Removed include/glad
)

# Define core framework source files (excluding old window.c and pal implementation)
set(FRAMEWORK_SOURCES
    src/widgets/widget.c
    src/widgets/button.c
    src/drawing/color.c
    src/drawing/primitives.c
    src/drawing/canvas.c
    # Exclude src/core/window.c
)

# Define PAL implementation source files
set(PAL_SOURCES
    src/pal/sdl/pal_sdl_window.c
    src/pal/sdl/pal_sdl_input.c
    src/pal/sdl/pal_sdl_renderer.c
    # Removed src/pal/glad/glad.c
)

# Define main application source file
set(MAIN_SOURCE src/Main.c)

# Add executable
add_executable(ui_framework
    ${FRAMEWORK_SOURCES}
    ${PAL_SOURCES}
    ${MAIN_SOURCE}
)

# Link libraries
target_link_libraries(ui_framework PRIVATE SDL2::SDL2 OpenGL::GL glad::glad)

# Install targets
install(TARGETS ui_framework DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
