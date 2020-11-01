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

class Solution2 {
public:
    // this is brute force still
    int largestRectangleArea(const vector<int>& heights) {
        vector<int> sortedHeights = heights;
        sort(sortedHeights.begin(), sortedHeights.end());
        int max = 0;
        for (vector<int>::const_iterator i = sortedHeights.begin();
            i != sortedHeights.end();
            ++i) {
            int heightsMax = 0;
            int curMax = 0;
            for (int j = 0; j < heights.size(); ++j) {
                int min = ((heights[j] < *i)?(0):(*i));
                if (min == 0) {
                    curMax = 0;
                } else {
                    curMax += *i;
                }
                if (curMax > heightsMax) {
                    heightsMax = curMax;
                }
            }
            if (heightsMax > max) {
                max = heightsMax;
            }
        }
        return max;
    }
    
    // this is a bit optimized
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.size() == 0) { return 0; }
        
        vector<int> heights(matrix[0].size());
        
        int max = 0;
        for (int i = 0 ; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (i == 0) { 
                    heights[j] = ((matrix[i][j] == '1')?1:0);
                } else {
                    heights[j] = ((matrix[i][j] == '1')?(heights[j]+1):0);
                }
            }
            int curRowMax = largestRectangleArea(heights);
            if (curRowMax > max) {
                max = curRowMax;
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

  Solution2* obj = new Solution2;

  std::cout << "Max area: " << obj->maximalRectangle(matrix) << std::endl;

  return 0;
}
