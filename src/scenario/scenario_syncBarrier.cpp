#include "scenario_syncBarrier.h"
#include "event_logger.h"
#include <barrier>
#include <string>
#include <sstream>

const char* g_sync_barrier_name = "barrier";
const char* g_sync_barrier_name_reused = "barrier_reused";
std::string g_sync_barrier_name_1 = g_sync_barrier_name;

auto sync_barrier_on_completion = []() noexcept
{
    g_sync_barrier_name_1 = g_sync_barrier_name_reused;
};

std::barrier<void(*)(void) noexcept> g_sync_barrier(SCENARIO_SYNC_BARRIER_THREAD_COUNT, sync_barrier_on_completion);

Scenario_syncBarrier_A::Scenario_syncBarrier_A()
{
    id = "syncBarrier_A";
}

Scenario_syncBarrier_A::~Scenario_syncBarrier_A()
{

}

int Scenario_syncBarrier_A::do_run()
{
    // ***** Step 1

    // Perform operations
    long_loop();

    // Wait for others
    arrive_and_wait(g_sync_barrier, g_sync_barrier_name_1.c_str());
 
    // ***** Step 2

    // Perform operations
    short_loop();

    // Wait for others
    arrive_and_wait(g_sync_barrier, g_sync_barrier_name_1.c_str());

    return SCENARIO_RUN_SUCCESS;
}

Scenario_syncBarrier_B::Scenario_syncBarrier_B()
{
    id = "syncBarrier_B";
}

Scenario_syncBarrier_B::~Scenario_syncBarrier_B()
{
}

int Scenario_syncBarrier_B::do_run()
{
    // ***** Step 1

    // Perform operations
    long_loop();

    // Wait for others
    arrive_and_wait(g_sync_barrier, g_sync_barrier_name_1.c_str());
 
    // ***** Step 2

    // Perform operations
    short_loop();

    // Wait for others
    arrive_and_wait(g_sync_barrier, g_sync_barrier_name_1.c_str());

    return SCENARIO_RUN_SUCCESS;
}

Scenario_syncBarrier_C::Scenario_syncBarrier_C()
{
    id = "syncBarrier_C";
}

Scenario_syncBarrier_C::~Scenario_syncBarrier_C()
{
}

int Scenario_syncBarrier_C::do_run()
{
    // ***** Step 1

    // Perform operations
    long_loop();

    // Wait for others
    arrive_and_wait(g_sync_barrier, g_sync_barrier_name_1.c_str());
 
    // ***** Step 2

    // Perform operations
    short_loop();

    // Wait for others
    arrive_and_wait(g_sync_barrier, g_sync_barrier_name_1.c_str());

    return SCENARIO_RUN_SUCCESS;
}
