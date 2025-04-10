# UI-Framwork

A simple C UI framework.

## Building with CMake

### Prerequisites
- CMake (version 3.10 or higher)
- A C compiler (gcc, clang, etc.)

### Building on Unix-like systems
```bash
# Option 1: Using the build script
chmod +x build.sh
./build.sh

# Option 2: Manual build
mkdir -p build
cd build
cmake ..
make
```

### Building on Windows with MinGW
```batch
# Option 1: Using the build script
build.bat

# Option 2: Manual build
if not exist build mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### Running the program
After building, the executable will be located in the `build` directory.
