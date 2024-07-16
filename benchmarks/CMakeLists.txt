# benchmark/CMakeLists.txt

find_package(benchmark REQUIRED)

# Add include
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/benchmark/*.cpp)

# Add executable
add_executable(b_main ${SOURCES} b_main.cpp)

# Link google benchmark
target_link_libraries(b_main PRIVATE benchmark::benchmark)