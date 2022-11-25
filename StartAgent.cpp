/**
 * @file    StartAgent.h
 * @brief   Start zone synchronisation agent class
 * @author  Karol Wojslaw (10746230)
 */

#include "StartAgent.h"

/**
 * @brief Constructor
 */
StartAgent::StartAgent() {}

/**
 * @brief Increment the readyCount and pause the calling thread
 */
void StartAgent::pause() {
    std::unique_lock<std::mutex> lk(start_mu);  // Guard the CS with a mutex lock
    readyCount++;
    cv.wait(lk);
}

/**
 * @brief Unblock all threads blocked in the cv Condition Variable (to be called by main)
 */
void StartAgent::proceed() {
    std::unique_lock<std::mutex> lk(start_mu);
    cv.notify_all();
}
