/**
 * @file    competitor.h
 * @brief   Competitor class for storing team and name of each athlete
 * @author  Karol Wojslaw (10746230)
 */

#pragma once

#include <string>

class Competitor {
   private:
    std::string teamName;
    std::string personName;

   public:
    Competitor();
    Competitor(std::string tN, std::string pN);
    void setTeam(std::string tN);
    std::string getTeam();
    void setPerson(std::string pN);
    std::string getPerson();
    static Competitor makeNull();
    void printCompetitor();
};
