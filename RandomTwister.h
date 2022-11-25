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

class RandomTwister {
   private:
    std::mt19937 rnd;    // standard mersenne_twister_engine object
    std::mutex rand_mu;  // mutex for guarding the CS

   public:
    RandomTwister();
    int randomPeriod(int l, int u);
};
