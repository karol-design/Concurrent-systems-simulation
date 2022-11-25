/**
 * @file    Competitor.cpp
 * @brief   Competitor class for storing team and name of each athlete
 * @author  Karol Wojslaw (10746230)
 */

#include "Competitor.h"

Competitor::Competitor() {}

/**
 * @brief Constructor
 * @param string team name
 * @param string athlete's family name
 */
Competitor::Competitor(std::string tN, std::string pN) : teamName(tN), personName(pN) {}

/**
 * @brief Set the team for the competitor (mutator)
 * @param string team name
 */
void Competitor::setTeam(std::string tN) { teamName = tN; }

/**
 * @brief Set the name for the competitor (mutator)
 * @param string athlete's family name
 */
void Competitor::setPerson(std::string pN) { personName = pN; }

/**
 * @brief Set the race time (mutator)
 * @param int athlete's race time
 */
void Competitor::setRaceTime(int rt) { raceTime = rt; }

/**
 * @brief Get the team of the competitor (accessor)
 * @return Team name
 */
std::string Competitor::getTeam() { return teamName; }

/**
 * @brief Get the name of the competitor (accessor)
 * @return Athlete's family name
 */
std::string Competitor::getPerson() { return personName; }

/**
 * @brief Get the race time of the competitor (accessor)
 * @return Race time in ms
 */
int Competitor::getRaceTime() { return raceTime; }

/**
 * @brief Generate a NULL Competitor object
 * @return NULL Competitor object
 */
Competitor Competitor::makeNull() { return *(new Competitor(" ", " ")); }

/**
 * @brief Print competitor's team, name and time in ms
 */
void Competitor::printCompetitor() { std::cout << "Team: " << teamName << "\tName: " << personName << "\tTime: " << raceTime << std::endl; }
