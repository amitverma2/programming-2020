#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> out;
        for (int i = 0; i < words.size(); ++i) {
            if (found(board, words[i])) {
                out.push_back(words[i]);
            }
        }
        return out;
    }
    bool found(vector<vector<char>>& board, string& word) {
        // words[i] is always >=1
        char c = word[0];
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == c) {
                    // check if from this position this word can be found
                    bool visited[12][12] = { 0 };
                    if (foundFromPos(i, j, board, word, 0, visited)) {
                        //cout << "i =" << i << " j = " << j << endl;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    bool foundFromPos(int i, int j, vector<vector<char>>& board, string& word, int pos, bool visited[12][12]) {
        //cout << "i " << i << " j " << j << " pos " << pos << " s " << word << endl;
        if (pos == word.length()) return true;

        if (board[i][j] != word[pos]) return false;
        
        if (pos == word.length() - 1) return true;
        
        visited[i][j] = true; // mark this position as visited
        
        bool saved[12][12] = { 0 };
        
        if (i > 0) {
            saveVisited(visited, saved);
            if (!visited[i-1][j] && foundFromPos(i - 1, j, board, word, pos+1, visited)) {
                restoreVisited(saved, visited);
                return true;
            }
            restoreVisited(saved, visited);
        }
        if (i < (board.size() - 1)) {
            saveVisited(visited, saved);
            if (!visited[i+1][j] && foundFromPos(i + 1, j, board, word, pos+1, visited)) {
                restoreVisited(saved, visited);
                return true;
            }
            restoreVisited(saved, visited);
        }
        if (j > 0) {
            saveVisited(visited, saved);
            if (!visited[i][j-1] && foundFromPos(i, j - 1, board, word, pos+1, visited)) {
                restoreVisited(saved, visited);
                return true;
            }
            restoreVisited(saved, visited);
        }
        if (j < (board[i].size() - 1)) {
            saveVisited(visited, saved);
            if (!visited[i][j+1] && foundFromPos(i, j + 1, board, word, pos+1, visited)) {
                restoreVisited(saved, visited);
                return true;
            }
            restoreVisited(saved, visited);
        }
        return false;
    }
    
    void saveVisited(bool v[12][12], bool s[12][12]) {
        for (int i = 0; i < 12; ++i)
            for (int j = 0; j < 12; ++j)
                s[i][j] = v[i][j];
    }
    
    void restoreVisited(bool s[12][12], bool v[12][12]) {
        for (int i = 0; i < 12; ++i)
            for (int j = 0; j < 12; ++j)
                v[i][j] = s[i][j];
    }
};

int main (void) {
  Solution* obj = new Solution();
  vector<vector<char>> board = {
    { 'o', 'a', 'a', 'n' },
    { 'e', 't', 'a', 'e' },
    { 'i', 'h', 'k', 'r' },
    { 'i', 'f', 'l', 'v' },
  };
  vector<string> words = {
    "oath",
    "pea",
    "eat",
    "rain",
  };
  vector<string> out = obj->findWords(board, words);
  for (int i = 0; i < out.size(); ++i) {
    cout << out[i] << endl;
  }
  return 0;
}
