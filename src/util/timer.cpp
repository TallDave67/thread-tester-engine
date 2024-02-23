#include "timer.h"

Timer::Timer()
    : running(false)
{

}

void Timer::start()
{
    startTimePoint = std::chrono::steady_clock::now();
    running = true;
}

void Timer::stop() {
    endTimePoint = std::chrono::steady_clock::now();
    running = false;
}

long long Timer::duration_in_microseconds() const
{
    if (running) {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startTimePoint);
        return duration.count();
    } else {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTimePoint - startTimePoint);
        return duration.count();
    }
}
