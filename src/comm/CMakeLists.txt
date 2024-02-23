cmake_minimum_required(VERSION 3.22.1)
project(thread-tester-engine-src-comm)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(thread-tester-engine-src-comm
    event_logger.cpp
)

target_compile_options(thread-tester-engine-src-comm PRIVATE
)
