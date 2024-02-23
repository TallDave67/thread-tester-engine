#ifndef THREAD_CONSTANTS_H
#define THREAD_CONSTANTS_H

#include <limits>
#include <chrono>

constexpr int MAX_THREADS = std::numeric_limits<int>::max();
constexpr auto THREAD_TRY_LOCK_TIMEOUT = std::chrono::microseconds(5000000);

constexpr int NUM_SHORT_LOOP_ITERATIONS = 10;
constexpr int NUM_LONG_LOOP_ITERATIONS = 100;
constexpr auto LOOP_ITERATION_DELAY = std::chrono::microseconds(5000);

#endif //THREAD_CONSTANTS_H
