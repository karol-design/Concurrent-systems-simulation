/**
 * @file    Results.h
 * @brief   Results class for allocating places in the race
 * @author  Karol Wojslaw (10746230)
 */

#pragma once

#include <iostream>
#include <string>

#include "Competitor.h"

class Results {
   private:
    std::string resArr[4][2];

   public:
    Results();
    void setPosition(Competitor c);
    void printResults();
};
