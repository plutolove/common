cmake_minimum_required(VERSION 3.17)
project(patterns)

set(CMAKE_CXX_STANDARD 20)

find_package(LLVM REQUIRED CONFIG)
find_package(Boost REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/fmt)
include_directories(${CMAKE_SOURCE_DIR}/deps/fmt/include)

include_directories(${CMAKE_SOURCE_DIR}/src/)
file(GLOB_RECURSE SRC_FILE ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*/*.cpp)

add_executable(patterns ${SRC_FILE})

target_link_libraries(patterns ${Boost_LIBRARIES} LLVM fmt-header-only)