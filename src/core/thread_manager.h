#ifndef _THREAD_MANAGER_H_
#define _THREAD_MANAGER_H_

#include "thread_driver.h"

class EventLogger;

class ThreadManager
{
public:
    ThreadManager();

    void set_event_logger(EventLogger *pEventLogger);

    // Tests
    bool isTestRunning();
    void runTest_lockOrderSame();
    void runTest_lockOrderInverted();

private:
    ThreadDriver thread_driver;
    EventLogger *m_pEventLogger;
};

#endif