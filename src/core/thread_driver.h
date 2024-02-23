#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "thread_wrapper.h"
#include <vector>

class EventLogger;

class ThreadDriver
{
public:
    ThreadDriver();
    ~ThreadDriver();

    void set_event_logger(EventLogger *pEventLogger);
    bool init(size_t num_threads);
    ThreadWrapper* get_thread_wrapper(size_t index);
    void run();

private:
    EventLogger *m_pEventLogger;
    std::vector<ThreadWrapper> threads;
};

#endif
