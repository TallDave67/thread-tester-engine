#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>

class Timer
{
public:
    Timer();

    void start();
    void stop();
    long long duration_in_microseconds() const;

private:
    std::chrono::time_point<std::chrono::steady_clock> startTimePoint;
    std::chrono::time_point<std::chrono::steady_clock> endTimePoint;
    bool running;
};

#endif
