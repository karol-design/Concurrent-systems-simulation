/**
 * @file    ThreadMap.h
 * @brief   ThreadMap class for managing threads in the program
 * @author  Karol Wojslaw (10746230)
 */

#include "ThreadMap.h"

ThreadMap::ThreadMap(){};

/**
 * @brief Insert a pair of Thread ID and Competitor object into the map (thread-safe)
 * @param Competitor object represented by a calling thread
 */
void ThreadMap::insertThreadPair(Competitor c) {
    std::lock_guard<std::mutex> guard(thread_mu);
    // create a threadID, Competitor pair using a call to make_pair
    std::pair<std::thread::id, Competitor> p = make_pair(std::this_thread::get_id(), c);
    threadComp.insert(p);  // store the pair in the map using the map insert member function
}  // guard goes out of scope, thread_mu mutex is released

/**
 * @brief Get a competitor represented by a calling thread
 * @return Competitor object represented by a calling thread
 */
Competitor ThreadMap::getCompetitor() {
    // Use an iterator and find method to look for an ID
    std::map<std::thread::id, Competitor>::iterator it = threadComp.find(std::this_thread::get_id());
    if (it == threadComp.end()) {
        return Competitor::makeNull();  // Return a null object
    } else {
        return it->second;  // Return mapped competitor object (the 2nd item in the pair)
    }
}

/**
 * @brief Print all competitors in the map and associated threads
 */
void ThreadMap::printMapContents() {
    std::cout << std::endl;
    std::cout << "Map contents:" << std::endl;
    // Use an iterator to print all elements in the map
    std::map<std::thread::id, Competitor>::iterator it = threadComp.begin();
    for (it = threadComp.begin(); it != threadComp.end(); it++) {
        std::cout << "Thread ID: " << (it->first) << "\t";
        (it->second).printCompetitor();
    }
    std::cout << "End map contents" << std::endl;
}

/**
 * @brief Place content iterator at the beginning of the map
 */
void ThreadMap::initContentIt(){
    contentIt = threadComp.begin();
}

/**
 * @brief Find a competitor object and increment the iterator
 * @return Competitor object at the position pointed by the iterator
 */
Competitor ThreadMap::getNextMappedVal() {
	Competitor c;
	if (contentIt != threadComp.end())
		c = contentIt->second;
	else
		c = contentIt->second.makeNull();
	contentIt++;
	return c;
}

/**
 * @brief Get thread map size
 * @return Number of elements in the map
 */
int ThreadMap::ThreadMapSize() { return threadComp.size(); }
