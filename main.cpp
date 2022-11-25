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
#include "RandomTwister.h"
#include "ThreadMap.h"
#include "RaceCommon.h"
#include "StartAgent.h"
#include "FinishAgent.h"
#include "EZAgent.h"
#include "Results.h"

#define DEBUG true

RandomTwister rnd;  // an instance of a Random number generator class

/* Function declaration */
void run(Competitor &c, SyncAgent &thisAgent, SyncAgent &nextAgent, ThreadMap &tMap);

/* Main function */
int main() {
    ThreadMap tMap;     // an instance of a STL Map wrapper class (shared resource)

    std::thread theThreads[NO_TEAMS][NO_MEMBERS];  // arrays of threads and objects representing athletes
    Competitor teamsAndMembers[NO_TEAMS][NO_MEMBERS];
    EZAgent exchanges[NO_TEAMS][NO_EXCHANGES];
    StartAgent theStartAgent;
    FinishAgent theFinishAgent(std::ref(tMap));

    std::string teams[NO_TEAMS] = {"Jamaica", "Japan", "UK", "RSA"};
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

        theThreads[i][1] = std::thread(run, std::ref(teamsAndMembers[i][1]),
                                            std::ref(exchanges[i][0]),
                                            std::ref(exchanges[i][1]),
                                            std::ref(tMap));

        theThreads[i][2] = std::thread(run, std::ref(teamsAndMembers[i][2]),
                                            std::ref(exchanges[i][1]),
                                            std::ref(exchanges[i][2]),
                                            std::ref(tMap));

        theThreads[i][3] = std::thread(run, std::ref(teamsAndMembers[i][3]),
                                            std::ref(exchanges[i][2]),
                                            std::ref(theFinishAgent),
                                            std::ref(tMap));
    }

    if(DEBUG){std::cout << "main id " << std::this_thread::get_id() << ": Threads created successfully" << std::endl;}

    while(theStartAgent.readyToStart() == false) {} // Wait until all threads are blocked and ready to start

    int delay_ms = rnd.randomPeriod(1000, 4000);  // wait for a random delay between 1 and 4 seconds
    if(DEBUG){std::cout << "main id " << std::this_thread::get_id() << ": All threads in the START position blocked. " << delay_ms << " ms delay..." << std::endl;}

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));  // block the thread

    theStartAgent.proceed();
    if(DEBUG){std::cout << "main id " << std::this_thread::get_id() << ": START threads unblocked. Go!" << std::endl << std::endl;}

    for (int i = 0; i < NO_TEAMS; i++) {  // join all threads to the main thread
        for (int j = 0; j < NO_MEMBERS; j++) {
            theThreads[i][j].join();
        }
    }

    if(DEBUG){tMap.printMapContents();}
    int teamTime[4] = { 0 };
    int team = 0;

    tMap.initContentIt(); // tMap is the ThreadMap in my program
    for (int k = 0; k < tMap.ThreadMapSize(); k++) {
        teamTime[team] += tMap.getNextMappedVal().getRaceTime();
        if(((k+1)%4) == 0) {team++;}
        // update team time using tMap.getNextMappedVal()
        //- a call to this function returns the next Competitor object stored in the map
    }

    Results res = theFinishAgent.returnResults();

    std::cout << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "Race Results" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    res.printResults();
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "Total Team Times" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    for(int i=0; i<NO_TEAMS; i++) {
        double time_s = ((double)teamTime[i] / 1000.00);
        std::cout << teamsAndMembers[i][0].getTeam() << "\t" << DP3(time_s) << " s" << std::endl;
    }

    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "Individual Times" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    for(int i=0; i<NO_TEAMS; i++) {
        std::cout << teamsAndMembers[i][0].getTeam() << ":" << std::endl;
        for(int j=0; j<NO_MEMBERS; j++) {
            int time_ms = teamsAndMembers[i][j].getRaceTime();
            double time_s = ((double)time_ms/1000.0);
            std::cout << teamsAndMembers[i][j].getPerson() << ":\t" << DP3(time_s) << " s" << std::endl;
        }
        if(i != 3) {std::cout << "%%%%%%%%%%%%%%%" << std::endl;}
    }
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

    return 0;
}

/**
 * @brief Simulate an athlete: randomly assign run time, map thread into competitor
 * @param Competitor pointer to a competitor object
 * @param SyncAgent pointer to a synchronisation object for this thread
 * @param SyncAgent pointer to a synchronisation object for the next thread
 */
void run(Competitor &c, SyncAgent &thisAgent, SyncAgent &nextAgent, ThreadMap &tMap) {
    thisAgent.pause();

    int delay_ms = rnd.randomPeriod(9580, 12000);  // assign a random delay between 9.58 and 12 seconds
    double delay_s = ((double)delay_ms / 1000.0);
    c.setRaceTime(delay_ms);
    tMap.insertThreadPair(c);  // store thread id and an instance of a Competitor class in a map

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));  // block the thread
    if(DEBUG){std::cout << "run:\t" << c.getPerson() << "\t" << DP3(delay_s) << " s" << std::endl;}

    nextAgent.proceed();
}
