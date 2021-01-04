#include<iostream>
#include<vector>

using namespace std;

class NumArray {
    vector<int>& array;
    vector<int> sums;
    int sz;
public:
    NumArray(vector<int>& nums) : array(nums), sums(nums), sz(array.size()) {
        for (int i = 1; i < nums.size(); ++i) {
            sums[i] += sums[i-1];
        }
    }
    
    int sumRange(int i, int j) {
        if (sz > 0)
            return sums[j] - sums[i] + array[i];
        else
            return 0;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */

int main() {
  std::vector<int> nums = { -2, 0, 3, -5, 2, -1 };

  NumArray *obj = new NumArray(nums);

  std::cout << "Sum range 0,2 : " << obj->sumRange(0, 2) << std::endl;
  std::cout << "Sum range 2,5 : " << obj->sumRange(2, 5) << std::endl;
  std::cout << "Sum range 0,5 : " << obj->sumRange(0, 5) << std::endl;

  return 0;
}