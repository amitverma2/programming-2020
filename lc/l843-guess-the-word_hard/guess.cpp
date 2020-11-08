#include<iostream>
#include<unordered_set>
#include<vector>

using namespace std;

class Master {
  public:
    int guess(string& str) { return 0; }
};

/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
    int N;
    int M[100][100];
    
    int match(vector<string>& wordlist, int i, int j) {
        int matches = 0;
        for (int k = 0 ; k < 6; ++k) {
            if (wordlist[i][k] == wordlist[j][k])
                matches++;
        }
        return matches;
    }

    int findBestGuess(vector<string>& W, unordered_set<int>& S, unordered_set<int>& G) {
        if (S.size() <= 2) return *S.begin();
        
        int bestGuess = -1;
        int bestGuessMaxSize = S.size();
        
        for (unordered_set<int>::const_iterator g = S.begin(); g != S.end(); ++g) {
            vector<int> m(7,0);
            
            for (unordered_set<int>::const_iterator other = S.begin(); other != S.end(); ++other) {
                if (*g != *other) {
                    m[M[*g][*other]]++;
                }
            }
            
            int max = 0;
            for (int i = 0; i < 7; ++i) {
                if (m[i] > max) {
                    max = m[i];
                }
            }
            
            if (max < bestGuessMaxSize) {
                bestGuessMaxSize = max;
                bestGuess = *g;
            }
        }
        return bestGuess;
    }
    
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        N = wordlist.size();
        if (N == 1) {
            master.guess(wordlist[0]);
            return;
        }
        
        unordered_set<int> solutionSet;
        for (int i = 0 ; i < N; ++i) solutionSet.insert(i);
        
        for (int i = 0 ; i < N; ++i)
            for (int j = i; j < N; ++j) {
                M[i][j] = M[j][i] = match(wordlist, i, j);
            }
        
        unordered_set<int> guesses;
        
        while(!solutionSet.empty()) {
            int guess = findBestGuess(wordlist, solutionSet, guesses);
            int match = master.guess(wordlist[guess]);
            if (match == 6) return ; // we are done
            
            // prune the solution set
            unordered_set<int> newSolutionSet;
            for (unordered_set<int>::const_iterator i = solutionSet.begin(); i != solutionSet.end(); ++i) {
                if (M[guess][*i] == match) {
                    newSolutionSet.insert(*i);
                }
            }
            solutionSet = newSolutionSet;
        }
    }
};

int main() {
  // no op for this problem
  return 0;
}