#include<iostream>
#include<string>
#include<cstdio>

using namespace std;

class Solution {
public:
    string nextClosestTime(string time) {
        int _t[4];
        _t[0] = time[0] - '0';
        _t[1] = time[1] - '0';
        _t[2] = time[3] - '0';
        _t[3] = time[4] - '0';
        int t_minutes = 60 * (_t[0] * 10 + _t[1]) + (_t[2]*10 + _t[3]);
        int ans = t_minutes;
        int ans_diff = 24 * 60;
        for (int h1 = 0 ; h1 < 4; ++h1) {
            for (int h2 = 0 ; h2 < 4; ++h2) {
                if (_t[h1] * 10 + _t[h2] < 24) {
                    // valid hour
                    for (int m1 = 0 ; m1 < 4; ++m1) {
                        for (int m2 = 0 ; m2 < 4; ++m2) {
                            if (_t[m1] * 10 + _t[m2] < 60) {
                                // valid minutes
                                int t2_minutes = 60 * (_t[h1] * 10 + _t[h2]) + (_t[m1] * 10 + _t[m2]);
                                int diff = t2_minutes - t_minutes;
                                if (diff <= 0) diff += 24 * 60;
                                if (diff < ans_diff) {
                                    ans_diff = diff;
                                    ans = t2_minutes;
                                }
                            }
                        }
                    }
                }
            }
        }
        char outtime[6] = "";
        sprintf(outtime, "%02d:%02d", ans / 60, ans % 60);
        return string(outtime);
    }
};

int main() {
  string time("19:34");
  Solution *obj = new Solution;

  std::cout << "Next closest time is : " << obj->nextClosestTime(time) << std::endl;

  return 0;
}