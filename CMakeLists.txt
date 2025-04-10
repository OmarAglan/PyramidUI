cmake_minimum_required(VERSION 3.10)
project(UI-Framework C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add compiler flags
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
endif()

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find source files
file(GLOB_RECURSE SOURCES 
    "src/*.c"
)

# Add executable
add_executable(ui_framework ${SOURCES})

# Platform-specific libraries
if(WIN32)
    target_link_libraries(ui_framework PRIVATE winmm)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(ui_framework PRIVATE m)
endif()

# Install targets
install(TARGETS ui_framework DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
