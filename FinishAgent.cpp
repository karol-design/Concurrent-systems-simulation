#include "FinishAgent.h"

 FinishAgent::FinishAgent(ThreadMap& t) : tMap(t) {
 }

 void FinishAgent::proceed() {
    std::unique_lock<std::mutex> lk (finish_mutex);
    Competitor c;
    c = tMap.getCompetitor();
    r.setPosition(c);
 }

 void FinishAgent::pause() {}

 Results FinishAgent::returnResults() {
    return r;
 }
