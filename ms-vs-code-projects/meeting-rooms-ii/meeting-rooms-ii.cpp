#include<iostream>
#include<queue>
#include<vector>

using namespace std;

// Find out the smallest number of meeting room required to schedule a set of meetings having {s, e} start and end times
// I had to take all the hints for this solution, but nonetheless got it working quickly
// Learnt min-heap, and the concept for ordering of the events/data in solving problems.

class Solution {
public:
  static bool sortStartMeeting(const vector<int>& m1, const vector<int>& m2) {
    return m1[0] < m2[0];
  }

  int minMeetingRooms(vector<vector<int> >& intervals) {
    // first sort meetings by start time
    sort(intervals.begin(), intervals.end(), sortStartMeeting);
    
    // now go over meetings one by one, and keep track of end times in a min-heap
    priority_queue<int, vector<int>, greater<int> > endTimesHeap;

    int count = 0;
    for (int i = 0; i < intervals.size(); ++i) {
      // for each meeting check if the heap top is < the end time of this meeting
      int endTime = intervals[i][1];
      int startTime = intervals[i][0];
      if (endTimesHeap.empty()) {
        count = 1;
        endTimesHeap.push(endTime);
      } else {
        int earliestFreeTime = endTimesHeap.top();
        if (earliestFreeTime > startTime) {
          // can't use the existing rooms, allocate new room
          count++;
          // record the end time of this new room in the min heap
          endTimesHeap.push(endTime);
        } else {
          // no need for new room, update the endTime in the heap
          endTimesHeap.pop();
          endTimesHeap.push(endTime);                    
        }
      }
    }
    return count;
  }
};

int main(int argc, char *argv[])
{
  vector<vector<int> > meetings = { {0, 30}, {1, 10}, {9, 20}};
  // ans should be 3

  cout << (new Solution)->minMeetingRooms(meetings) << endl;

  return 0;
}