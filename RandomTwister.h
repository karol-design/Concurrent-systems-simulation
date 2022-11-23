/**
 * @file    RandomTwister.h
 * @brief   RandomTwister class for generating uniformly distributed random numbers
 * @author  Karol Wojslaw (10746230)
 */

#pragma once

#include <chrono>
#include <ctime>
#include <mutex>
#include <random>

using namespace std;

class RandomTwister {
   private:
    std::mt19937 rnd;    // mt19937 type object
    std::mutex rand_mu;  // mutex for generating random number

   public:
    RandomTwister();
    int randomPeriod(int l, int u);
};
