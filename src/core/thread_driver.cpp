#include "thread_driver.h"
#include "event_logger.h"
#include <sstream>

#include <chrono>
using namespace std::chrono_literals;

ThreadDriver::ThreadDriver()
    : m_pEventLogger(nullptr)
{
}

ThreadDriver::~ThreadDriver()
{
}

void ThreadDriver::set_event_logger(EventLogger *pEventLogger)
{
    m_pEventLogger = pEventLogger;
}

bool ThreadDriver::init(size_t num_threads)
{
    // create the thread wrappers
    for(int i = 0; i < num_threads; i++)
    {
        threads.push_back(ThreadWrapper());
        threads.back().set_event_logger(m_pEventLogger);
    }

    // log the event ?
    if(m_pEventLogger)
    {
        std::stringstream ss;
        ss << "create " << num_threads << " threads";
        std::string event = ss.str();
        m_pEventLogger->send_event(event);
    }

    return true;
}

ThreadWrapper* ThreadDriver::get_thread_wrapper(size_t index)
{
    ThreadWrapper *pThreadWrapper = nullptr;
    if(index < threads.size())
    {
        pThreadWrapper = &(threads[index]);
    }
    return pThreadWrapper;
}

void ThreadDriver::run()
{
    for(auto & t : threads)
    {
        t.run();

        // log the event ?
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "thread_wrapper " << t.get_wrapper_id() << " with id = " << t.get_id() << " is launched";
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }
    }

    for(auto & t : threads)
    {
        t.wait();

        // log the event ?
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "thread_wrapper " << t.get_wrapper_id() << " had a thread that terminated with state = " << t.get_termination_state();
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }
    }

}
