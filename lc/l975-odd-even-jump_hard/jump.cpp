#include<map>
#include<vector>
#include<iostream>
using namespace std;

class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
        int N = A.size();
        if (N <= 1) return N;
        
        std::map<int, int> orderedMap;
        std::vector<bool> odd(N);
        std::vector<bool> even(N);
        
        odd[N-1] = even[N-1] = true;
        
        orderedMap.insert(std::make_pair(A[N-1], N-1));
        
        for (int i = N-2; i >= 0; --i) {
            
            odd[i] = even[i] = false;
            
            int val = A[i];
            typedef std::map<int, int>::const_iterator CI;
            CI match = orderedMap.find(val);
            
            if (match != orderedMap.end()) {
                int index = match->second;
                odd[i] = even[index];
                even[i] = odd[index];
                orderedMap[val] = i;
            } else {
                CI upper = orderedMap.upper_bound(val);
                if (upper != orderedMap.end()) {
                    odd[i] = even[upper->second];
                }
                
                CI lower = orderedMap.lower_bound(val);
                if (lower != orderedMap.end()) {
                    if (lower == orderedMap.begin()) {
                        lower = orderedMap.end();
                    } else {
                        lower--;
                    }
                } else {
                    lower--;
                }
                if (lower != orderedMap.end()) {
                    even[i] = odd[lower->second];
                }
                orderedMap.insert(std::make_pair(A[i], i));
            }
        }
        int good = 0;
        for (int i = 0 ; i < N; ++i) {
            if (odd[i]) good++;
        }
        return good;
    }
};

int main() {
  Solution *obj = new Solution;
  std::vector<int> A = { 2,3,1,1,4 };

  std::cout << "Good starting indices: " << obj->oddEvenJumps(A) << std::endl;

  return 0;
}