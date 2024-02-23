cmake_minimum_required(VERSION 3.22.1)
project(thread-tester-engine-src)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(comm)
add_subdirectory(core)
add_subdirectory(scenario)
add_subdirectory(util)
include_directories(
    comm
    core
    scenario
    util
)

add_library(thread-tester-engine-src
    src_main.cpp
)

target_compile_options(thread-tester-engine-src PRIVATE
)

target_link_libraries(thread-tester-engine-src
        thread-tester-engine-src-comm
        thread-tester-engine-src-core
        thread-tester-engine-src-scenario
        thread-tester-engine-src-util
)
