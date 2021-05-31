#include<iostream>

using namespace std;

class WordDictionary {
    struct TrieNode {
        bool eow;
        TrieNode* children[26];
        TrieNode() : eow(false) { for (int i = 0 ; i < 26; ++i) children[i] = NULL; }
    };
    TrieNode* root;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();        
    }
    
    void addWord(string word) {
        string::const_iterator i = word.begin();
        TrieNode* cur = root;
        while (i != word.end()) {
            if ((cur->children)[*i - 'a'] == NULL) {
                (cur->children)[*i - 'a'] = new TrieNode();
            }
            cur = (cur->children)[*i - 'a'];
            ++i;
        }
        cur->eow = true;
    }
    
    bool search(string word) {
        return wildcardSearch(root, word, 0);
    }
    
    bool wildcardSearch(TrieNode* node, string& word, int index) {
        if (index == word.length()) {
            if (node->eow)
                return true;
            else
                return false;
        }
        
        char c = word[index];
        
        if (c != '.') {
            if ((node->children)[c - 'a'] == NULL) {
                return false;
            }
            return wildcardSearch((node->children)[c - 'a'], word, index + 1);
        }
        
        // wildcard search
        
        for (int i = 0 ; i < 26; ++i) {
            if ((node->children)[i]) {
                if (wildcardSearch((node->children)[i], word, index + 1))
                    return true;
            }
        }
        return false;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

int main (void) {
  WordDictionary* obj = new WordDictionary();
  obj->addWord("bad");
  obj->addWord("dad");
  obj->addWord("mad");
  cout << "Is \"pad\" in the dict: " << obj->search("pad") << endl;
  cout << "Is \"bad\" in the dict: " << obj->search("bad") << endl;
  cout << "Is \".ad\" in the dict: " << obj->search(".ad") << endl;
  cout << "Is \"b..\" in the dict: " << obj->search("b..") << endl;
  return 0;
}