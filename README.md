# UI-Framwork

A simple C UI framework.

## Building with CMake

### Prerequisites
- CMake (version 3.10 or higher)
- A C compiler (gcc, clang, etc.)
- [SDL2 Development Library](https://github.com/libsdl-org/SDL/)
- (Windows) Ninja build system
- (Windows) [vcpkg](https://github.com/microsoft/vcpkg) package manager

### Building on Unix-like systems
```bash
# Ensure SDL2 development package is installed (e.g., libsdl2-dev on Debian/Ubuntu)
# Option 1: Using the build script
chmod +x build.sh
./build.sh

# Option 2: Manual build
mkdir -p build
cd build
cmake ..
make
```

### Building on Windows

**Prerequisites:**
1.  Install a C compiler (e.g., Clang, GCC via MinGW, or MSVC).
2.  Install Ninja and ensure it's in your PATH.
3.  Install vcpkg.
4.  Install required libraries using vcpkg:
    ```bash
    cd path/to/vcpkg
    .\vcpkg install sdl2:x64-windows glad:x64-windows
    ```
    (Replace `x64-windows` with your target triplet if needed).

**Build Steps:**
1.  Edit `build.bat` and set `VCPKG_ROOT` to your vcpkg installation path.
2.  Run the build script from the project root:
    ```batch
    .\build.bat
    ```

### Running the program
After building, the executable `ui_framework.exe` (Windows) or `ui_framework` (Unix) will be located in the `build` directory.
