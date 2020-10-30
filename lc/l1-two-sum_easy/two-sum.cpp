#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    // brute force
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0 ; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return { -1, -1 };
    }
};

int main() {
  vector<int> nums = { 2, 7, 11, 15 };

  Solution* obj = new Solution;
  vector<int> index = obj->twoSum(nums, 9);
  std::cout << index[0] << "," << index[1] << std::endl;
  return 0;
}