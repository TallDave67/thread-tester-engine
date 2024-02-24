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
    }

    for(auto & t : threads)
    {
        t.wait();

        // log the event ?
        if(m_pEventLogger)
        {
            std::stringstream ss;
            ss << "{\"event\":\"thread terminated\", \"thread_wrapper\":" << t.get_wrapper_id() << ", \"termination_state\":\"" << t.get_termination_state_as_string() << "\"}";        
            std::string event = ss.str();
            m_pEventLogger->send_event(event);
        }
    }

}
