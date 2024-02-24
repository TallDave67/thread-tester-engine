cmake_minimum_required(VERSION 3.22.1)
project(thread-tester-engine-src-scenario)

set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(
    ../comm
    ../util
)

add_library(thread-tester-engine-src-scenario
    scenario.cpp
    scenario_lockOrderSame.cpp
    scenario_lockOrderInverted.cpp
)

target_compile_options(thread-tester-engine-src-scenario PRIVATE
)
