# From the root of your project
#mkdir build
#cd build

# Configure with CMake for x64 architecture
#cmake .. -G "Visual Studio 16 2019" -A x64

# Build the project in Release mode (for x64)
#cmake --build . --config Release
#cmake --build . --config Debug


cmake_minimum_required(VERSION 3.10)

# Project Name
project(Electric_Harmonica)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Source files
file(GLOB SOURCES
    "main.cpp"
    "src/*.cpp"    # Include all .cpp files from the src folder
    "src/reciverTask.cpp"  # Explicitly include reciverTask.cpp if not caught by globbing
)

# Header files
file(GLOB HEADERS
    "include/*.hpp"  # Adjust this if you store headers in another directory
    "incllude/fluidsynth/*.h"
)

# Include directories
include_directories(include)

# Create executable
add_executable(Electric_Harmonica ${SOURCES} ${HEADERS})

# Link FluidSynth library (ensure you have the MSVC-compatible FluidSynth version)
# Update the path here to point to the MSVC version of FluidSynth
target_link_libraries(Electric_Harmonica "${CMAKE_SOURCE_DIR}/lib/libfluidsynth.dll.a")

# Link necessary Windows libraries (kernel32 and for Winsock and serial)
target_link_libraries(Electric_Harmonica kernel32)

# Use MSVC as the compiler (don't need to specify manually unless needed)
# Remove the lines setting CMAKE_C_COMPILER and CMAKE_CXX_COMPILER for MSVC
