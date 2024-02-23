cmake_minimum_required(VERSION 3.22.1)
project(thread-tester-engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(src)
include_directories(
        src
        src/comm
        src/core
        src/scenario
        src/util
)

add_executable(thread-tester-engine main.cpp)

target_link_libraries(thread-tester-engine thread-tester-engine-src)
