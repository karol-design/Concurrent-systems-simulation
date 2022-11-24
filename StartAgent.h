#pragma once

#include <mutex>
#include <condition_variable>

#include "SyncAgent.h"

class StartAgent : public SyncAgent { //concrete class that CAN be instantiated
public:
   StartAgent(); //constructor
   void pause();
   void proceed();
private:
    std::mutex start_mu;  // mutex for synchronising threads on start
    std::condition_variable cv; // condition variable for synchronising threads on start

   // insert necessary data members including variables, mutexes, locks, cond vars
}; //end class StartAgent
