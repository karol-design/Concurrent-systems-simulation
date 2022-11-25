/**
 * @file    StartAgent.h
 * @brief   Start zone synchronisation agent class
 * @author  Karol Wojslaw (10746230)
 */

#pragma once

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include "SyncAgent.h"

class StartAgent : public SyncAgent {
   private:
    std::mutex start_mu;         // mutex for synchronising threads on start
    std::condition_variable cv;  // condition variable for synchronising threads on start

   public:
    StartAgent();
    void pause();
    void proceed();
};
