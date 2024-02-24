#ifndef _SCENARIO_LOCK_ORDER_INVERTED_H_
#define _SCENARIO_LOCK_ORDER_INVERTED_H_

#include "scenario.h"

static const int SCENARIO_LOCK_ORDER_INVERTED_THREAD_A = 0;
static const int SCENARIO_LOCK_ORDER_INVERTED_THREAD_B = 1;
static const int SCENARIO_LOCK_ORDER_INVERTED_THREAD_COUNT = 2;

class Scenario_lockOrderInverted_A : public Scenario
{
public:
    Scenario_lockOrderInverted_A();
    ~Scenario_lockOrderInverted_A();

protected:
    int do_run() override;
};

class Scenario_lockOrderInverted_B : public Scenario
{
public:
    Scenario_lockOrderInverted_B();
    ~Scenario_lockOrderInverted_B();

protected:
    int do_run() override;
};

#endif