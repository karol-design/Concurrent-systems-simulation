/**
 * @file    ThreadMap.h
 * @brief   ThreadMap class for managing threads in the program
 * @author  Karol Wojslaw (10746230)
 */

#include "ThreadMap.h"
using namespace std;

ThreadMap::ThreadMap(){};

void ThreadMap::insertThreadPair(Competitor c) {
    std::lock_guard<std::mutex> guard(thread_mu);
    // create a threadID, Competitor pair using a call to make_pair
    pair<thread::id, Competitor> p = make_pair(this_thread::get_id(), c);
    threadComp.insert(p);  // store the pair in the map using the map insert member function
}  // thread_mu mutex is automatically released when the lock_guard object goes out of scope

Competitor ThreadMap::getThreadId() {
    // Use an iterator and find method to look for an ID
    map<thread::id, Competitor>::iterator it = threadComp.find(this_thread::get_id());
    if (it == threadComp.end()) {
        return Competitor::makeNull();  // Return a null object
    } else {
        return it->second;  // Return mapped competitor object (the 2nd item in the pair)
    }
}

void ThreadMap::printMapContents() {
    cout << endl;
    cout << "Map contents:" << endl;
    // Use an iterator to print all elements in the map
    map<thread::id, Competitor>::iterator it = threadComp.begin();
    for (it = threadComp.begin(); it != threadComp.end(); it++) {
        cout << "Thread ID = " << (it->first) << "\t";
        (it->second).printCompetitor();
    }
    cout << "End map contents" << endl;
}

int ThreadMap::ThreadMapSize() { return threadComp.size(); }
