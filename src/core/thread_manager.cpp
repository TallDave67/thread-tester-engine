#include "thread_manager.h"
#include "event_logger.h"
#include "scenario.h"
#include "scenario_lockOrderInversionSame.h"
#include "scenario_lockOrderInversionInverted.h"

ThreadManager::ThreadManager()
    : m_pEventLogger(nullptr)
{
}

void ThreadManager::set_event_logger(EventLogger *pEventLogger)
{
    m_pEventLogger = pEventLogger;
    thread_driver.set_event_logger(m_pEventLogger);
}

// Tests
bool ThreadManager::isTestRunning()
{
    return false;
}

void ThreadManager::runTest_lockOrderInversionSame()
{
    if(m_pEventLogger)
    {
        std::string event;
        event = "ThreadManager::runTest_lockOrderInversionSame() running";
        m_pEventLogger->send_event(event);
    }

    thread_driver.init(SCENARIO_LOCK_ORDER_INVERSION_SAME_THREAD_COUNT);
    //
    Scenario_lockOrderInversionSame_A scenarioA;
    scenarioA.set_event_logger(m_pEventLogger);
    thread_driver.get_thread_wrapper(SCENARIO_LOCK_ORDER_INVERSION_SAME_THREAD_A)->set_scenario(&scenarioA);
    //
    Scenario_lockOrderInversionSame_B scenarioB;
    scenarioB.set_event_logger(m_pEventLogger);
    thread_driver.get_thread_wrapper(SCENARIO_LOCK_ORDER_INVERSION_SAME_THREAD_B)->set_scenario(&scenarioB);
    //
    thread_driver.run();
}

void ThreadManager::runTest_lockOrderInversionInverted()
{
    if(m_pEventLogger)
    {
        std::string event;
        event = "ThreadManager::runTest_lockOrderInversionInverted() running";
        m_pEventLogger->send_event(event);
    }

    thread_driver.init(SCENARIO_LOCK_ORDER_INVERSION_INVERTED_THREAD_COUNT);
    //
    Scenario_lockOrderInversionInverted_A scenarioA;
    scenarioA.set_event_logger(m_pEventLogger);
    thread_driver.get_thread_wrapper(SCENARIO_LOCK_ORDER_INVERSION_INVERTED_THREAD_A)->set_scenario(&scenarioA);
    //
    Scenario_lockOrderInversionInverted_B scenarioB;
    scenarioB.set_event_logger(m_pEventLogger);
    thread_driver.get_thread_wrapper(SCENARIO_LOCK_ORDER_INVERSION_INVERTED_THREAD_B)->set_scenario(&scenarioB);
    //
    thread_driver.run();
}
