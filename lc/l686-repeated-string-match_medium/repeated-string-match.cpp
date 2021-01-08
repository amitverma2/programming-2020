#include<string>
#include<iostream>

using namespace std;

class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        string s = a;
        while (s.size() < b.size())
            s += a;
        for (int i = 0; i * a.size() < b.size(); ++i)
            s += a;
        int loc = s.find(b);
        if (loc == string::npos)
            return -1;
        int i;
        for (i = 1; (i * a.size()) < (loc + b.size()); ++i)
            ;
        return i;
    }
};

int main() {
  string a = "aaaaaaaaaaaaaaaab";
  string b = "ba";

  Solution * obj = new Solution;

  std::cout << "repeated String match : " << obj->repeatedStringMatch(a, b) << std::endl;

  return 0;
}