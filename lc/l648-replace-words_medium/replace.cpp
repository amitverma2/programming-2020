#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Solution {
    class StringTokenizer {
            string sentence;
            size_t pos;
        public:
            StringTokenizer(string _sentence) : sentence(_sentence), pos(0) { }
            string getNext(void) {
                if (pos == string::npos) return "";
                size_t nextBr = sentence.find(" ", pos);
                string token;
                if (nextBr != string::npos) {
                    token = sentence.substr(pos, nextBr-pos);
                    pos = nextBr+1;
                } else {
                    token = sentence.substr(pos);
                    pos = nextBr;
                }
                return token;
            }
    };
    class PrefixTree {
        class TrieNode {
        public:
            bool eow;
            TrieNode *children[26];

            TrieNode() : eow(false) { for(int i = 0 ; i < 26 ; ++i) children[i] = NULL; }
        };
        TrieNode * root;
    public:
        int nodes;
        PrefixTree(vector<string>& dictionary) {
            root = new TrieNode();
            nodes = 1;
            vector<string>::iterator i = dictionary.begin();
            while (i != dictionary.end()) {
                addWord(*i);
                ++i;
            }
        }
        void addWord(string word) {
            TrieNode * cur = root;
            string::const_iterator i = word.begin();
            while (i != word.end()) {
                if ((cur->children)[*i - 'a'] == NULL) {
                    (cur->children)[*i - 'a'] = new TrieNode();
                    nodes++;
                }
                cur = (cur->children)[*i - 'a'];
                ++i;
            }
            cur->eow = true;
        }
        string findRoot(string word) {
            string::const_iterator i = word.begin();

            string minRoot = "";
            TrieNode * node = root;
            while (i != word.end()) {
                if ((node->children)[*i - 'a'] == NULL) {
                    return word; // no root found
                }
                minRoot += *i;
                if ((node->children)[*i - 'a']->eow) {
                    return minRoot;
                } else {
                    node = (node->children)[*i - 'a'];
                }
                ++i;
            }
            return word;
        }
    };
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        StringTokenizer tokenize(sentence);
        PrefixTree tree(dictionary);

        string out;
        string next;
        bool first = true;
        while (!((next = tokenize.getNext()).empty())) {
            if (!first) {
                out += " ";
            } else
                first = false;
            out += tree.findRoot(next);
        }
        return out;
    }
};


int main (void) {
  vector<string> dictionary = {
    "t", "bat", "rat"
  };
  string sentence = "the cattle was rattled by the battery";
  
  Solution * obj = new Solution();

  std::cout << obj->replaceWords(dictionary, sentence) << std::endl;

  return 1;
}