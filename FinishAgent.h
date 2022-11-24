#pragma once

#include <iostream>
#include <mutex>
#include "SyncAgent.h"
#include "ThreadMap.h"
#include "Competitor.h"
#include "Results.h"

class FinishAgent : public SyncAgent {
private:
    Results r;
    ThreadMap& tMap;
    std::mutex finish_mutex;  // mutex for synchronising threads on finish
public:
    FinishAgent (ThreadMap& t);
    void proceed();
    void pause();
    Results returnResults();
    void setThreadMap(ThreadMap& t);
};