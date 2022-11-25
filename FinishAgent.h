/**
 * @file    FinishAgent.h
 * @brief   Finish zone synchronisation agent class
 * @author  Karol Wojslaw (10746230)
 */

#pragma once

#include <iostream>
#include <mutex>

#include "Results.h"
#include "SyncAgent.h"
#include "ThreadMap.h"

class FinishAgent : public SyncAgent {
   private:
    Results r;
    ThreadMap& tMap;
    std::mutex finish_mutex;  // mutex for synchronising threads on finish
   public:
    FinishAgent(ThreadMap& t);

    void proceed();
    void pause();

    Results returnResults();
    void setThreadMap(ThreadMap& t);
};
