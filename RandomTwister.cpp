#include "RandomTwister.h"

RandomTwister::RandomTwister() : rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count()){}

int RandomTwister::randomPeriod(int l, int u) {
    std::lock_guard<std::mutex> guard (mu);
    std::uniform_int_distribution<int> dis(l, u);
    int n = dis(rnd);
    return n;
}
