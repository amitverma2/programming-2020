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

class Solution2 {
public:
    int max(int a, int b) {
        if (a > b) return a;
        return b;
    }
    int calculateAreaRecursive(vector<int>& heights, int left, int right) {
        if (left > right) {
            return 0;
        }
        // find minimum
        int min = left;
        for (int i = left; i <= right; ++i) {
            if (heights[min] > heights[i]) {
                min = i;
            }
        }
        int minLeft = calculateAreaRecursive(heights, left, min-1);
        int minRight = calculateAreaRecursive(heights, min+1, right);
        int minHeightArea = heights[min] * (right - left + 1);
        return max(minLeft, max(minRight, minHeightArea));
    }
    // divide and conquer
    int largestRectangleArea(vector<int>& heights) {
        return calculateAreaRecursive(heights, 0, heights.size()-1);
    }
};

int main() {
  vector<int> heights = { 2, 1, 5, 6, 2, 3 };

  Solution2* obj = new Solution2;

  std::cout << "Largest rectangle area : " << obj->largestRectangleArea(heights) << std::endl;

  return 0;
}