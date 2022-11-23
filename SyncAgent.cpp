#include "RaceBasics.h"

class SyncAgent { //abstract base class
public:
   SyncAgent() : readyCount(0) {} //constructor
   // Declare virtual methods to be overridden by derived classes
   virtual void pause() = 0;
   virtual void proceed() = 0;
   bool readyToStart() {
   if (readyCount == NO_MEMBERS)
      return true;
   else
      return false;
    }
protected:
    int readyCount;
}; //end abstract class SyncAgent
