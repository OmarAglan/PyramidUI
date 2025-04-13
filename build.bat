@echo off
if exist build rmdir /s /q build
mkdir build
cd build
REM !!! IMPORTANT: Replace D:/src/vcpkg with YOUR actual vcpkg path !!!
set VCPKG_ROOT=C:/src/vcpkg/vcpkg
cmake .. -G "Ninja" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake
cmake --build .
