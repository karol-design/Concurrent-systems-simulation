/**
 * @file    RaceCommon.h
 * @brief   Macro definitions and variables common for all program files
 * @author  Karol Wojslaw (10746230)
 */

#pragma once

#include <iomanip>
#include <iostream>

#define DP3(num) std::fixed << std::setprecision(3) << (num)  // Print numbers to 3 decimal places

const int NO_TEAMS = 4;                     // number of teams in the race
const int NO_MEMBERS = 4;                   // number of athletes in the team
const int NO_EXCHANGES = (NO_MEMBERS - 1);  // number of exchange zones
