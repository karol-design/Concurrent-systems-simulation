#include "ThreadMap.h"
using namespace std;

ThreadMap::ThreadMap() {};

void ThreadMap::insertThreadPair(Competitor c) {
    std::lock_guard<std::mutex> guard (mu);
    // create a threadID, Competitor pair using a call to make_pair
    pair <thread::id, Competitor> p = make_pair(this_thread::get_id(), c);
    // store the pair in the map using the map insert member function
    threadComp.insert(p);
}   // mu mutex is automatically released when the lock_guard object goes out of scope

Competitor ThreadMap::getThreadId() {
	map <thread::id, Competitor>::iterator it = threadComp.find(this_thread::get_id());
	if (it == threadComp.end())
		return Competitor::makeNull();						//	alternatively	return *(new Competitor(" ", " "));
	else
		return it->second;									// i.e. the second item in the pair
}

void ThreadMap::printMapContents() {
    cout << endl << endl;
	cout << "MAP CONTENTS:" << endl;
	map <thread::id, Competitor>::iterator it = threadComp.begin();
	for( it = threadComp.begin(); it != threadComp.end(); it++ ) {
        cout << "Thread ID = " << (it->first) << "\t";
        (it->second).printCompetitor();
	}
	cout << "END MAP CONTENTS" << endl;
}

int ThreadMap::ThreadMapSize() { return threadComp.size(); }
