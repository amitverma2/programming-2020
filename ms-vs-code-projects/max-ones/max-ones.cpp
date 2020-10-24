#include<iostream>
#include<vector>

using namespace std;

// l485. Max Consecutive Ones
// Given a binary array, find the maximum number of consecutive 1s in this array.

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int max = 0;
        for (int i = 0 ; i < nums.size(); ) {
            int cur = 0;
            if (nums[i] == 0) {
                ++i;
                continue;
            }
            while (i < nums.size() &&
                  nums[i] == 1) {
                ++i;
                cur++;
            }
            if (cur > max) { max = cur; }
        }
        return max;
    }
};

int main() {
  vector<int> input = { 1, 0, 1, 1, 0, 1 };
  Solution* obj = new Solution;

  cout << obj->findMaxConsecutiveOnes(input) << endl;

  return 0;
}