#include<iostream>
#include<unordered_set>
#include<string>
#include<vector>

using namespace std;

// lc 929 Unique email addresses

class Solution {
    string normalizeEmailId(string &email) {
        string normalized(email);
        
        int atPos = normalized.find('@');
        // we must have at != std::string::npos
        int plusPos = normalized.find('+');
        if (plusPos != string::npos &&
            plusPos < atPos) { // while not mentioned, the plus can occur after @ sign, we should only handle the plus sign if it occurs in the local name
            // remove the stuff between + & @
            normalized.erase(plusPos, atPos - plusPos);
        }
        
        for(int dotPos = normalized.find('.');
            (dotPos != string::npos && dotPos < normalized.find('@'));
            dotPos = normalized.find('.')) {
            normalized.erase(dotPos,1);
        }
        
        return normalized;
    }
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_set<string> normalizedEmailsSet;
        
        for (int i = 0; i < emails.size(); ++i) {
            normalizedEmailsSet.insert(normalizeEmailId(emails[i]));
        }
        return normalizedEmailsSet.size();
    }
};

int main() {
  vector<string> emails = { "test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com" };

  Solution* obj = new Solution;

  std::cout << "Total emails sent : " << obj->numUniqueEmails(emails) << std::endl;
  return 0;
}