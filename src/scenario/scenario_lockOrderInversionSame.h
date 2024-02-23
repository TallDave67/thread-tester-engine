#ifndef _SCENARIO_LOCK_ORDER_INVERSION_SAME_H_
#define _SCENARIO_LOCK_ORDER_INVERSION_SAME_H_

#include "scenario.h"

static const int SCENARIO_LOCK_ORDER_INVERSION_SAME_THREAD_A = 0;
static const int SCENARIO_LOCK_ORDER_INVERSION_SAME_THREAD_B = 1;
static const int SCENARIO_LOCK_ORDER_INVERSION_SAME_THREAD_COUNT = 2;

class Scenario_lockOrderInversionSame_A : public Scenario
{
public:
    Scenario_lockOrderInversionSame_A();
    ~Scenario_lockOrderInversionSame_A();

protected:
    int do_run() override;
};

class Scenario_lockOrderInversionSame_B : public Scenario
{
public:
    Scenario_lockOrderInversionSame_B();
    ~Scenario_lockOrderInversionSame_B();

protected:
    int do_run() override;
};

#endif