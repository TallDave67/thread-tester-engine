#include "thread_wrapper.h"
#include "constants.h"
#include "event_logger.h"
#include "scenario.h"
#include <thread>
#include <functional>
#include <string>
#include <sstream>
#include <iostream>

int ThreadWrapper::max_wrapper_id = 0;
int ThreadWrapper::get_max_wrapper_id()
{
    return ThreadWrapper::max_wrapper_id;
}

ThreadWrapper::ThreadWrapper()
    : m_pEventLogger(nullptr), m_pScenario(nullptr), wrapper_id(0), thread_ptr(nullptr), finish_state(SCENARIO_RUN_NOOP)
{
    ThreadWrapper::max_wrapper_id++;
    if(ThreadWrapper::max_wrapper_id == MAX_THREADS)
    {
        ThreadWrapper::max_wrapper_id = 1;
    }
    wrapper_id = ThreadWrapper::max_wrapper_id;
}

ThreadWrapper::~ThreadWrapper()
{
}

void ThreadWrapper::set_event_logger(EventLogger *pEventLogger)
{
    m_pEventLogger = pEventLogger;
}

void ThreadWrapper::set_scenario(Scenario *pScenario)
{
    m_pScenario = pScenario;
}

bool ThreadWrapper::run()
{
    thread_ptr = std::make_unique<std::thread>(std::bind(&ThreadWrapper::do_run, std::ref(*this)));
    return thread_ptr ? true : false;
}

void ThreadWrapper::wait()
{
    if(thread_ptr) thread_ptr->join();
}

int ThreadWrapper::get_finish_state()
{
    return finish_state;
}

std::string ThreadWrapper::get_finish_state_as_string()
{
    switch(finish_state)
    {
        case SCENARIO_RUN_ABORT:
            finish_state_as_string = "ABORT";
            break;
        case SCENARIO_RUN_FAILURE:
            finish_state_as_string = "FAILURE";
            break;
        case SCENARIO_RUN_NOOP:
            finish_state_as_string = "NOOP";
            break;
        case SCENARIO_RUN_SUCCESS:
            finish_state_as_string = "SUCCESS";
            break;
    }
    return finish_state_as_string;
}

int ThreadWrapper::get_wrapper_id()
{
    return wrapper_id;
}

std::thread::id ThreadWrapper::get_id()
{
    std::thread::id tid;
    if(thread_ptr) tid = thread_ptr->get_id();
    return tid;
}

std::thread::native_handle_type ThreadWrapper::get_native_handle()
{
    std::thread::native_handle_type hid;
    if(thread_ptr) hid = thread_ptr->native_handle();
    return hid;
}

int ThreadWrapper::do_run()
{
    finish_state = run_scenario();

    return finish_state;
}

int ThreadWrapper::run_scenario()
{
    if(m_pScenario)
    {
        return m_pScenario->run();
    }
    else
    {
        return SCENARIO_RUN_NOOP;
    }
}