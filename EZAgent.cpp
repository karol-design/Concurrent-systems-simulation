/**
 * @file    EZAgent.cpp
 * @brief   Exchange zone synchronisation agent class
 * @author  Karol Wojslaw (10746230)
 */

#include "EZAgent.h"

/**
 * @brief Constructor
 */
EZAgent::EZAgent() {}

/**
 * @brief Pause the calling thread (to be called by thread i)
 */
void EZAgent::pause() {
    std::unique_lock<std::mutex> lk(EZ_mutex);  // Guard the CS with a mutex lock
    cv.wait(lk);                                // Use condition variable to block thread i
}

/**
 * @brief Unblock all threads blocked in the cv Condition Variable (to be called by thread i-1)
 */
void EZAgent::proceed() {
    std::unique_lock<std::mutex> lk(EZ_mutex);  // Guard the CS with a mutex lock
    cv.notify_all();                            // Use condition variable to unblock thread i
}
