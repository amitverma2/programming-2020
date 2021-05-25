#include<iostream>
#include<unordered_map>
#include<string>

using namespace std;

class Trie {
    struct TrieNode {
        bool eow; // end of word
        std::unordered_map<char, TrieNode*> children;
    };
    TrieNode * root;
    TrieNode * find(string str) {
        TrieNode * cur = root;
        string::const_iterator i = str.begin();
        while (i != str.end()) {
            if ((cur->children)[*i] == NULL)
                return NULL;
            else {
                cur = (cur->children)[*i];
                ++i;
            }
        }
        return cur;
    }
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
        root->eow = false; // umm...
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        string::const_iterator i = word.begin();
        TrieNode * cur = root;
        while (i != word.end()) {
            if ((cur->children)[*i] == NULL) {
                (cur->children)[*i] = new TrieNode();
            }
            cur = (cur->children)[*i];
            ++i;
        }
        cur->eow = true; // this is the end of an inserted word
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode * node = find(word);
        if (node && node->eow) return true;
        return false;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode * node = find(prefix);
        if (node) return true;
        return false;        
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
int main (void) {
  Trie * obj = new Trie();
  obj->insert("apple");
  bool found = obj->search("apple");
  std::cout << "apple:" << (found?"found":"not found") << std::endl;
  return 0;
}
