/**
 * @file    main.c
 * @brief   This program simulates four-by-one hundred metres sprint relay race. There are four competing
 *          teams and four athletes in every team, each represented by a unique thread executing the run
 *          function. The code utilise c++ maps, mutexes, random number generation, synchronisation
 *          mechanisms.
 * @author  Karol Wojslaw (10746230)
 */

#include <chrono>  // time conversion
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

ThreadMap tMap;     // an instance of a STL Map wrapper class (shared resource)
RandomTwister rnd;  // an instance of a Random number generator class (shared resource)

int competitor = 0;


/* Function declaration */
void run(Competitor &c, SyncAgent &thisAgent, SyncAgent &nextAgent);

/* Main function */
int main() {
    thread theThreads[NO_TEAMS][NO_MEMBERS];  // arrays of threads and objects representing athletes
    Competitor teamsAndMembers[NO_TEAMS][NO_MEMBERS];
    EZAgent exchanges[NO_TEAMS][NO_EXCHANGES];
    StartAgent theStartAgent;
    FinishAgent theFinishAgent;

    string teams[NO_TEAMS] = {"Jamaica", "Japan", "UK", "RSA"};
    string members[NO_TEAMS * NO_MEMBERS] = {
        "Bolt", "Blake", "Frater", "Carter", "Tada", "Shiraishi",
        "Kiryu", "Brown", "Gemili", "Hughes", "Kilty", "Blake",
        "Dlodlo", "Magakwe", "Munyai", "Simbine"};

    for (int i = 0; i < NO_TEAMS; i++) {  // create and assign all teamsAndMembers objects
        for (int j = 0; j < NO_MEMBERS; j++) {
            teamsAndMembers[i][j] = Competitor(teams[i], members[i * NO_MEMBERS + j]);
        }
    }

    for (int i = 0; i < NO_TEAMS; i++) {  // create and assign all theThreads threads
        theThreads[i][0] = std::thread(run, std::ref(teamsAndMembers[i][0]), std::ref(theStartAgent), std::ref(exchanges[i][0]));
        theThreads[i][1] = std::thread(run, std::ref(teamsAndMembers[i][1]), std::ref(exchanges[i][0]), std::ref(exchanges[i][1]));
        theThreads[i][2] = std::thread(run, std::ref(teamsAndMembers[i][2]), std::ref(exchanges[i][1]), std::ref(exchanges[i][2]));
        theThreads[i][3] = std::thread(run, std::ref(teamsAndMembers[i][3]), std::ref(exchanges[i][2]), std::ref(theFinishAgent));
    }

    std::cout << "Main: threads created" << std::endl;

    while(theStartAgent.readyToStart() == false) {} // Wait until all threads are blocked and ready to start

    int delay_ms = rnd.randomPeriod(1000, 4000);  // wait for a random delay between 1 and 4 seconds
    std::cout << "Main: all threads blocked. " << delay_ms << " ms delay..." << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));  // block the thread

    theStartAgent.proceed();
    std::cout << "Main: " << "threads unblocked. Go!" << std::endl;

    for (int i = 0; i < NO_TEAMS; i++) {  // join all threads to the main thread
        for (int j = 0; j < NO_MEMBERS; j++) {
            theThreads[i][j].join();
        }
    }

    tMap.printMapContents();
    return 0;
}

/**
 * @brief Simulate an athlete: randomly assign run time, map thread into competitor
 * @param Competitor pointer to a competitor object
 * @param SyncAgent pointer to a synchronisation object for this thread
 * @param SyncAgent pointer to a synchronisation object for the next thread
 */
void run(Competitor &c, SyncAgent &thisAgent, SyncAgent &nextAgent) {
    tMap.insertThreadPair(c);  // store thread id and an instance of a Competitor class in a map
    thisAgent.pause();

    int delay_ms = rnd.randomPeriod(9580, 12000);  // assign a random delay between 9.58 and 12 seconds
    double delay_s = ((double)delay_ms) / 1000.00;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));  // block the thread

    nextAgent.proceed();

    std::cout << competitor << ": " << delay_s << "\t";  // print the competitor and its time
    c.printCompetitor();
    competitor++;
    if(competitor % 4 == 0){
        std::cout << std::endl;
    }
}
