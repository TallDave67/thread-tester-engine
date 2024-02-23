#ifndef _SCENARIO_LOCK_ORDER_INVERSION_INVERTED_H_
#define _SCENARIO_LOCK_ORDER_INVERSION_INVERTED_H_

#include "scenario.h"

static const int SCENARIO_LOCK_ORDER_INVERSION_INVERTED_THREAD_A = 0;
static const int SCENARIO_LOCK_ORDER_INVERSION_INVERTED_THREAD_B = 1;
static const int SCENARIO_LOCK_ORDER_INVERSION_INVERTED_THREAD_COUNT = 2;

class Scenario_lockOrderInversionInverted_A : public Scenario
{
public:
    Scenario_lockOrderInversionInverted_A();
    ~Scenario_lockOrderInversionInverted_A();

protected:
    int do_run() override;
};

class Scenario_lockOrderInversionInverted_B : public Scenario
{
public:
    Scenario_lockOrderInversionInverted_B();
    ~Scenario_lockOrderInversionInverted_B();

protected:
    int do_run() override;
};

#endif