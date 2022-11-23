
// Note that there is some debate in the C++ world about whether a .cpp file is needed or appropriate for an abstract class
// - see https://stackoverflow.com/questions/14001356/do-i-need-to-have-a-cpp-file-for-an-abstract-class
// Here SyncAgent has a none virtual member function (readyToStart) so both a .h and .cpp file should be used

class SyncAgent { //abstract base class
public:
   SyncAgent(); //constructor
   // Declare virtual methods to be overridden by derived classes
   virtual void pause() = 0;
   virtual void proceed() = 0;
   bool readyToStart();
   ~SyncAgent();
protected:
    int readyCount;
}; //end abstract class SyncAgent
