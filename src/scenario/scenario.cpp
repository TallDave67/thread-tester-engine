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

    // log the event ?
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event_type\":\"run\", \"event\":\"start\", \"object\":\"scenario\", \"id\":\"" << get_id() << "\", \"duration\":0}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    int ret = do_run();

    timer.stop();

    // log the event ?
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event_type\":\"run\", \"event\":\"finish\", \"object\":\"scenario\", \"id\":\"" << get_id() <<  "\", \"duration\":" << timer.duration_in_microseconds() << "}";
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
    // log the event ?
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event_type\":\"acquire_lock\", \"event\":\"start\", \"object\":\"mutex\", \"id\":\"" << name <<  "\", \"parent_object\":\"scenario\", \"parent_id\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    // Try to acquire the lock on the mutex with a timeout
    if (mtx.try_lock_for(THREAD_TRY_LOCK_TIMEOUT)) 
    {
        // Lock acquired successfully

        // log the events ?
        if(m_pEventLogger)
        {
            {
                std::stringstream ss;
                ss << "{\"event_type\":\"acquire_lock\", \"event\":\"finish_success\", \"object\":\"mutex\", \"id\":\"" << name <<  "\", \"parent_object\":\"scenario\", \"parent_id\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
                std::string event = ss.str();
                m_pEventLogger->send_event(event);
            }
            {
                std::stringstream ss;
                ss << "{\"event_type\":\"use_lock\", \"event\":\"start\", \"object\":\"mutex\", \"id\":\"" << name <<  "\", \"parent_object\":\"scenario\", \"parent_id\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
                std::string event = ss.str();
                m_pEventLogger->send_event(event);
            }
        }

        return true;
    }
    else
    {
        // Unable to acquire the lock within the timeout

        // log the event ?
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "{\"event_type\":\"acquire_lock\", \"event\":\"finish_failure\", \"object\":\"mutex\", \"id\":\"" << name <<  "\", \"parent_object\":\"scenario\", \"parent_id\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
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

    // log the event ?
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event_type\":\"use_lock\", \"event\":\"finish\", \"object\":\"mutex\", \"id\":\"" << name <<  "\", \"parent_object\":\"scenario\", \"parent_id\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }
}

void Scenario::arrive_and_wait(std::latch & lat, const char* name)
{
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event_type\":\"wait\", \"event\":\"start\", \"object\":\"latch\", \"id\":\"" << name <<  "\", \"parent_object\":\"scenario\", \"parent_id\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    lat.arrive_and_wait();

    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event_type\":\"wait\", \"event\":\"finish\", \"object\":\"latch\", \"id\":\"" << name <<  "\", \"parent_object\":\"scenario\", \"parent_id\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }
}

void Scenario::arrive_and_wait(std::barrier<void(*)(void) noexcept> & bar, const char* name)
{
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event_type\":\"wait\", \"event\":\"start\", \"object\":\"barrier\", \"id\":\"" << name <<  "\", \"parent_object\":\"scenario\", \"parent_id\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    bar.arrive_and_wait();

    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event_type\":\"wait\", \"event\":\"finish\", \"object\":\"barrier\", \"id\":\"" << name <<  "\", \"parent_object\":\"scenario\", \"parent_id\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }
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
        ss << "{\"event_type\":\"short_loop\", \"event\":\"start\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
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
        ss << "{\"event_type\":\"short_loop\", \"event\":\"finish\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }
}

void Scenario::long_loop()
{
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "{\"event_type\":\"long_loop\", \"event\":\"start\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
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
        ss << "{\"event_type\":\"long_loop\", \"event\":\"finish\", \"object\":\"scenario\", \"scenario\":\"" << get_id() << "\", \"duration\":" << timer.duration_in_microseconds() << "}";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }
}