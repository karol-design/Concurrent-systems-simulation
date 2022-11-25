/**
 * @file    Results.cpp
 * @brief   Results class for allocating places in the race
 * @author  Karol Wojslaw (10746230)
 */

#include "Results.h"

/**
 * @brief Constructor. Populate the result array with places
 */
Results::Results() {
    resArr[0][0] = "First\t";
    resArr[1][0] = "Second\t";
    resArr[2][0] = "Third\t";
    resArr[3][0] = "Fourth\t";
}

/**
 * @brief Allocate Competitors to an appropriate position in the results
 * @param Competitor to be allocated a place
 */
void Results::setPosition(Competitor c) {
    if (resArr[0][1].empty()) {
        resArr[0][1] = c.getTeam();
    } else if (resArr[1][1].empty()) {
        resArr[1][1] = c.getTeam();
    } else if (resArr[2][1].empty()) {
        resArr[2][1] = c.getTeam();
    } else if (resArr[3][1].empty()) {
        resArr[3][1] = c.getTeam();
    }
}

/**
 * @brief Print race results (teams in order)
 */
void Results::printResults() {
    for (int i = 0; i < 4; i++) {std::cout << resArr[i][0] << resArr[i][1] << std::endl;}
}
