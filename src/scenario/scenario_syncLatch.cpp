#include "scenario_syncLatch.h"
#include "event_logger.h"
#include <latch>
#include <sstream>

std::latch g_sync_latch_step1_done{SCENARIO_SYNC_LATCH_THREAD_COUNT};
std::latch g_sync_latch_step2_done{SCENARIO_SYNC_LATCH_THREAD_COUNT};

const char* g_sync_latch_step1_done_name = "latch1";
const char* g_sync_latch_step2_done_name = "latch2";

Scenario_syncLatch_A::Scenario_syncLatch_A()
{
    id = "syncLatch_A";
}

Scenario_syncLatch_A::~Scenario_syncLatch_A()
{

}

int Scenario_syncLatch_A::do_run()
{
     // ***** Step 1

    // Perform operations
    long_loop();

    // Wait for others
    arrive_and_wait(g_sync_latch_step1_done, g_sync_latch_step1_done_name);
 
    // ***** Step 2

    // Perform operations
    short_loop();

    // Wait for others
    arrive_and_wait(g_sync_latch_step2_done, g_sync_latch_step2_done_name);

    return SCENARIO_RUN_SUCCESS;
}

Scenario_syncLatch_B::Scenario_syncLatch_B()
{
    id = "syncLatch_B";
}

Scenario_syncLatch_B::~Scenario_syncLatch_B()
{
}

int Scenario_syncLatch_B::do_run()
{
     // ***** Step 1

    // Perform operations
    long_loop();

    // Wait for others
    arrive_and_wait(g_sync_latch_step1_done, g_sync_latch_step1_done_name);
 
    // ***** Step 2

    // Perform operations
    short_loop();

    // Wait for others
    arrive_and_wait(g_sync_latch_step2_done, g_sync_latch_step2_done_name);

    return SCENARIO_RUN_SUCCESS;
}

Scenario_syncLatch_C::Scenario_syncLatch_C()
{
    id = "syncLatch_C";
}

Scenario_syncLatch_C::~Scenario_syncLatch_C()
{
}

int Scenario_syncLatch_C::do_run()
{
     // ***** Step 1

    // Perform operations
    long_loop();

    // Wait for others
    arrive_and_wait(g_sync_latch_step1_done, g_sync_latch_step1_done_name);
 
    // ***** Step 2

    // Perform operations
    short_loop();

    // Wait for others
    arrive_and_wait(g_sync_latch_step2_done, g_sync_latch_step2_done_name);

    return SCENARIO_RUN_SUCCESS;
}
