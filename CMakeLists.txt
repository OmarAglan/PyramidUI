cmake_minimum_required(VERSION 3.10)
project(UI-Framework C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add compiler flags
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
endif()

# Add executable
add_executable(ui_framework src/Main.c)

# Include directories (uncomment if needed)
# target_include_directories(ui_framework PRIVATE include)

# Link libraries (uncomment if needed)
# target_link_libraries(ui_framework PRIVATE some_library)
