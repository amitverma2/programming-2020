#include<vector>
#include<iostream>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& cur, vector<int>& other) {
        int min = -1;
        for (int val = 1; val <= 6; ++val) {
            int swaps = 0;
            for (int d = 0; d < cur.size(); d++) {
                if (cur[d] != val) {
                    if (other[d] == val) {
                        swaps++;
                    } else {
                        swaps = -1;
                        break;
                    }
                }
            }
            if (swaps != -1) {
                if (min == -1) {
                    min = swaps;
                } else {
                    if (swaps < min) {
                        min = swaps;
                    }
                }
            }
        }
        return min;
    }
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        int minA = findMin(A, B);
        int minB = findMin(B, A);
        return (minA < minB)?minA:minB;
    }
};

int main() {
  std::vector<int> A = { 2, 1, 2, 4, 2, 2 };
  std::vector<int> B = { 5, 2, 6, 2, 3, 2 };

  Solution *obj = new Solution;

  std::cout << "Solution is : " << obj->minDominoRotations(A, B) << std::endl;

  return 0;
}