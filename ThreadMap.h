#pragma once

#include <iostream>
#include <thread>
#include <map>
#include <string>
#include <mutex>
#include "Competitor.h"

class ThreadMap {
private:
    std::map <std::thread::id, Competitor> threadComp;  //map of thread ids v. Competitors
    std::mutex mu;

public:
    ThreadMap();
    void insertThreadPair(Competitor c);
    Competitor getThreadId();
    void printMapContents();
    int ThreadMapSize();
};
