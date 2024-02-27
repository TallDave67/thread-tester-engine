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
    timer.start();

    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"start\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"duration_microseconds\":0}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    int ret = do_run();

    timer.stop();

    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"finish\", \"object\":\"scenario\", \"scenario\":\"" << get_id() <<  ", \"duration_microseconds\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    return ret;
}

long long Scenario::duration_in_microseconds()
{
    return timer.duration_in_microseconds();
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
            ss << "{\"event\":\"acquired lock\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"mutex\":\"" << name << "\", \"duration_microseconds\":" << timer.duration_in_microseconds() << "}";
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
            ss << "{\"event\":\"unable to acquire lock\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"mutex\":\"" << name << "\", \"duration_microseconds\":" << timer.duration_in_microseconds() << "}";
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
        ss << "{\"event\":\"released lock\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"mutex\":\"" << name << "\", \"duration_microseconds\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }
}

void Scenario::arrive_and_wait(std::latch & lat, const char* name)
{
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"latch arrive_and_wait\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"latch\":\"" << name << "\", \"duration_microseconds\":" << timer.duration_in_microseconds() << "}";
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
        ss << "{\"event\":\"barrier arrive_and_wait\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"barrier\":\"" << name << "\", \"duration_microseconds\":" << timer.duration_in_microseconds() << "}";
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
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"start short_loop\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"duration_microseconds\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    for(int i = 0; i < NUM_SHORT_LOOP_ITERATIONS; i++)
    {
        std::this_thread::sleep_for(LOOP_ITERATION_DELAY);
    }

    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"finish short_loop\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"duration_microseconds\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }
}

void Scenario::long_loop()
{
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"start long_loop\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"duration_microseconds\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    for(int i = 0; i < NUM_LONG_LOOP_ITERATIONS; i++)
    {
        std::this_thread::sleep_for(LOOP_ITERATION_DELAY);
    }

    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event\":\"finish long_loop\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"duration_microseconds\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }
}