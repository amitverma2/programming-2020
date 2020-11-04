#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int getPathLen(vector<vector<int>>&dp, vector<vector<int>>& matrix, int r, int c) {        
        
        if (dp[r][c]) return dp[r][c];
        
        int maxlen = 0;
        int moves[4][2] = { { 0, 1}, { 0, -1}, { 1, 0 }, { -1, 0} };
        for (int m = 0; m < 4; ++m) {
            int newR = r + moves[m][0];
            int newC = c + moves[m][1];
            if (newR < 0 || newR >= matrix.size() ||
                newC < 0 || newC >= matrix[r].size() ||
                matrix[r][c] >= matrix[newR][newC]) {
                continue;
            }
            int newLen = getPathLen(dp, matrix, newR, newC);
            if (newLen > maxlen) {
                maxlen = newLen;
            }
        }
        dp[r][c] = maxlen + 1;
        return dp[r][c];
    }
    
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.size() == 0) return 0;
        
        vector<vector<int>> dp(matrix.size());
        for (int i = 0 ; i < matrix.size(); ++i) {
            dp[i].resize(matrix[i].size());
        }                
        
        int longestPath = 0;
        
        for (int i = 0 ; i < matrix.size(); ++i) {
            for (int j = 0 ; j < matrix[i].size(); ++j) {
                int pathLen = getPathLen(dp, matrix, i, j);
                if (pathLen > longestPath) {
                    longestPath = pathLen;
                }
            }
        }
        return longestPath;
    }
};

int main() {
  vector<vector<int>> matrix = {
    { 7, 6, 1, 1 },
    { 2, 7, 6, 0 },
    { 1, 3, 5, 1 },
    { 6, 6, 3, 2 }
  };
  Solution* obj = new Solution;
  std::cout << "Longest increasing path is = " << obj->longestIncreasingPath(matrix) << std::endl;
  return 0;
}
