#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        if (intervals.size() == 1) { return true; }
        for (int i = 1; i < intervals.size() ; ++i) {
            if (intervals[i][0] < intervals[i-1][1]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
  vector<vector<int> > intervals = {
    /* can not attend
    { 0, 30 },
    { 5, 10 },
    { 15, 20 }
    */
    { 7, 10 },
    { 2, 4 }
  };

  Solution* obj = new Solution;

  std::cout << ((obj->canAttendMeetings(intervals)?"Can attend!":"Can not attend")) << std::endl;

  return 0;
}