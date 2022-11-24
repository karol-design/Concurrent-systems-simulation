/**
 * @file    Competitor.h
 * @brief   Competitor class for storing team and name of each athlete
 * @author  Karol Wojslaw (10746230)
 */

#pragma once

#include <string>
#include "RaceCommon.h"

class Competitor {
   private:
    std::string teamName;
    std::string personName;
    int raceTime;

   public:
    Competitor();
    Competitor(std::string tN, std::string pN);

    void setTeam(std::string tN);
    void setPerson(std::string pN);
    void setRaceTime(int rt);

    std::string getTeam();
    std::string getPerson();
    int getRaceTime();

    static Competitor makeNull();
    void printCompetitor();
};
