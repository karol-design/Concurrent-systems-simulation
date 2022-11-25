/**
 * @file    main.c
 * @brief   This program simulates four-by-one hundred metres sprint relay race. There are four competing
 *          teams and four athletes in every team, each represented by a unique thread executing the run
 *          function. The code utilise c++ map, mutexes, random number generation, synchronisation
 *          mechanisms.
 * @author  Karol Wojslaw (10746230)
 */

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "Competitor.h"
#include "EZAgent.h"
#include "FinishAgent.h"
#include "RaceCommon.h"
#include "RandomTwister.h"
#include "Results.h"
#include "StartAgent.h"
#include "ThreadMap.h"

#define DEBUG true  // turn debug messages on / off

RandomTwister rnd;  // an instance of a Random number generator class

void run(Competitor &c, SyncAgent &thisAgent, SyncAgent &nextAgent, ThreadMap &tMap);

/* Main function */
int main() {
    ThreadMap tMap;  // an instance of a STL Map wrapper class

    Competitor teamsAndMembers[NO_TEAMS][NO_MEMBERS];  // Competitor objects representing athletes
    std::thread theThreads[NO_TEAMS][NO_MEMBERS];      // Thread objects representing athletes

    StartAgent theStartAgent;                    // the start synchronisation agent
    EZAgent exchanges[NO_TEAMS][NO_EXCHANGES];   // exchange zone sycnhronisation agents
    FinishAgent theFinishAgent(std::ref(tMap));  // the finish synchronisation agent

    std::string teams[NO_TEAMS] = {"Jamaica", "Japan", "UK", "RSA"};  // team and athlete names
    std::string members[NO_TEAMS * NO_MEMBERS] = {
        "Bolt", "Blake", "Frater", "Carter", "Tada", "Lin",
        "Kiryu", "Brown", "Gemili", "Hughes", "Kilty", "Blake",
        "Dlodlo", "Ofili", "Munyai", "Amusan"};

    for (int i = 0; i < NO_TEAMS; i++) {  // create and assign all teamsAndMembers objects
        for (int j = 0; j < NO_MEMBERS; j++) {
            teamsAndMembers[i][j] = Competitor(teams[i], members[i * NO_MEMBERS + j]);
        }
    }

    for (int i = 0; i < NO_TEAMS; i++) {  // create and assign all theThreads threads
        theThreads[i][0] = std::thread(run, std::ref(teamsAndMembers[i][0]),
                                       std::ref(theStartAgent),
                                       std::ref(exchanges[i][0]),
                                       std::ref(tMap));

        for (int j = 1; j < (NO_MEMBERS - 1); j++) {
            theThreads[i][j] = std::thread(run, std::ref(teamsAndMembers[i][j]),
                                           std::ref(exchanges[i][j - 1]),
                                           std::ref(exchanges[i][j]),
                                           std::ref(tMap));
        }

        theThreads[i][NO_MEMBERS - 1] = std::thread(run, std::ref(teamsAndMembers[i][3]),
                                                    std::ref(exchanges[i][2]),
                                                    std::ref(theFinishAgent),
                                                    std::ref(tMap));
    }

    if (DEBUG) {std::cout << "main id " << std::this_thread::get_id() << ": Threads created successfully\n";}

    while (theStartAgent.readyToStart() == false) {}  // Wait until all threads are blocked and ready to start

    int delay_ms = rnd.randomPeriod(1000, 4000);  // wait for a random delay between 1 and 4 seconds
    if (DEBUG) {std::cout << "main id " << std::this_thread::get_id() << ": All threads in the START position blocked. " << delay_ms << " ms delay...\n";}

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));  // block the main thread

    theStartAgent.proceed();  // unblock threads in the Start synchronisation agent
    if (DEBUG) {std::cout << "main id " << std::this_thread::get_id() << ": START threads unblocked. Go!\n\n";}

    for (int i = 0; i < NO_TEAMS; i++) {  // join all threads to the main thread (wait for them to finish)
        for (int j = 0; j < NO_MEMBERS; j++) {
            theThreads[i][j].join();
        }
    }

    if (DEBUG) {tMap.printMapContents();}
    int teamTime[4] = {0};
    int team = 0;

    tMap.initContentIt();                                         // initialise content iterator in the thread map
    for (int k = 0; k < tMap.ThreadMapSize(); k++) {              // iterate through all entries in the map
        teamTime[team] += tMap.getNextMappedVal().getRaceTime();  // update team time using tMap.getNextMappedVal()
        if (((k + 1) % 4) == 0) {team++;}
    }

    Results res = theFinishAgent.returnResults();  // collect and output race results

    std::cout << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "Race Results" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    res.printResults();  // print race results (teams in order of finishing)

    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "Total Team Times" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    for (int i = 0; i < NO_TEAMS; i++) {
        double time_s = ((double)teamTime[i] / 1000.00);                                           // convert miliseconds to seconds
        std::cout << teamsAndMembers[i][0].getTeam() << "\t" << DP3(time_s) << " s" << std::endl;  // print team and its time
    }

    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "Individual Times" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    for (int i = 0; i < NO_TEAMS; i++) {
        std::cout << teamsAndMembers[i][0].getTeam() << ":" << std::endl;  // print team
        for (int j = 0; j < NO_MEMBERS; j++) {                             // print results of all athletes in the team
            int time_ms = teamsAndMembers[i][j].getRaceTime();
            double time_s = ((double)time_ms / 1000.0);  // convert miliseconds to seconds
            std::cout << teamsAndMembers[i][j].getPerson() << ":\t" << DP3(time_s) << " s" << std::endl;
        }
        if (i != 3) {std::cout << "%%%%%%%%%%%%%%%" << std::endl;}
    }
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    return 0;
}

/**
 * @brief Simulate an athlete: randomly assign run time, map thread into competitor, sleep and unblock the next thread
 * @param Competitor pointer to a competitor object
 * @param SyncAgent pointer to a synchronisation object for this thread
 * @param SyncAgent pointer to a synchronisation object for the next thread
 * @param ThreadMap map of threads and associated Competitor objects
 */
void run(Competitor &c, SyncAgent &thisAgent, SyncAgent &nextAgent, ThreadMap &tMap) {
    thisAgent.pause();

    int delay_ms = rnd.randomPeriod(9580, 12000);  // assign a random delay between 9.58 and 12 seconds
    double delay_s = ((double)delay_ms / 1000.0);
    c.setRaceTime(delay_ms);
    tMap.insertThreadPair(c);  // store thread id and an instance of a Competitor class in a map

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));  // block the thread
    if (DEBUG) {std::cout << "run:\t" << c.getPerson() << "\t" << DP3(delay_s) << " s" << std::endl;}

    nextAgent.proceed();
}
