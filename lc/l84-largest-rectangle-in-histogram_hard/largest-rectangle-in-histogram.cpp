#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    // brute force
    int largestRectangleArea(vector<int>& heights) {
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
};

int main() {
  vector<int> heights = { 2, 1, 5, 6, 2, 3 };

  Solution* obj = new Solution;

  std::cout << "Largest rectangle area : " << obj->largestRectangleArea(heights) << std::endl;

  return 0;
}