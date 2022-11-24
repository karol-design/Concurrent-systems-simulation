#include "EZAgent.h"

EZAgent::EZAgent() {} //constructor

void EZAgent::pause() {
    std::unique_lock<std::mutex> lk (EZ_mutex);
    cv.wait(lk);
}

void EZAgent::proceed() {
    std::unique_lock<std::mutex> lk (EZ_mutex);
    cv.notify_all();
}
