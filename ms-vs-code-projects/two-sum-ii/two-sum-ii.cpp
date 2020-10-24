#include<iostream>
#include<vector>

using namespace std;

// 167. Two Sum II - Input array is sorted
// Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.


class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0;
        int j = numbers.size()-1;
        vector<int> indices(2);
        
        while (i < j) {
            int sum;
            while ((sum = numbers[i] + numbers[j]) > target) {
                --j;
            }
            if (sum == target) {
                indices[0] = i + 1;
                indices[1] = j + 1;
                return indices;
            }
            ++i;
        }
        return indices; // should never come here.
    }
};

int main() {
  vector<int> numbers = { 2, 7, 11, 15 };
  int target = 9;

  Solution* obj = new Solution;

  vector<int> indices(2);

  indices = obj->twoSum(numbers, target);
  cout << "index1 = " << indices[0] << ", index2 = " << indices[1] << endl;

  return 0;
}