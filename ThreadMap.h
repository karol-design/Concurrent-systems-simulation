/**
 * @file    ThreadMap.h
 * @brief   ThreadMap class for managing threads in the program
 * @author  Karol Wojslaw (10746230)
 */

#pragma once

#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

#include "Competitor.h"

class ThreadMap {
   private:
    std::map<std::thread::id, Competitor> threadComp;           // map of thread ids with Competitor objects
    std::map<std::thread::id, Competitor>::iterator contentIt;  // iterator for the map
    std::mutex thread_mu;                                       // mutex for inserting a new thread - competitor pair

   public:
    ThreadMap();
    void insertThreadPair(Competitor c);
    void printMapContents();
    void initContentIt();
    int ThreadMapSize();
    Competitor getCompetitor();
    Competitor getNextMappedVal();
};
