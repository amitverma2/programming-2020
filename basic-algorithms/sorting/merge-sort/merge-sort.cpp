#include<iostream>
#include<vector>

using namespace std;

// Top Down
class MyMergeSort {
    void merge(vector<int> & sequence, int left, int mid, int right) {
      // assume [left, mid] is sorted and [mid+1, right] is sorted
      // merge both
      int cur = left;
      vector<int> leftSeq(sequence.begin() + left, sequence.begin() + mid + 1);
      vector<int> rightSeq(sequence.begin() + mid + 1, sequence.begin() + right + 1);
      int leftPtr = 0;
      int rightPtr = 0;

      while (leftPtr < leftSeq.size() && rightPtr < rightSeq.size()) {
        if (leftSeq[leftPtr] <= rightSeq[rightPtr]) {
          sequence[cur++] = leftSeq[leftPtr++];
        } else {
          sequence[cur++] = rightSeq[rightPtr++];
        }
      }
      while (leftPtr < leftSeq.size()) {
        sequence[cur++] = leftSeq[leftPtr++];
      }
      while (rightPtr < rightSeq.size()) {
        sequence[cur++] = rightSeq[rightPtr++];
      }
    }
  public:
    void sort(vector<int> & sequence, int left, int right) {
      if (left >= right) return ; // nothing to sort

      int mid = left + (right - left)/2;

      sort(sequence, left, mid);
      sort(sequence, mid+1, right);
      merge(sequence, left, mid, right);
    }
    void print(vector<int> & sequence) {
      cout << "Sequence is :\n" ;
      for (vector<int>::const_iterator p = sequence.begin();
           p != sequence.end();
           ++p) {
             cout << *p << " ";
           }
      cout << endl;
    }
};

// Top Down 2
class Solution {
    void mergeSortArray(vector<int>& nums, int first, int last) {
        if (first >= last) return;
        int mid = first + (last - first)/2;
        mergeSortArray(nums, first, mid);
        mergeSortArray(nums, mid+1, last);
        vector<int> mergedVector(last-first+1);
        int to = 0; int from1 = first; int from2 = mid+1;
        while (from1 <= mid && from2 <= last) {
            if (nums[from1] <= nums[from2])
                mergedVector[to++] = nums[from1++];
            else
                mergedVector[to++] = nums[from2++];
        }
        while (from1 <= mid) {
            mergedVector[to++] = nums[from1++];
        }
        while (from2 <= last) {
            mergedVector[to++] = nums[from2++];
        }
        for (int i = 0 ; i < (last-first+1); ++i) {
            nums[first+i] = mergedVector[i];
        }
        return;
    }
public:
    void print(vector<int> & sequence) {
      cout << "Sequence is :\n" ;
      for (vector<int>::const_iterator p = sequence.begin();
           p != sequence.end();
           ++p) {
             cout << *p << " ";
           }
      cout << endl;
    }
    vector<int> sortArray(vector<int>& nums) {
        if (nums.size() > 1) {
            mergeSortArray(nums, 0, nums.size()-1);
        }
        return nums;
    }
};

int main() {
  vector<int> sequence = { 11, 2, 3, 14 };

/*
  MyMergeSort * obj = new MyMergeSort;
  obj->print(sequence);
  obj->sort(sequence, 0, sequence.size()-1);
  obj->print(sequence);
*/
  Solution * sol = new Solution;
  sol->print(sequence);
  sol->sortArray(sequence);
  sol->print(sequence);

  return 0;
}
