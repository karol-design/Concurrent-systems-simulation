/**
 * @file    FinishAgent.cpp
 * @brief   Finish zone synchronisation agent class
 * @author  Karol Wojslaw (10746230)
 */

#include "FinishAgent.h"

/**
 * @brief Constructor
 */
FinishAgent::FinishAgent(ThreadMap& t) : tMap(t) {}

/**
 * @brief Allocate Competitors to an appropriate position in the results
 */
void FinishAgent::proceed() {
    std::unique_lock<std::mutex> lk(finish_mutex);  // Guard the CS with a mutex lock
    r.setPosition(tMap.getCompetitor());
}
/**
 * @brief Not in use
 */
void FinishAgent::pause() {}

/**
 * @brief Get the results of the run
 * @return Results object
 */
Results FinishAgent::returnResults() { return r; }
