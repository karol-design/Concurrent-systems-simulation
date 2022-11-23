#include "RaceCommon.h"
#include "SyncAgent.h"


SyncAgent::SyncAgent() : readyCount(0) {} //constructor
SyncAgent::~SyncAgent() {}

// Declare virtual methods to be overridden by derived classes

bool SyncAgent::readyToStart() {
   if (readyCount == NO_MEMBERS)
      return true;
   else
      return false;
}
