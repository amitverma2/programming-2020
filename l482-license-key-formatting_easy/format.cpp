#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Solution {
public:
    string licenseKeyFormatting(string S, int K) {
        string out;
        int count = 0;
        for (string::reverse_iterator r = S.rbegin(); r != S.rend(); ++r) {
            if (*r != '-') {
                if (count >= K) {
                    out += '-';
                }
                out += (char)toupper(*r);
                count = (count % K) + 1;
            }
        }
        std::reverse(out.begin(), out.end());
        return out;
    }
};

int main() {
  string S = "5F3Z-2e-9-w";
  Solution *obj = new Solution;

  std::cout << "Formatted : " << obj->licenseKeyFormatting(S,4) << std::endl;

  return 0;
}