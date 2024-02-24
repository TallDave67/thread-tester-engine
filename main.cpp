// main.cpp
#include <iostream>
#include <cstdlib>
#include <string>
#include "thread_manager.h"
#include "event_logger.h"
#include "test_ids.h"
 
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <test_id>" << std::endl;
        return 1;
    }

    // Our test runner
    ThreadManager thread_mgr;
    EventLogger event_logger;
    thread_mgr.set_event_logger(&event_logger);

    // Convert the test_id argument to an integer
    int test_id = std::stoi(argv[1]);

    // Launch the corresponding test program based on the test_id
    switch (test_id) {
        case TEST_LOCK_ORDER_SAME:
            thread_mgr.runTest_lockOrderSame();
            break;
        case TEST_LOCK_ORDER_INVERTED:
            thread_mgr.runTest_lockOrderInverted();
            break;
        case TEST_SYNC_LATCH:
            thread_mgr.runTest_syncLatch();
            break;
        case TEST_SYNC_BARRIER:
            thread_mgr.runTest_syncBarrier();
            break;
        // Add more cases for additional test programs

        default:
            std::cerr << "Invalid test_id. Please provide a valid test_id." << std::endl;
            return 1;
    }
   
    return 0;
}
