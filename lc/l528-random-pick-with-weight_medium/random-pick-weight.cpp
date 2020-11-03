#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

class Solution {
    vector<int> _w;
    int maxwt;
public:
    Solution(vector<int>& w) : _w(w.size()), maxwt(0) {
        for (int i = 0 ; i < w.size(); ++i) {
            maxwt += w[i];
            _w[i] = maxwt;
        }
    }
    
    int pickIndex() {
        int pick = rand() % maxwt + 1;
        for (int i = 0; i < _w.size(); ++i) {
            if (_w[i] >= pick) {
                return i;
            }
        }
        return _w.size()-1; // should never come here actually
    }
};

int main() {
  vector<int> weights = { 1 , 3 };

  Solution* obj = new Solution(weights);
  for(int i = 0 ; i < 10000; ++i) {
    std::cout << "Rand index with weights = " << obj->pickIndex() << std::endl;
  }
  return 0;
}