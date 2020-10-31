#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int findArea(vector<vector<char>>& matrix,
                int x1, int y1,
                int x2, int y2) {
        int area = 0;
        for (int x = x1; x <= x2; ++x) {
            for (int y = y1; y <= y2; ++y) {
                if(matrix[x][y] == '1') {
                    area++;
                } else
                    return 0;
            }
        }
        return area;
    }
    // brute force
    int maximalRectangle(vector<vector<char>>& matrix) {
        int max = 0;
        for (int x1 = 0 ; x1 < matrix.size(); x1++) {
            for (int y1 = 0 ; y1 < matrix[x1].size(); ++y1) {
                int curMax = 0;
                for (int x2 = x1 ; x2 < matrix.size(); ++x2) {
                    for (int y2 = y1 ; y2 < matrix[x2].size(); ++y2) {
                        int area = findArea(matrix, x1, y1, x2, y2);
                        if (area > max) {
                            max = area;
                        }
                    }
                }
            }
        }
        return max;
    }
};

int main() {
  vector<vector<char> > matrix = {
    { '1', '0', '1', '0', '0' },
    { '1', '0', '1', '1', '1' },
    { '1', '1', '1', '1', '1' },
    { '1', '0', '0', '1', '0' }
  };

  Solution* obj = new Solution;

  std::cout << "Max area: " << obj->maximalRectangle(matrix) << std::endl;

  return 0;
}
