// AssignmentPart1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "Competitor.h"
#include "ThreadMap.h"
#include "RandomTwister.h"

const int NO_TEAMS = 4; 	// number of teams in the race
const int NO_MEMBERS = 4;	// number of athletes in the team

ThreadMap global_tm;

void run(Competitor& c) {
    // store thread id and competitor in a map
    global_tm.insertThreadPair(c);

    // delay for random period
    RandomTwister rnd;
    int delay_ms = rnd.randomPeriod(9580, 12000);
    double delay_s = ((double) delay_ms) / 1000.00;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));

    // print message stating which competitor has just finished
    std::cout << delay_s << "\t";
    c.printCompetitor();
}

int main() {
    thread theThreads[NO_TEAMS][NO_MEMBERS];
    Competitor teamsAndMembers[NO_TEAMS][NO_MEMBERS];

    string teams[NO_TEAMS] = {"Jamaica", "Japan", "UK", "RSA"};
    string members[NO_TEAMS*NO_MEMBERS] = { "Bolt", "Blake", "Frater", "Carter", "Tada", "Shiraishi",
                                            "Kiryu", "Brown", "Gemili", "Hughes", "Kilty", "Blake",
                                            "Dlodlo", "Magakwe", "Munyai", "Simbine"};

    // define elements of teamsAndMembers
    for(int i = 0; i < NO_TEAMS; i++) {
        for(int j = 0; j < NO_MEMBERS; j++) {
            teamsAndMembers[i][j] = Competitor(teams[i], members[i*NO_MEMBERS + j]);
        }
    }

    // create threads (elements of theThreads)
    for(int i = 0; i < NO_TEAMS; i++) {
        for(int j = 0; j < NO_MEMBERS; j++) {
            theThreads[i][j] = std::thread(run, std::ref(teamsAndMembers[i][j]));
        }
    }

    // join threads
    for(int i = 0; i < NO_TEAMS; i++) {
        for(int j = 0; j < NO_MEMBERS; j++) {
            theThreads[i][j].join();
        }
    }

    global_tm.printMapContents();
    return 0;
}
