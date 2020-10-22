#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Solution {
public:
    void reverseStringRecursion(vector<char>::iterator i,
                                vector<char>::iterator j) {
      if (i < j) {
        char tmp = *i;
        *i = *j;
        *j = tmp;
        ++i;
        --j;
        reverseStringRecursion(i, j);
      }
    }

    void reverseString(vector<char>& s) {
        if (s.size() == 0) return;
        
        vector<char>::iterator i = s.begin();
        vector<char>::iterator j = s.end() - 1;
        
        while(i < j) {
            char tmp = *i;
            *i = *j;
            *j = tmp;
            ++i;
            --j;
        }
    }
};

int main() {
  vector<char> str = { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' };

  for(auto i : str) cout << i ;
  cout << endl;
  Solution* obj = new Solution;
  //obj->reverseString(str);
  obj->reverseStringRecursion(str.begin(), str.end()-1); // doesn't work well for empty vectors
  cout << "After reversing:";
  cout << endl;
  for(auto i : str) cout << i ;
  cout << endl;
  return 0;
}