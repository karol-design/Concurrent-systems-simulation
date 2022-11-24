#pragma once

#include <mutex>
#include <condition_variable>

#include "SyncAgent.h"

class EZAgent : public SyncAgent { //concrete class that CAN be instantiated
public:
   EZAgent(); //constructor
   void pause();
   void proceed();
private:
    std::mutex EZ_mutex;  // mutex for synchronising threads on start
    std::condition_variable cv; // condition variable for synchronising threads on start
   // insert any necessary data members including variables, mutexes, locks, cond vars
}; //end class EZAgent
