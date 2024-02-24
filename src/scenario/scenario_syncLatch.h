#ifndef _SCENARIO_SYNC_LATCH_H_
#define _SCENARIO_SYNC_LATCH_H_

#include "scenario.h"

static const int SCENARIO_SYNC_LATCH_THREAD_A = 0;
static const int SCENARIO_SYNC_LATCH_THREAD_B = 1;
static const int SCENARIO_SYNC_LATCH_THREAD_C = 2;
static const int SCENARIO_SYNC_LATCH_THREAD_COUNT = 3;

class Scenario_syncLatch_A : public Scenario
{
public:
    Scenario_syncLatch_A();
    ~Scenario_syncLatch_A();

protected:
    int do_run() override;
};

class Scenario_syncLatch_B : public Scenario
{
public:
    Scenario_syncLatch_B();
    ~Scenario_syncLatch_B();

protected:
    int do_run() override;
};

class Scenario_syncLatch_C : public Scenario
{
public:
    Scenario_syncLatch_C();
    ~Scenario_syncLatch_C();

protected:
    int do_run() override;
};

#endif