#include<unordered_set>
#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        
        int maxXor = 0;
        for (int i = sizeof(int) * 8 - 1; i >=0; --i) {
            maxXor <<= 1;
            int curXor = maxXor | 1;

            unordered_set<int> hashMap;
            for (int j = 0; j < nums.size(); ++j) {
                hashMap.insert(nums[j] >> i);
            }
            bool found = false;
            for (int j = 0; j < nums.size(); ++j) {
                if (hashMap.find((nums[j] >> i) ^ curXor) != hashMap.end()) {
                    found = true;
                }
            }
            if (found) {
                maxXor = curXor;
            }
        }
        return maxXor;
    }
};

int main (void) {
  vector<int> nums = { 3, 10, 5, 25, 2, 8 };

  Solution * obj = new Solution;
  cout << "Max XOR = " << obj->findMaximumXOR(nums) << endl;

  return 0;
}