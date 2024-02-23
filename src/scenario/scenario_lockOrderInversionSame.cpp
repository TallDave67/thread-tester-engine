#include "scenario_lockOrderInversionSame.h"
#include "event_logger.h"
#include <mutex>
#include <sstream>

std::timed_mutex g_mutex_lockOrderInversionSame_1;
std::timed_mutex g_mutex_lockOrderInversionSame_2;

Scenario_lockOrderInversionSame_A::Scenario_lockOrderInversionSame_A()
{
    id = "lockOrderInversionSame_A";
}

Scenario_lockOrderInversionSame_A::~Scenario_lockOrderInversionSame_A()
{

}

int Scenario_lockOrderInversionSame_A::do_run()
{
    // ***** Step 1

    // Attempt to acquire the lock on the 1st mutex with a timeout
    bool lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInversionSame_1);

    // Use the lock if acquired
    if (lockAcquired) 
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " acquired lock on mutex g_mutex_lockOrderInversionSame_1";
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
            ss << "scenario with id = " << get_id() << " unable to acquire lock on mutex g_mutex_lockOrderInversionSame_1 within the timeout";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        return SCENARIO_RUN_ABORT;

    }

    // ***** Step 2

    // Attempt to acquire the lock on the 2nd mutex with a timeout
    lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInversionSame_2);

    // Use the lock if acquired
    if (lockAcquired) 
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " acquired lock on mutex g_mutex_lockOrderInversionSame_2";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Release the lock on the 1st mutex
        g_mutex_lockOrderInversionSame_1.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionSame_1";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Perform operations with the lock
        short_loop();
        
        // Release the lock
        g_mutex_lockOrderInversionSame_2.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionSame_2";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }
    }
    else
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " unable to acquire lock on mutex g_mutex_lockOrderInversionSame_2 within the timeout";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Release the lock on the 1st
        g_mutex_lockOrderInversionSame_1.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionSame_1";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        return SCENARIO_RUN_ABORT;
    }

    return SCENARIO_RUN_SUCCESS;
}

Scenario_lockOrderInversionSame_B::Scenario_lockOrderInversionSame_B()
{
    id = "lockOrderInversionSame_B";
}

Scenario_lockOrderInversionSame_B::~Scenario_lockOrderInversionSame_B()
{
}

int Scenario_lockOrderInversionSame_B::do_run()
{
    // ***** Step 1

    // Attempt to acquire the lock on the 1st mutex with a timeout
    bool lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInversionSame_1);

    // Use the lock if acquired
    if (lockAcquired) 
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " acquired lock on mutex g_mutex_lockOrderInversionSame_1";
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
            ss << "scenario with id = " << get_id() << " unable to acquire lock on mutex g_mutex_lockOrderInversionSame_1 within the timeout";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        return SCENARIO_RUN_ABORT;
    }

    // ***** Step 2

    // Attempt to acquire the lock on the 2nd mutex with a timeout
    lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInversionSame_2);

    // Use the lock if acquired
    if (lockAcquired) 
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " acquired lock on mutex g_mutex_lockOrderInversionSame_2";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Release the lock on the 1st
        g_mutex_lockOrderInversionSame_1.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionSame_1";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Perform operations with the lock
        short_loop();
        
        // Release the lock
        g_mutex_lockOrderInversionSame_2.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionSame_2";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }
    }
    else
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " unable to acquire lock on mutex g_mutex_lockOrderInversionSame_2 within the timeout";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // Release the lock on the 1st
        g_mutex_lockOrderInversionSame_1.unlock();

        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "scenario with id = " << get_id() << " released lock on mutex g_mutex_lockOrderInversionSame_1";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        return SCENARIO_RUN_ABORT;
    }

    return SCENARIO_RUN_SUCCESS;
}
