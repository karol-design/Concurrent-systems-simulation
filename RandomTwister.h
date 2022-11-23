#pragma once

#include <chrono>
#include <random>
#include <ctime>
#include <mutex>

using namespace std;

class RandomTwister {

private:
    std::mt19937 rnd; // rnd is an object of class mt19937
    std::mutex mu;

public:
    RandomTwister();
    int randomPeriod(int l, int u);
};
