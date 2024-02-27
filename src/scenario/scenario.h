#ifndef _SCENARIO_H_
#define _SCENARIO_H_

#include "timer.h"
#include <string>
#include <mutex>
#include <latch>
#include <barrier>

static const int SCENARIO_RUN_ABORT = -2;
static const int SCENARIO_RUN_FAILURE = -1;
static const int SCENARIO_RUN_NOOP = 0;
static const int SCENARIO_RUN_SUCCESS = 1;

class EventLogger;

class Scenario
{
public:
    Scenario();
    virtual ~Scenario();

    void set_event_logger(EventLogger *pEventLogger);
    std::string & get_id();
    int run();
    long long duration_in_microseconds();
    
    bool try_lock_with_timeout(std::timed_mutex & mtx, const char* name);
    void unlock(std::timed_mutex & mtx, const char* name);

    void arrive_and_wait(std::latch & lat, const char* name);
    void arrive_and_wait(std::barrier<void(*)(void) noexcept> & bar, const char* name);

protected:
    virtual int do_run();
    void short_loop();
    void long_loop();

protected:
    EventLogger *m_pEventLogger;
    std::string id;
    //
    Timer timer;
};

#endif
