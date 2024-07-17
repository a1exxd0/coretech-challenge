# CMakeLists.txt

# Specify project make details
cmake_minimum_required(VERSION 3.22)
project(coretechchallenge)

# Set minimum C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3 -march=native -flto -funroll-loops")

# Add more optimization flags for an actual build
# Good idea for debugging steps to use this though!
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -ffast-math -funsafe-math-optimizations -fstrict-aliasing -mtune=native")

# Add source directory
add_subdirectory(src)

# Add benchmark directory
add_subdirectory(benchmarks)

# Add testing directory
enable_testing()
add_subdirectory(test)