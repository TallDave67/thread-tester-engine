#include "thread_manager.h"
#include "event_logger.h"
#include "scenario.h"
#include "scenario_lockOrderSame.h"
#include "scenario_lockOrderInverted.h"

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

void ThreadManager::runTest_lockOrderSame()
{
    if(m_pEventLogger)
    {
        std::string event;
        event = "{\"event\":\"running\", \"test\":\"lockOrderSame\"}";
        m_pEventLogger->send_event(event);
    }

    thread_driver.init(SCENARIO_LOCK_ORDER_SAME_THREAD_COUNT);
    //
    Scenario_lockOrderSame_A scenarioA;
    scenarioA.set_event_logger(m_pEventLogger);
    thread_driver.get_thread_wrapper(SCENARIO_LOCK_ORDER_SAME_THREAD_A)->set_scenario(&scenarioA);
    //
    Scenario_lockOrderSame_B scenarioB;
    scenarioB.set_event_logger(m_pEventLogger);
    thread_driver.get_thread_wrapper(SCENARIO_LOCK_ORDER_SAME_THREAD_B)->set_scenario(&scenarioB);
    //
    thread_driver.run();
}

void ThreadManager::runTest_lockOrderInverted()
{
    if(m_pEventLogger)
    {
        std::string event;
        event = "{\"event\":\"running\", \"test\":\"lockOrderInverted\"}";
        m_pEventLogger->send_event(event);
    }

    thread_driver.init(SCENARIO_LOCK_ORDER_INVERTED_THREAD_COUNT);
    //
    Scenario_lockOrderInverted_A scenarioA;
    scenarioA.set_event_logger(m_pEventLogger);
    thread_driver.get_thread_wrapper(SCENARIO_LOCK_ORDER_INVERTED_THREAD_A)->set_scenario(&scenarioA);
    //
    Scenario_lockOrderInverted_B scenarioB;
    scenarioB.set_event_logger(m_pEventLogger);
    thread_driver.get_thread_wrapper(SCENARIO_LOCK_ORDER_INVERTED_THREAD_B)->set_scenario(&scenarioB);
    //
    thread_driver.run();
}
