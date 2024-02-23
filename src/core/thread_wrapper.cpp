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
    : m_pEventLogger(nullptr), m_pScenario(nullptr), wrapper_id(0), thread_ptr(nullptr), termination_state(SCENARIO_RUN_NOOP)
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
    if(thread_ptr)
    {
        // log the event ?
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "thread_wrapper " << get_wrapper_id() << " has an std::thread to destroy";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        // if(thread_ptr->joinable())
        // {
        //     // log the event ?
        //     if(m_pEventLogger)
        //     {
        //         std::stringstream ss;
        //         ss << "thread_wrapper " << get_wrapper_id() << " has an std::thread that is joinable, so we must join it before destruction";
        //         std::string event = ss.str();
        //         m_pEventLogger->send_event(event);
        //     }

        //     thread_ptr->join();
        // }
    }
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

int ThreadWrapper::get_termination_state()
{
    return termination_state;
}

long long ThreadWrapper::duration_in_microseconds()
{
    return timer.duration_in_microseconds();
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
    timer.start();

    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "thread_wrapper " << get_wrapper_id() << " with id = " << std::this_thread::get_id() << " is running";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);

    }

    termination_state = run_scenario();

    timer.stop();

    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "thread_wrapper " << get_wrapper_id() << " with id = " << std::this_thread::get_id() << " took " << timer.duration_in_microseconds() << " microseconds to run";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);

    }

    return termination_state;
}

int ThreadWrapper::run_scenario()
{
    if(m_pScenario)
    {
        return m_pScenario->run();
    }
    else
    {
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "thread_wrapper " << get_wrapper_id() << " with id = " << std::this_thread::get_id() << " has no scenario to run";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }

        return SCENARIO_RUN_NOOP;
    }
}