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

int main() {
  vector<int> sequence = { 11, 2, 3, 14 };

  MyMergeSort * obj = new MyMergeSort;
  obj->print(sequence);
  obj->sort(sequence, 0, sequence.size()-1);
  obj->print(sequence);
  return 0;
}
