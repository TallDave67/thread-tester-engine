#include "scenario.h"
#include "event_logger.h"
#include "constants.h"
#include <sstream>

#include <thread>
#include <chrono>
using namespace std::chrono_literals;

Scenario::Scenario()
    : m_pEventLogger(nullptr), id {"default"}
{
}

Scenario::~Scenario()
{
}

void Scenario::set_event_logger(EventLogger *pEventLogger)
{
    m_pEventLogger = pEventLogger;
}

std::string & Scenario::get_id()
{
    return id;
}

int Scenario::run()
{
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "running scenario with id = " << get_id();
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    return do_run();
}

bool Scenario::try_lock_with_timeout(std::timed_mutex & mtx)
{
    // Try to acquire the lock on the mutex with a timeout of 15 seconds
    if (mtx.try_lock_for(THREAD_TRY_LOCK_TIMEOUT)) 
    {
        // Lock acquired successfully
        return true;
    } else
    {
        // Unable to acquire the lock within the timeout
        return false;
    }
}

int Scenario::do_run()
{
    return SCENARIO_RUN_NOOP;
}

void Scenario::short_loop()
{
    for(int i = 0; i < NUM_SHORT_LOOP_ITERATIONS; i++)
    {
        std::this_thread::sleep_for(LOOP_ITERATION_DELAY);
    }
}

void Scenario::long_loop()
{
    for(int i = 0; i < NUM_LONG_LOOP_ITERATIONS; i++)
    {
        std::this_thread::sleep_for(LOOP_ITERATION_DELAY);
    }
}