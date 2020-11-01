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

class Solution3 {
public:
    int max(int a, int b) {
        if (a > b) return a;
        return b;
    }
    int min(int a, int b) {
        if (a < b) return a;
        return b;
    }
    struct Node {
        Node* l;
        Node* r;
        int s; int e; // start and end index
        int min; // index of the minimum value between start and end
    };
    Node* makeSegTree(vector<int>& heights, int ss, int se) {
        if (ss > se) return nullptr;
        Node* node = new Node;
        node->s = ss;
        node->e = se;
        node->l = node->r = nullptr;
        if (ss == se) {
            node->min = ss;
            // std::cout << "Leaf node: " << "s = " << ss << ", e = " << se << " min = " << ss << std::endl;
        } else {
            int mid = ss + (se - ss)/2;
            node->l = makeSegTree(heights, ss, mid);
            node->r = makeSegTree(heights, mid+1, se);
            node->min = mid;
            if (node->l) {
                node->min = ((heights[node->min] < heights[node->l->min])?node->min:node->l->min);
            }
            if (node->r) {
                node->min = ((heights[node->min] < heights[node->r->min])?node->min:node->r->min);
            }
            // std::cout << "Not leaf node: " << "s = " << ss << ", e = " << se << " min = " << ss << std::endl;
        }
        return node;
    }
    int findMinSegTree(Node* root, vector<int>& heights, int qs, int qe) {
        if (root == nullptr ||
            root->s > qe ||
            root->e < qs) {
            return -1;
        }
        if (qs <= root->s && qe >= root->e) {
            return root->min;
        }
        int minL = findMinSegTree(root->l, heights, qs, qe);
        int minR = findMinSegTree(root->r, heights, qs, qe);
        if (minL == -1) {
            return minR;
        }
        if (minR == -1) {
            return minL;
        }
        return ((heights[minR] < heights[minL])?minR:minL);
    }
    int calculateAreaRecursive(Node* root, vector<int>& heights, int left, int right) {
        if (left > right) {
            return 0;
        }
        // find index with minimum value between left and right index
        int min = findMinSegTree(root, heights, left, right);

        int minLeft = calculateAreaRecursive(root, heights, left, min-1);
        int minRight = calculateAreaRecursive(root, heights, min+1, right);
        int minHeightArea = heights[min] * (right - left + 1);
        return max(minLeft, max(minRight, minHeightArea));
    }
    int largestRectangleArea(vector<int>& heights) {
        if (heights.size() == 0)
            return 0;
        if (heights.size() == 1)
            return heights[0];
        
        // std::cout << "Using segment tree and divide-and-conquer\n";
        Node* root = makeSegTree(heights, 0, heights.size()-1);
        return calculateAreaRecursive(root, heights, 0, heights.size()-1);
    }
};

int main() {
  vector<int> heights = { 2, 1, 5, 6, 2, 3 };

  Solution3* obj = new Solution3;

  std::cout << "Largest rectangle area : " << obj->largestRectangleArea(heights) << std::endl;

  return 0;
}