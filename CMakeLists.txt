cmake_minimum_required(VERSION 3.17)
project(patterns)

set(CMAKE_CXX_STANDARD 20)

find_package(Arrow REQUIRED)
find_package(Boost REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/src/)
file(GLOB_RECURSE SRC_FILE ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*/*.cpp)

add_executable(patterns ${SRC_FILE})

target_link_libraries(patterns ${Boost_LIBRARIES} ${arrow_shared})