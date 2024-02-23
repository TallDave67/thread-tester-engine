cmake_minimum_required(VERSION 3.22.1)
project(thread-tester-engine-src-core)

set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(
    ../comm
    ../scenario
    ../util
)

add_library(thread-tester-engine-src-core
    thread_driver.cpp
    thread_manager.cpp
    thread_wrapper.cpp
)

target_compile_options(thread-tester-engine-src-core PRIVATE
)
