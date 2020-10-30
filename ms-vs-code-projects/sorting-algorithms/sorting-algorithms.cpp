#include<iostream>
#include<vector>

class Sorting {
public:
  virtual void sort(std::vector<int>& nums) = 0;
  void swap(std::vector<int>& nums, int a, int b) {
    int temp = nums[a];
    nums[a] = nums[b];
    nums[b] = temp;
  }
  void print(std::vector<int>& nums) {
    std::cout << "Vector: " ;
    for (auto x : nums) {
      std::cout << x << " ";
    }
    std::cout << std::endl;
  }
};

class SelectionSort : public Sorting { 
public:
  void sort(std::vector<int>& nums) {
    std::cout << "Selection Sorting...\n";
    int N = nums.size();

    for (int i = 0 ; i < N; ++i) {
      int min = i;
      for (int j = i + 1 ; j < N; ++j) {
        if (nums[j] < nums[min]) {
          min = j;
        }
      }
      swap(nums, i, min);
    }
  }
};

class InsertionSort: public Sorting {
public:
  void sort(std::vector<int>& nums) {
    std::cout << "Insertion sorting...\n";

    int N = nums.size();

    for (int i = 0; i < N; ++i) {
      for (int j = i ; j > 0; --j) {
        if (nums[j-1] > nums[j]) {
          swap(nums, j-1, j);
        } else {
          break;
        }
      }
    }
  }
};

int main() {
  std::vector<int> nums = { 2, 3, 4, 1, 5 ,9, 10, 30, 6, 5 };

  Sorting* obj = new InsertionSort;

  std::cout << "Before sorting...\n";
  obj->print(nums);

  obj->sort(nums);

  std::cout << "After sorting...\n";
  obj->print(nums);

  return 0;
}