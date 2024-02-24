#ifndef _SCENARIO_LOCK_ORDER_SAME_H_
#define _SCENARIO_LOCK_ORDER_SAME_H_

#include "scenario.h"

static const int SCENARIO_LOCK_ORDER_SAME_THREAD_A = 0;
static const int SCENARIO_LOCK_ORDER_SAME_THREAD_B = 1;
static const int SCENARIO_LOCK_ORDER_SAME_THREAD_COUNT = 2;

class Scenario_lockOrderSame_A : public Scenario
{
public:
    Scenario_lockOrderSame_A();
    ~Scenario_lockOrderSame_A();

protected:
    int do_run() override;
};

class Scenario_lockOrderSame_B : public Scenario
{
public:
    Scenario_lockOrderSame_B();
    ~Scenario_lockOrderSame_B();

protected:
    int do_run() override;
};

#endif