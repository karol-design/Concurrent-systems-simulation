/**
 * @file    competitor.cpp
 * @brief   Competitor class for storing team and name of each athlete
 * @author  Karol Wojslaw (10746230)
 */

#include "Competitor.h"

#include <iostream>

Competitor::Competitor() {}

Competitor::Competitor(std::string tN, std::string pN) : teamName(tN), personName(pN) {}

void Competitor::setTeam(std::string tN) { teamName = tN; }  // mutators for team and name
void Competitor::setPerson(std::string pN) { personName = pN; }

std::string Competitor::getTeam() { return teamName; }  // accessors for team and name
std::string Competitor::getPerson() { return personName; }

Competitor Competitor::makeNull() { return *(new Competitor(" ", " ")); }  // null object generator

void Competitor::printCompetitor() {  // print team and name
    std::cout << "Team = " << teamName << "\tPerson = " << personName << endl;
}
