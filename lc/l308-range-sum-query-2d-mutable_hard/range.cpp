#include<iostream>
#include<vector>

using namespace std;

class NumMatrix {
    int rows;
    int cols;
    vector<vector<int>>& matrix;
    vector<vector<int>> bit;
    
    int lsb(int val) {
        return val & (-val);
    }
    
    void updateBIT(int r, int c, int diff) {
        for (int i = r; i <= rows; i += lsb(i)) {
            for (int j = c; j <= cols; j += lsb(j)) {
                bit[i][j] += diff;
            }
        }
    }
    
    void buildBIT(vector<vector<int>>& matrix) {
        for (int r = 1; r <= rows; ++r)
            for (int c = 1; c <= cols; ++c)
                updateBIT(r, c, matrix[r-1][c-1]);
    }
    
    int queryBIT(int r, int c) {
        int sum = 0;
        
        for (int i = r; i > 0; i -= lsb(i))
            for (int j = c; j > 0; j -= lsb(j))
                sum += bit[i][j];
        
        return sum;
    }

public:
    NumMatrix(vector<vector<int>>& matrix) : matrix(matrix) {
        if (matrix.empty() || matrix[0].empty())
            return;
        
        rows = matrix.size();
        cols = matrix[0].size();
        
        bit.resize(rows+1);
        for (int r = 1; r <= rows; ++r)
            bit[r].resize(cols+1, 0);
        
        buildBIT(matrix);
    }
    
    void update(int row, int col, int val) {
        int diff = val - matrix[row][col];
        matrix[row][col] = val;
        updateBIT(row+1, col+1, diff);
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        ++row1; ++col1; ++row2; ++col2;
        return queryBIT(row2, col2)
            - queryBIT(row1-1, col2)
            - queryBIT(row2, col1-1)
            + queryBIT(row1-1, col1-1);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
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

  std::cout << "SumRegion 2,1 - 4,3 : " << obj->sumRegion(2, 1, 4, 3) << std::endl;

  obj->update(3, 2, 2);

  std::cout << "SumRegion 2,1 - 4,3 : " << obj->sumRegion(2, 1, 4, 3) << std::endl;

  return 0;
}