# src/CMakeLists.txt
find_package(PcapPlusPlus REQUIRED)

# Add include
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Add executable
add_executable(ctc ${SOURCES})
target_link_libraries(ctc PcapPlusPlus::Pcap++)