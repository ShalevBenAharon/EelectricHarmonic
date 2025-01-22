cmake_minimum_required(VERSION 3.10)

# Project Name
project(Electric_Harmonica)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include "C:/msys64/mingw64/include")

# Source files
file(GLOB SOURCES
    "main.cpp"
    "src/*.cpp"
)

# Create executable
add_executable(Electric_Harmonica ${SOURCES})

# Link FluidSynth library
target_link_libraries(Electric_Harmonica "C:/msys64/mingw64/lib/libfluidsynth.dll.a")

# Set C and C++ compilers
set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")
