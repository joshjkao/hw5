

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool bt(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, vector<size_t>& currShifts, DailySchedule& sched, size_t i, size_t j);

// Add your implementation of schedule() and other helper functions here

bool schedule(
  const AvailabilityMatrix& avail,
  const size_t dailyNeed,
  const size_t maxShifts,
  DailySchedule& sched
)
{
  if(avail.size() == 0U){
    return false;
  }
  sched.clear();
  // Add your code below
  size_t n = avail.size();
  unsigned int k = avail[0].size();
  vector<size_t> currShifts(k, 0);
  vector<unsigned int> temp;
  for (unsigned int i = 0; i < n; i++) {
    sched.push_back(temp);
  }
  return bt(avail, dailyNeed, maxShifts, currShifts, sched, 0, 0);
}

bool bt(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, vector<size_t>& currShifts, DailySchedule& sched, size_t i, size_t j) {
  if (i == avail.size()) {
    return true;
  }
  else {
    for (unsigned int k = 0; k < avail[i].size(); k++) {
      if (avail[i][k] && (find(sched[i].begin(), sched[i].end(), k) == sched[i].end()) && currShifts[k] < maxShifts) {
        sched[i].push_back(k);
        ++currShifts[k];
        size_t new_i = i;
        size_t new_j = j+1;
        if (new_j == dailyNeed) {
          ++new_i;
          new_j = 0;
        }
        bool temp = bt(avail, dailyNeed, maxShifts, currShifts, sched, new_i, new_j);
        if (!temp) {
          --currShifts[k];
          sched[i].pop_back();
        }
        else {
          return true;
        }
      }
    }
    return false;
  }
}
