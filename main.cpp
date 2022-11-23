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

const int NO_TEAMS = 4;    // number of teams in the race
const int NO_MEMBERS = 4;  // number of athletes in the team

ThreadMap tm;       // an instance of a STL Map wrapper class (shared resource)
RandomTwister rnd;  // an instance of a Random number generator class (shared resource)

/* Function declaration */
void run(Competitor &c);

/* Main function */
int main() {
  thread theThreads[NO_TEAMS][NO_MEMBERS];  // arrays of threads and objects representing athletes
  Competitor teamsAndMembers[NO_TEAMS][NO_MEMBERS];

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
    for (int j = 0; j < NO_MEMBERS; j++) {
      // Pass a Competitor object as an argument
      theThreads[i][j] = std::thread(run, std::ref(teamsAndMembers[i][j]));
    }
  }

  for (int i = 0; i < NO_TEAMS; i++) {  // join all threads to the main thread
    for (int j = 0; j < NO_MEMBERS; j++) {
      theThreads[i][j].join();
    }
  }

  tm.printMapContents();
  return 0;
}

/**
 * @brief Simulate an athlete: randomly assign run time, map thread into competitor
 * @param Competitor pointer to an object of type Competitor
 */
void run(Competitor &c) {
  tm.insertThreadPair(c);  // store thread id and an instance of a Competitor class in a map

  int delay_ms = rnd.randomPeriod(9580, 12000);  // assign a random delay between 9.58 and 12 seconds
  double delay_s = ((double)delay_ms) / 1000.00;
  std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));  // block the thread

  std::cout << delay_s << "\t";  // print the competitor and its time
  c.printCompetitor();
}
