#include<iostream>
#include<string>
#include<queue>
#include<vector>

using namespace std;

class AutocompleteSystem {
    struct TrieNode {
        bool eow;
        int times;
        string str; // the string represented by this node ; needed later
        TrieNode *children[27];
        TrieNode() : eow(false), times(0) { for (int i = 0 ; i < 27; ++i) children[i] = NULL; }
        TrieNode(string& _str) : eow(false), times(0), str(_str) { for (int i = 0 ; i < 27; ++i) children[i] = NULL; }
    };
    TrieNode * root;
    string searchString;
    TrieNode *searchNode;
public:
    class myComparison {
        public:
        bool operator() (const pair<int, string>& lhs, const pair<int, string>& rhs) {
            if (lhs.first < rhs.first) return true;
            if (lhs.first == rhs.first) return (lhs.second.compare(rhs.second) > 0);
            return false;
        }
    };
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new TrieNode();
        searchString = "";
        searchNode = root;
        /* 
         * make a prefix tree of 26 + 1 childrens in each node
         * at every terminating node, initialize count with 0
         * when a sentence is added, increment existing counte with times
         */        
        for (int i = 0 ; i < sentences.size(); ++i) {
            addSentence(sentences[i], times[i]);
        }
    }
    
    void addSentence(string& sentence, int times) {
        string::const_iterator i = sentence.begin();
        TrieNode * cur = root;
        string prefix;
        
        while (i != sentence.end()) {
            prefix += *i;
            TrieNode * child = getChild(cur, *i);
            if (!child) {
                setChild(cur, *i, new TrieNode(prefix));
            }
            cur = getChild(cur, *i); // this should be NON null for sure now.
            ++i;
        }
        cur->eow = true;
        cur->times += times;
    }
    
    void setChild(TrieNode *cur, char c, TrieNode *child) {
        if (c == ' ') {
            (cur->children)[0] = child;
        } else {
            (cur->children)[1 + c - 'a'] = child;
        }
    }
    
    TrieNode * getChild(TrieNode *node, char c) {
        if (node == NULL) return NULL;
        
        if (c == ' ') return (node->children)[0];
        
        return (node->children)[1 + c - 'a'];
    }
    
    vector<string> input(char c) {
        vector<string> autoCompletes;
        /*
         * maintain the current search string
         *
         * if c == '#', add the current search string to the prefix tree, return empty vector
         * Otherwise
         * add this char to the current search string, and move down in the prefix tree if possible
         * let the current node by 'node'
         * do a BFS from this node, and add the sentences found to a
         * heap sorted on times, and then on the string
         *
         * return the top three entries of this heap everytime
         *
         */
        if (c == '#') {
            addSentence(searchString, 1);
            searchString = ""; // reset search string
            searchNode = root; // reset search node position
            return autoCompletes; // it is empty vector
        }
        // update search string
        searchString += c;
        // get to next search node
        searchNode = getChild(searchNode, c);      
        if (searchNode == NULL) {
            // no matches
            return autoCompletes;
        }
        // from this node find all the sentences and add them to the heap
        // here is my heap
        priority_queue<pair<int, string>, vector<pair<int, string>>, myComparison> myHeap;
        // do a bfs and add all sentences
        queue<TrieNode *> bfs;
        bfs.push(searchNode);
        while (!bfs.empty()) {
            TrieNode * cur = bfs.front();
            bfs.pop();
            if (cur->eow) {
                myHeap.push(make_pair(cur->times, cur->str));
            }
            for (int i = 0 ; i < 27; ++i) {
                if ((cur->children)[i] != NULL) {
                    bfs.push((cur->children)[i]);
                }
            }
        }
        // find the top three entries of the heap and add to vector
        for (int i = 0 ; i < 3 && !myHeap.empty(); ++i) {
            pair<int, string> topMatch = myHeap.top();
            autoCompletes.push_back(topMatch.second);
            myHeap.pop();
        }
        return autoCompletes;
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */

int main (void) {
  vector<string> sentences = {
    "i love you",
    "island",
    "iroman",
    "i love leetcode"
  };
  vector<int> times = {
    5,
    3,
    2,
    2
  };

  AutocompleteSystem * obj = new AutocompleteSystem(sentences, times);
  cout << "Input : i\n";
  vector<string> param_1 = obj->input('i');
  for (auto autoCompletes : param_1) { cout << autoCompletes << endl; }
  cout << "Input : <space>\n";
  param_1 = obj->input(' ');
  for (auto autoCompletes : param_1) { cout << autoCompletes << endl; }
  cout << "Input : a\n";
  param_1 = obj->input('a');
  for (auto autoCompletes : param_1) { cout << autoCompletes << endl; }
  cout << "Input : #\n";
  param_1 = obj->input('#');
  for (auto autoCompletes : param_1) { cout << autoCompletes << endl; }
  cout << "End.\n";
  return 0;
}