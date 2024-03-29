#include "scenario_lockOrderInverted.h"
#include "event_logger.h"
#include <mutex>
#include <sstream>

std::timed_mutex g_mutex_lockOrderInverted_1;
std::timed_mutex g_mutex_lockOrderInverted_2;

const char* g_mutex_lockOrderInverted_1_name = "mutex1";
const char* g_mutex_lockOrderInverted_2_name = "mutex2";

Scenario_lockOrderInverted_A::Scenario_lockOrderInverted_A()
{
    id = "lockOrderInverted_A";
}

Scenario_lockOrderInverted_A::~Scenario_lockOrderInverted_A()
{

}

int Scenario_lockOrderInverted_A::do_run()
{
    // ***** Step 1

    // Attempt to acquire the lock on the 1st mutex with a timeout
    bool lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInverted_1, g_mutex_lockOrderInverted_1_name);

    // Use the lock on the 1st mutex if acquired
    if (lockAcquired) 
    {
        // Perform operations with the lock on the 1st mutex 
        long_loop();
    }
    else
    {
        return SCENARIO_RUN_ABORT;
    }

    // ***** Step 2

    // Attempt to acquire the lock on the 2nd mutex with a timeout
    lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInverted_2, g_mutex_lockOrderInverted_2_name);

    // Use the lock if acquired
    if (lockAcquired) 
    {
        // Release the lock on the 1st mutex
        unlock(g_mutex_lockOrderInverted_1, g_mutex_lockOrderInverted_1_name);

        // Perform operations with the lock on the 2nd mutex 
        short_loop();
        
        // Release the lock on the 2nd mutex 
        unlock(g_mutex_lockOrderInverted_2, g_mutex_lockOrderInverted_2_name);
    }
    else
    {
        // Release the lock on the 1st mutex
        unlock(g_mutex_lockOrderInverted_1, g_mutex_lockOrderInverted_1_name);

        return SCENARIO_RUN_ABORT;
    }

    return SCENARIO_RUN_SUCCESS;
}

Scenario_lockOrderInverted_B::Scenario_lockOrderInverted_B()
{
    id = "lockOrderInverted_B";
}

Scenario_lockOrderInverted_B::~Scenario_lockOrderInverted_B()
{
}

int Scenario_lockOrderInverted_B::do_run()
{
    // ***** Step 1

    // Attempt to acquire the lock on the 2nd mutex with a timeout
    bool lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInverted_2, g_mutex_lockOrderInverted_2_name);

    // Use the lock on the 2nd mutex if acquired
    if (lockAcquired) 
    {
        // Perform operations with the lock on the 2nd mutex
        short_loop();        
    }
    else
    {
        return SCENARIO_RUN_ABORT;
    }

    // ***** Step 2

    // Attempt to acquire the lock on the 1st mutex with a timeout
    lockAcquired = try_lock_with_timeout(g_mutex_lockOrderInverted_1, g_mutex_lockOrderInverted_1_name);

    // Use the lock on the 1st mutex if acquired
    if (lockAcquired) 
    {
        // Release the lock on the 2nd mutex
        unlock(g_mutex_lockOrderInverted_2, g_mutex_lockOrderInverted_2_name);

        // Perform operations with the lock on the 1st mutex
        long_loop();
        
        // Release the lock on the 1st mutex
        unlock(g_mutex_lockOrderInverted_1, g_mutex_lockOrderInverted_1_name);
    }
    else
    {
        // Release the lock on the 2nd mutex
        unlock(g_mutex_lockOrderInverted_2, g_mutex_lockOrderInverted_2_name);

        return SCENARIO_RUN_ABORT;
    }

    return SCENARIO_RUN_SUCCESS;
}
