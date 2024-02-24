#ifndef _SCENARIO_SYNC_BARRIER_H_
#define _SCENARIO_SYNC_BARRIER_H_

#include "scenario.h"

static const int SCENARIO_SYNC_BARRIER_THREAD_A = 0;
static const int SCENARIO_SYNC_BARRIER_THREAD_B = 1;
static const int SCENARIO_SYNC_BARRIER_THREAD_C = 2;
static const int SCENARIO_SYNC_BARRIER_THREAD_COUNT = 3;

class Scenario_syncBarrier_A : public Scenario
{
public:
    Scenario_syncBarrier_A();
    ~Scenario_syncBarrier_A();

protected:
    int do_run() override;
};

class Scenario_syncBarrier_B : public Scenario
{
public:
    Scenario_syncBarrier_B();
    ~Scenario_syncBarrier_B();

protected:
    int do_run() override;
};

class Scenario_syncBarrier_C : public Scenario
{
public:
    Scenario_syncBarrier_C();
    ~Scenario_syncBarrier_C();

protected:
    int do_run() override;
};

#endif