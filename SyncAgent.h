/**
 * @file    SyncAgent.h
 * @brief   Synchronisation agent abstract class
 * @author  Karol Wojslaw (10746230)
 */

#pragma once

#include "RaceCommon.h"

class SyncAgent {
   protected:
    int readyCount;

   public:
    SyncAgent();
    virtual void pause() = 0;    // virtual pause method to be overridden by derived classes
    virtual void proceed() = 0;  // virtual proceed method to be overridden by derived classes
    bool readyToStart();
};
