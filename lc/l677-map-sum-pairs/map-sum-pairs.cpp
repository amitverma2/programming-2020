#include<queue>
#include<iostream>
#include<string>

using namespace std;

class MapSum {
    class TrieNode {
        public:
            bool eow;
            int val;
            TrieNode * children[26];
            TrieNode() : eow(false), val(0) { for (int i = 0 ; i < 26; ++i) children[i] = NULL; }
    };
    TrieNode * root;
public:
    /** Initialize your data structure here. */
    MapSum() {
        root = new TrieNode();
    }
    
    void insert(string key, int val) {
        TrieNode * cur = root;
        string::const_iterator i = key.begin();
        while (i != key.end()) {
            if ((cur->children)[*i - 'a'] == 0) {
                (cur->children)[*i - 'a'] = new TrieNode();
            }
            cur = (cur->children)[*i - 'a'];
            ++i;
        }
        cur->eow = true;
        cur->val = val;
    }
    
    int sum(string prefix) {
        TrieNode * cur = root;
        int sum = 0;
        string::const_iterator i = prefix.begin();
        while (i != prefix.end()) {
            if ((cur->children)[*i - 'a'] == NULL)
                return 0; // prefix not found
            else {
                cur = (cur->children)[*i - 'a'];
                ++i;
            }
        }
        std::queue<TrieNode*> bfs;
        bfs.push(cur);
        while (!bfs.empty()) {
            TrieNode * node = bfs.front();
            bfs.pop();
            if (node->eow) {
                sum += node->val;
            }
            for (int i = 0 ; i < 26; ++i) {
                if ((node->children)[i]) {
                    bfs.push((node->children)[i]);
                }
            }
        }
        return sum;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */

int main (void) {
  MapSum * obj = new MapSum();
  obj->insert("apple", 3);
  std::cout << "Prefix sum \"ap\" = " << obj->sum("ap") << std::endl;
  obj->insert("app", 2);
  std::cout << "Prefix sum \"ap\" = " << obj->sum("ap") << std::endl;

  return 0;
}
