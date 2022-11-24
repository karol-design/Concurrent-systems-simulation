#include <iostream>
#include <thread>

#include "StartAgent.h"

StartAgent::StartAgent() {} //constructor

void StartAgent::pause() {
    std::unique_lock<std::mutex> lk (start_mu);
    readyCount++;
    cv.wait(lk);
}

void StartAgent::proceed() {
    // insert code to implement releasing of all athlete threads
    std::unique_lock<std::mutex> lk (start_mu);
    cv.notify_all();
}
