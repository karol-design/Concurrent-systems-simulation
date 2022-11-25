/**
 * @file    RandomTwister.cpp
 * @brief   RandomTwister class for generating uniformly distributed random numbers
 * @author  Karol Wojslaw (10746230)
 */

#include "RandomTwister.h"

/**
 * @brief Constructor. Seeds the mersenne_twister_engine with time value
 */
RandomTwister::RandomTwister() : rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count()) {}

/**
 * @brief Generate a random int number in range l to u (thread-safe)
 * @param int lower limit
 * @param int upper limit
 * @return int generated random number
 */
int RandomTwister::randomPeriod(int l, int u) {
    std::lock_guard<std::mutex> guard(rand_mu);  // guard the access to the generator with a mutex
    std::uniform_int_distribution<int> dis(l, u);
    int number = dis(rnd);
    return number;
}  // guard goes out of scope, rand_mu mutex is released
