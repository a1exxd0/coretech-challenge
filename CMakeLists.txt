# CMakeLists.txt

# Specify project make details
cmake_minimum_required(VERSION 3.22)
project(coretechchallenge)

# Set minimum C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -fopenmp")

# Add more optimization flags for an actual build
# Good idea for debugging steps to use this though!
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -march=native")

# Add source directory
add_subdirectory(src)

# Add benchmark directory
add_subdirectory(benchmark)

# Add testing directory
enable_testing()
add_subdirectory(test)