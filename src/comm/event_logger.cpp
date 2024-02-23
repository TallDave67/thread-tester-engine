#include "event_logger.h"
#include <iostream>
#include <mutex>

std::mutex g_mutex_send;

EventLogger::EventLogger()
{
}
    
void EventLogger::send_event(std::string & event)
{
    // Acquire the lock on the send mutex using std::lock_guard
    std::lock_guard<std::mutex> lock(g_mutex_send);    
    
    std::cout << event << std::endl;
}

