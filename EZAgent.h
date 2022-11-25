/**
 * @file    EZAgent.h
 * @brief   Exchange zone synchronisation agent class
 * @author  Karol Wojslaw (10746230)
 */

#pragma once

#include <condition_variable>
#include <mutex>

#include "SyncAgent.h"

class EZAgent : public SyncAgent {
   private:
    std::mutex EZ_mutex;         // mutex for synchronising threads on start
    std::condition_variable cv;  // condition variable for synchronising threads on start

   public:
    EZAgent();
    void pause();
    void proceed();
};
