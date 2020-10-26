#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int moveEven(int s, vector<int>& A, vector<int>& min, vector<int>& max, vector<int>& minIndex, vector<int>& maxIndex) {
        int cur = A[s];
        int curMin = -1;
        int curMinIndex = -1;
        for (int i = s + 1; i < A.size(); ++i) {
            if (A[i] == cur) {
                return i;
            } else if (A[i] < cur) {
                if (A[i] > curMin) {
                    curMin = A[i];
                    curMinIndex = i;
                }
            }
        }
        if (curMinIndex == -1) {
            return s;
        }
        return curMinIndex;
    }
    int moveOdd(int s, vector<int>& A, vector<int>& min, vector<int>& max, vector<int>& minIndex, vector<int>& maxIndex) {
        int cur = A[s];
        int curMax = 100000+1;
        int curMaxIndex = -1;
        for (int i = s + 1; i < A.size(); ++i) {
            if (A[i] > cur) {
                if (A[i] < curMax) {
                    curMax = A[i];
                    curMaxIndex = i;
                }
            } else if (A[i] == cur) {
                return i;
            }
        }
        if (curMaxIndex == -1) {
            return s;
        }
        return curMaxIndex;
    }
    bool isGoodIndex(int s, vector<int>& A, vector<int>& min, vector<int>& max, vector<int>& minIndex, vector<int>& maxIndex) {
        int move = 1;
        int newPos;
        int oldPos = s;
        while (s < A.size()-1) {
            switch(move % 2) {
                case 0:
                    newPos = moveEven(s, A, min, max, minIndex, maxIndex);
                    break;
                case 1:
                    newPos = moveOdd(s, A, min, max, minIndex, maxIndex);
                    break;
            }
            if (newPos == s) {
                return false;
            }
            s = newPos;
            move++;
        }
        return true;
    }
    int oddEvenJumps(vector<int>& A) {
        vector<int> min(A.size());
        vector<int> max(A.size());
        vector<int> minIndex(A.size());
        vector<int> maxIndex(A.size());
        // 0(2n) space
        
        int curMin = -1;
        int curMinIndex = -1;
        int curMax = 100000+1;
        int curMaxIndex = -1;
        // O(n) time
        for (int i = A.size()-1; i >=0 ; --i) {
            int num = A[i];
            if (A[i] >= curMax) { curMax = A[i]; curMaxIndex = i; }
            if (A[i] <= curMin) { curMin = A[i]; curMinIndex = i; }
            min[i] = curMin;
            minIndex[i] = curMinIndex;
            max[i] = curMax;
            maxIndex[i] = curMaxIndex;
        }
        // Now find the solutions
        int count = 0;
        for (int i = 0 ; i < A.size(); ++i) {
            if (isGoodIndex(i, A, min, max, minIndex, maxIndex)) {
                count++;
            }
        }
        return count;
    }
};

int main() {
  vector<int> nums = { 10,13,12,14,15 };

  Solution* obj = new Solution;
  std::cout << "Number of good index: " << obj->oddEvenJumps(nums) << endl;

  return 0;
}