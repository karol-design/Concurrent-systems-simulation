/**
 * @file    RandomTwister.cpp
 * @brief   RandomTwister class for generating uniformly distributed random numbers
 * @author  Karol Wojslaw (10746230)
 */

#include "RandomTwister.h"

RandomTwister::RandomTwister() : rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count()) {}

int RandomTwister::randomPeriod(int l, int u) {  // generate a random number in range l to u
    std::lock_guard<std::mutex> guard(rand_mu);  // guard the access to the generator with a lock_guard mutex
    std::uniform_int_distribution<int> dis(l, u);
    int number = dis(rnd);
    return number;
}
