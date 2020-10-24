#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// Given an array of 2n integers, your task is to group these integers into n pairs of
// integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all
// i from 1 to n as large as possible.
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int count = 0;
        for(vector<int>::const_iterator i = nums.begin(); i != nums.end(); i+=2) {
            count += *i;
        }
        return count;
    }
    int arrayPairSumOrderN(vector<int>& nums) {
      const int limitVal = 100000; // minimum value of an element in nums is -limitVal, maximum is +limitVal
      int counts[2*limitVal+1] = {0}; // 2*limitVal + 1 should cover all possible range of input in nums
      for(auto n : nums) {
        if (n > limitVal || n < -limitVal) {
          std::cout << "Bad input!\n";
          return 0;
        }
        counts[n+limitVal]++;
      }
      int d = 0;
      int sum = 0;
      for(int i = -limitVal; i <= limitVal; ++i) {
        sum += i * ((counts[i+limitVal] - d + 1)/2);
        d = counts[i+limitVal] - d;
        if (d < 0) d *= -1;
        d %= 2;
      }
      return sum;
    }
};

int main() {
  std::vector<int> nums = { 1, 4, 3, 2 };
  Solution* obj = new Solution;

  std::cout << "Max :" << obj->arrayPairSum(nums) << std::endl;
  std::cout << "Max O(n):" << obj->arrayPairSumOrderN(nums) << std::endl;
}