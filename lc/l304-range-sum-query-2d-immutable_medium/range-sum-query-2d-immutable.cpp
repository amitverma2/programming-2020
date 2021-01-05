#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class NumMatrixCachedHash {
    vector<vector<int>>& matrix;
    bool fast;
    unordered_map<unsigned int, int> hash;
    unsigned int numBits;
    unsigned int mask;
public:
    NumMatrixCachedHash(vector<vector<int>>& matrix) : matrix(matrix), fast(false), numBits(sizeof(unsigned int) * 8), mask(~(~(unsigned int)(0) << (numBits/4))) {
        if (matrix.size() > 10 & matrix.size() <= (2^(numBits/4))) { 
            fast = true;
        }
    }
    int fastSumRegion(int r1, int c1, int r2, int c2) {
        unsigned int box =
            (c2 & mask) |
            ((r2 & mask) << (numBits/4)) |
            ((c1 & mask) << (numBits/2)) |
            ((r1 & mask) << (3* (numBits/4)));
        unordered_map<unsigned int, int>::const_iterator got = hash.find(box);
        if (got != hash.end()) {
            return got->second;
        }
        if (r1 == r2 && c1 == c2) {
            hash[box] = matrix[r1][c1];
            return matrix[r1][c1];
        }
        // special case of small sub matrix
        if (r2 - r1 < 10 && c2 - c1 < 10) {
            int sum = 0;
            for (int r = r1; r <= r2; ++r) {
                for (int c= c1; c <= c2; ++c) {
                    sum += matrix[r][c];
                }
            }
            hash[box] = sum;
            return sum;
        }
        // break this box into four boxes each dimension in half
        int h = c2-c1; // |
        int w = r2-r1; // -
        // a, b
        // c, d
        int a_r1 = r1;
        int a_c1 = c1;
        int a_r2 = a_r1 + w/2;
        int a_c2 = a_c1 + h/2;
        int a_sum = fastSumRegion(a_r1, a_c1, a_r2, a_c2);
        
        int b_r1 = r1;
        int b_c1 = a_c2 + 1;
        int b_r2 = a_r2;
        int b_c2 = c2;
        int b_sum = fastSumRegion(b_r1, b_c1, b_r2, b_c2);
        
        int c_r1 = a_r2 + 1;
        int c_c1 = c1;
        int c_r2 = r2;
        int c_c2 = a_c2;
        int c_sum = fastSumRegion(c_r1, c_c1, c_r2, c_c2);
        
        int d_r1 = c_r1;
        int d_c1 = b_c1;
        int d_r2 = r2;
        int d_c2 = c2;
        int d_sum = fastSumRegion(d_r1, d_c1, d_r2, d_c2);
        
        return (hash[box] = a_sum + b_sum + c_sum + d_sum);
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        if (fast) {
            return fastSumRegion(row1, col1, row2, col2);
        }
        
        int sum = 0;
        for (int r = row1; r <= row2; ++r) {
            for (int c= col1; c <= col2; ++c) {
                sum += matrix[r][c];
            }
        }
        return sum;
    }
};

class NumMatrixCachedRow {
    vector<vector<int>>& nums;
    vector<vector<int>> sums;
public:
    NumMatrixCachedRow(vector<vector<int>>& matrix) : nums(matrix), sums(matrix) {
        for (int r = 0 ; r < matrix.size(); ++r) {
            for (int c = 1; c < matrix[r].size(); ++c) {
                sums[r][c] += sums[r][c-1];
            }
        }        
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = 0;
        for (int r = row1; r <= row2; ++r) {
            sum += sums[r][col2] - sums[r][col1] + nums[r][col1];
        }
        return sum;
    }
};

class NumMatrixCachedBox {
    vector<vector<int>>& nums;
    vector<vector<int>> sums;
public:
    NumMatrixCachedBox(vector<vector<int>>& matrix) : nums(matrix), sums(matrix) {
        for (int r = 0 ; r < matrix.size(); ++r) {
            for (int c = 0; c < matrix[r].size(); ++c) {
                if (r == 0) {
                    if (c != 0) {
                        sums[r][c] += sums[r][c-1];
                    }
                } else if (c == 0) {
                    sums[r][c] += sums[r-1][c];
                } else {
                    sums[r][c] += sums[r-1][c] + sums[r][c-1] - sums[r-1][c-1];
                }
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = sums[row2][col2];
        if (row1 > 0) sum -= sums[row1-1][col2];
        if (col1 > 0) sum -= sums[row2][col1-1];
        if (row1 > 0 & col1 > 0) sum += sums[row1-1][col1-1];
        return sum;
    }
};

class NumMatrix {
    int **sums;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty())
            return;
        
        sums = new int*[matrix.size()+1];
        for (int r = 0; r <= matrix.size(); ++r) {
          sums[r] = new int[matrix[0].size()+1]();
        }
        
        for (int r = 0; r < matrix.size(); ++r) {
            for (int c = 0; c < matrix[0].size(); ++c) {
                sums[r+1][c+1] = matrix[r][c] + sums[r][c+1] + sums[r+1][c] - sums[r][c];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return sums[row2+1][col2+1] - sums[row1][col2+1] - sums[row2+1][col1] + sums[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

int main() {
  vector<vector<int>> matrix = {
    { 3, 0, 1, 4, 2 },
    { 5, 6, 3, 2, 1 },
    { 1, 2, 0, 1, 5 },
    { 4, 1, 0, 1, 7 },
    { 1, 0, 3, 0, 5 }
  };

  NumMatrix *obj = new NumMatrix(matrix);

  std::cout << "SumRegion 2,1 4,3 : " << obj->sumRegion(2, 1, 4, 3) << std::endl;

  return 0;
}