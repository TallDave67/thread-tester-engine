#ifndef _THREAD_H_
#define _THREAD_H_

#include "constants.h"
#include <functional>
#include <thread>
#include <memory>

class EventLogger;
class Scenario;

class ThreadWrapper
{
private:
    static int max_wrapper_id;

public:
    static int get_max_wrapper_id();

public:
    ThreadWrapper();
    ~ThreadWrapper();

    //delete the copy constructor and copy assignment operator
    ThreadWrapper(const ThreadWrapper&) = delete;
    ThreadWrapper& operator=(const ThreadWrapper&) = delete;

    //create defauls of the move constructor and move assignment operator
    ThreadWrapper(ThreadWrapper&&) noexcept = default;
    ThreadWrapper& operator=(ThreadWrapper&&) noexcept = default;

    void set_event_logger(EventLogger *pEventLogger);
    void set_scenario(Scenario *pScenario);

    bool run();
    void wait();

    int get_finish_state();
    std::string get_finish_state_as_string();

    int get_wrapper_id();
    std::thread::id get_id();
    std::thread::native_handle_type get_native_handle();

private:
    int do_run();
    int run_scenario();

private:
    EventLogger *m_pEventLogger;
    Scenario *m_pScenario;
    //
    int wrapper_id;
    std::function<int()> thread_ftn;
    std::unique_ptr<std::thread> thread_ptr;
    int finish_state;
    std::string finish_state_as_string;
};

#endif
