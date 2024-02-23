#include "scenario_lockOrderInversionInverted.h"
#include "event_logger.h"
#include <mutex>
#include <sstream>

std::timed_mutex g_mutex_lockOrderInversionInverted_1;
std::timed_mutex g_mutex_lockOrderInversionInverted_2;

Scenario_lockOrderInversionInverted_A::Scenario_lockOrderInversionInverted_A()
{
    id = "lockOrderInversionInverted_A";
}

Scenario_lockOrderInversionInverted_A::~Scenario_lockOrderInversionInverted_A()
{

}

int Scenario_lockOrderInversionInverted_A::do_run()
{
    // ***** Step 1

    // Attempt to acquire the lock on the 1st mutex with a timeout
    bool lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInversionInverted_1);

    // Use the lock if acquired
    if (lockAcquired) 
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " acquired lock on mutex g_mutex_lockOrderInversionInverted_1";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Perform operations with the lock
        long_loop();
    }
    else
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " unable to acquire lock on mutex g_mutex_lockOrderInversionInverted_1 within the timeout";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        return SCENARIO_RUN_ABORT;
    }

    // ***** Step 2

    // Attempt to acquire the lock on the 2nd mutex with a timeout
    lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInversionInverted_2);

    // Use the lock if acquired
    if (lockAcquired) 
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " acquired lock on mutex g_mutex_lockOrderInversionInverted_2";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Release the lock on the 1st mutex
        g_mutex_lockOrderInversionInverted_1.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionInverted_1";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Perform operations with the lock
        short_loop();
        
        // Release the lock
        g_mutex_lockOrderInversionInverted_2.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionInverted_2";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }
    }
    else
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " unable to acquire lock on mutex g_mutex_lockOrderInversionInverted_2 within the timeout";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Release the lock on the 1st mutex
        g_mutex_lockOrderInversionInverted_1.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionInverted_1";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        return SCENARIO_RUN_ABORT;
    }

    return SCENARIO_RUN_SUCCESS;
}

Scenario_lockOrderInversionInverted_B::Scenario_lockOrderInversionInverted_B()
{
    id = "lockOrderInversionInverted_B";
}

Scenario_lockOrderInversionInverted_B::~Scenario_lockOrderInversionInverted_B()
{
}

int Scenario_lockOrderInversionInverted_B::do_run()
{
    // ***** Step 1

    // Attempt to acquire the lock on the 2nd mutex with a timeout
    bool lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInversionInverted_2);

    // Use the lock if acquired
    if (lockAcquired) 
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " acquired lock on mutex g_mutex_lockOrderInversionInverted_2";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Perform operations with the lock
        short_loop();        
    }
    else
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " unable to acquire lock on mutex g_mutex_lockOrderInversionInverted_2 within the timeout";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        return SCENARIO_RUN_ABORT;
    }

    // ***** Step 2

    // Attempt to acquire the lock on the 1st mutex with a timeout
    lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInversionInverted_1);

    // Use the lock if acquired
    if (lockAcquired) 
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " acquired lock on mutex g_mutex_lockOrderInversionInverted_1";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Release the lock on the 2nd mutex
        g_mutex_lockOrderInversionInverted_2.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionInverted_2";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Perform operations with the lock
        long_loop();
        
        // Release the lock
        g_mutex_lockOrderInversionInverted_1.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionInverted_1";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }
    }
    else
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " unable to acquire lock on mutex g_mutex_lockOrderInversionInverted_1 within the timeout";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Release the lock on the 2nd mutex
        g_mutex_lockOrderInversionInverted_2.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionInverted_2";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        return SCENARIO_RUN_ABORT;
    }

    return SCENARIO_RUN_SUCCESS;
}
