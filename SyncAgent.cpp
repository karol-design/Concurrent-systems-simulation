/**
 * @file    SyncAgent.cpp
 * @brief   Synchronisation agent abstract class
 * @author  Karol Wojslaw (10746230)
 */

#include "SyncAgent.h"

/**
 * @brief Constructor. Set readyCount to 0
 */
SyncAgent::SyncAgent() : readyCount(0) {}

/**
 * @brief Check if all threads has been blocked and hence synchronised
 * @return Boolean flag true if all threads has been bloceked
 */
bool SyncAgent::readyToStart() {
    if (readyCount == (NO_MEMBERS)) {
        return true;
    } else {
        return false;
    }
}
