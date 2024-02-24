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
        ss << "{\"event\":\"running\", \"scenario\":\"" << get_id() << "\"}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    return do_run();
}

bool Scenario::try_lock_with_timeout(std::timed_mutex & mtx, const char* name)
{
    // Try to acquire the lock on the mutex with a timeout
    if (mtx.try_lock_for(THREAD_TRY_LOCK_TIMEOUT)) 
    {
        // Lock acquired successfully
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "{\"event\":\"acquired lock\", \"scenario\":\"" << get_id() << "\", \"mutex\":\"" << name << "\"}";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        return true;
    }
    else
    {
        // Unable to acquire the lock within the timeout
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "{\"event\":\"unable to acquire lock\", \"scenario\":\"" << get_id() << "\", \"mutex\":\"" << name << "\", \"timeout_microseconds\":" << THREAD_TRY_LOCK_TIMEOUT.count() << "}";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        return false;
    }
}

void Scenario::unlock(std::timed_mutex & mtx, const char* name)
{
    // Release the lock on the mutex
    mtx.unlock();

    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"released lock\", \"scenario\":\"" << get_id() << "\", \"mutex\":\"" << name << "\"}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }
}

void Scenario::arrive_and_wait(std::latch & lat, const char* name)
{
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"arrive_and_wait\", \"scenario\":\"" << get_id() << "\", \"latch\":\"" << name << "\"}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    lat.arrive_and_wait();
}

void Scenario::arrive_and_wait(std::barrier<void(*)(void) noexcept> & bar, const char* name)
{
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"arrive_and_wait\", \"scenario\":\"" << get_id() << "\", \"barrier\":\"" << name << "\"}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    bar.arrive_and_wait();
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

    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"short_loop\", \"scenario\":\"" << get_id() << "\"}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }
}

void Scenario::long_loop()
{
    for(int i = 0; i < NUM_LONG_LOOP_ITERATIONS; i++)
    {
        std::this_thread::sleep_for(LOOP_ITERATION_DELAY);
    }

    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"long_loop\", \"scenario\":\"" << get_id() << "\"}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }
}