#include<stack>
#include<iostream>
#include<string>

using namespace std;

class Solution {
  public:
  int lengthLongestPath(string input) {
    string::const_iterator p = input.begin();
    int pathLen = 0;
    int maxFileLen = 0;
    stack<string> dirStack;
    
    while(p != input.end()) {
      switch(*p) {
        case '\n':
          {
            p++;
            int tabs = 0;
            while (p != input.end() && *p == '\t') {
              ++tabs;
              p++;
            }
            while (dirStack.size() > tabs) {
              string dir = dirStack.top();
              dirStack.pop();
              pathLen -= dir.length();
            }
          }
          break;
        default:
          {
            string::const_iterator end = p+1;
            while (end != input.end() && *end != '\n') {
              end++;
            }
            string entry(p, end);
            p = end;
            if (entry.find('.') != string::npos) {
              // this is a file
              int fileLen = 
                pathLen + 1 /* for '/' */ + entry.length();
              if (fileLen > maxFileLen) {
                maxFileLen = fileLen;
              }
            } else {
              // this is a directory
              string stackEntry = "/" + entry;
              dirStack.push(stackEntry);
              pathLen += stackEntry.length();
            }
          }
          break;
      }
    }
    return ((maxFileLen)?(maxFileLen-1):maxFileLen);
  }
};

int main() {
  string input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";

  Solution *obj = new Solution;

  std::cout << "Longest file path in string :\n" << input << std::endl;
  std::cout << obj->lengthLongestPath(input) << std::endl;

  return 0;
}